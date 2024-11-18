#include "restore.h"
#include "ui_restore.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

const int METADATA_SIZE = 512;

QString password;

// XOR 加密/解密函数
QByteArray restore::xorEncryptDecrypt(const QByteArray &data, const QByteArray &key) {
    QByteArray result(data.size(), 0);
    for (int i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

restore::restore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::restore)
{
    ui->setupUi(this);
    connect(this->ui->res_button, SIGNAL(clicked(bool)), this, SLOT(BrowseBuSource()));
    connect(this->ui->rst_button, SIGNAL(clicked(bool)), this, SLOT(BrowseRstSource()));
    connect(this->ui->rst, SIGNAL(clicked(bool)), this, SLOT(RestoreResources()));
    connect(this->ui->return_main, SIGNAL(clicked(bool)), this, SLOT(return_click()));
    connect(this->ui->pwd_button, SIGNAL(clicked(bool)), this, SLOT(setPassword()));
}

restore::~restore()
{
    delete ui;
}

// 计算填充字节数
quint64 restore::calculatePadding(quint64 size) {
    return (512 - (size % 512)) % 512;
}

QString getRelativePath(const QString &filepath, const QString &dir) {
    QFileInfo fileInfo(filepath);
    QDir directory(dir);
    QString relativePath = directory.relativeFilePath(fileInfo.absoluteFilePath());
    return relativePath;
}

void restore::BrowseBuSource(){
    QFileDialog dialog(this, tr("选择要恢复的文件"), ui->bu_res->text(), tr("所有文件 (*)"));
    dialog.setFileMode(QFileDialog::ExistingFiles); // 设置为选择一个或多个文件
    if (dialog.exec()) {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty()) {
            // 将文件路径转换为字符串，并在LineEdit中显示
            ui->bu_res->setText(files.join(";"));
        }
    }
}

void restore::BrowseRstSource(){
    QString path = QFileDialog::getExistingDirectory(this, tr("选择恢复目录"), ui->rst_res->text());
    if (!path.isEmpty()) {
        ui->rst_res->setText(path);
    }
}

void restore::setPassword(){
    password = ui->password->text();
    if (!this->password.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("密钥已设置成功！"));
    } else {
        QMessageBox::warning(this, tr("警告"), tr("密钥不能为空！"));
    }
}

bool restore::unpackFiles(const QString &inputFilePath, const QString &restorePath) {
    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "can't open input file:" << inputFilePath;
        return false;
    }

    QDataStream in(&inputFile);
    in.setByteOrder(QDataStream::LittleEndian); // 设置字节序，确保一致性

    // 读取全局元数据
    QByteArray globalMetadata(METADATA_SIZE, '\0');
    in.readRawData(globalMetadata.data(), METADATA_SIZE);

    bool isDirectoryPack;
    QDataStream globalMetaStream(&globalMetadata, QIODevice::ReadOnly);
    globalMetaStream.setByteOrder(QDataStream::LittleEndian);
    globalMetaStream >> isDirectoryPack;
    qDebug() << isDirectoryPack;
    if (globalMetaStream.status() != QDataStream::Ok) {
        qDebug() << "invalid global metadata";
        return false;
    }

    QString originalRootPath;
    if (isDirectoryPack) {
        QByteArray originalRootPathBytes;
        globalMetaStream >> originalRootPathBytes;
        originalRootPath = QString::fromUtf8(originalRootPathBytes.trimmed());
        qDebug() << "Original root path: " << originalRootPath;
    }

    while (!in.atEnd()) {
        // 读取文件元数据
        QByteArray metadata(METADATA_SIZE, '\0');
        in.readRawData(metadata.data(), METADATA_SIZE);

        QByteArray filePathBytes;
        quint64 fileSize;
        quint32 expectedCrc32;
        QDataStream metaStream(&metadata, QIODevice::ReadOnly);
        metaStream.setByteOrder(QDataStream::LittleEndian);
        metaStream >> filePathBytes;
        metaStream >> fileSize;
        metaStream >> expectedCrc32; // 读取 CRC32 校验值

        // 检查文件路径和文件大小的有效性
        if (filePathBytes.isEmpty()) {
            qDebug() << "Invalid file entry: filePath is empty";
            break; // 停止读取，因为后续数据可能是无效的
        }

        if (metaStream.status() != QDataStream::Ok) {
            qDebug() << "invalid metadata";
            break;
        }

        // 提取文件名并构建目标文件路径
        QString filePath = QString::fromUtf8(filePathBytes.trimmed());
        QFileInfo fileInfo(filePath);

        QString targetFile;
        if (isDirectoryPack) {
            QString relativePath = getRelativePath(fileInfo.absoluteFilePath(), originalRootPath);
            targetFile = restorePath + "/" + relativePath;
            qDebug() << "relativePath: " << relativePath;
        } else {
            targetFile = restorePath + "/" + fileInfo.fileName();
        }

        qDebug() << "Restoring file to:" << targetFile;

        // 创建目标文件目录
        QDir().mkpath(QFileInfo(targetFile).absolutePath());

        // 读取文件数据
        if (fileSize > 0) {
            QByteArray fileData(fileSize, 0);
            in.readRawData(fileData.data(), fileSize);

            if (in.status() != QDataStream::Ok) {
                qDebug() << "can't read raw data";
                return false;
            }

            // 解密文件数据
            QByteArray decryptedData = xorEncryptDecrypt(fileData, password.toUtf8());

            // 计算文件的 CRC32 校验值
            quint32 actualCrc32 = qChecksum(decryptedData.constData(), decryptedData.size());

            // 验证 CRC32 校验值
            if (actualCrc32 != expectedCrc32) {
                qDebug() << "CRC32 verification failed for file:" << targetFile;
                QMessageBox::critical(this, tr("错误"), tr("密钥不正确！"));
                return false;
            }

            // 恢复文件
            QFile outFile(targetFile);
            if (outFile.open(QIODevice::WriteOnly)) {
                outFile.write(decryptedData);
                outFile.close();
            } else {
                qDebug() << "can't open outfile:" << targetFile;
                return false;
            }
        } else {
            // 对于空文件，直接创建一个空文件
            QFile outFile(targetFile);
            if (outFile.open(QIODevice::WriteOnly)) {
                outFile.close(); // 创建一个空文件
            } else {
                qDebug() << "can't open outfile:" << targetFile;
                return false;
            }
        }

        // 跳过填充
        quint64 paddingSize = calculatePadding(fileSize);
        in.skipRawData(paddingSize);
    }

    inputFile.close();
    return true;
}

void restore::RestoreResources(){
    QString backupPath = ui->bu_res->text();
    QString restorePath = ui->rst_res->text();

    if (backupPath.isEmpty() || restorePath.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("请选择备份数据和恢复位置！"));
        return;
    }

    if (this->password.isEmpty()) {
         QMessageBox::warning(this, tr("警告"), tr("请先输入密钥！"));
         return;
     }

    QStringList backupPaths = backupPath.split(";", QString::SkipEmptyParts);
    bool allSuccess = true;

    foreach (const QString &backupPath, backupPaths) {
        QFileInfo fileInfo(backupPath);
        if (!fileInfo.isFile()) {
            QMessageBox::warning(this, tr("警告"), tr("备份路径不是一个有效的文件：%1").arg(backupPath));
            allSuccess = false;
            continue;
        }

        if (!unpackFiles(backupPath, restorePath)) {
            //QMessageBox::critical(this, tr("错误"), tr("恢复文件 %1 失败！").arg(backupPath));
            allSuccess = false;
        }
    }

    if (allSuccess) {
        QMessageBox::information(this, tr("成功"), tr("所有文件恢复成功！"));
    } else {
        QMessageBox::critical(this, tr("错误"), tr("部分文件恢复失败！"));
    }
}

void restore::return_click(){
    emit return_to_main();
    this->hide();
}
