#include "restore.h"
#include <QCryptographicHash>
#include <QDataStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_restore.h"
const int METADATA_SIZE = 512;

QString password;

// XOR 加密/解密函数
QByteArray restore::xorEncryptDecrypt(const QByteArray &data, const QByteArray &key)
{
    QByteArray result(data.size(), 0);
    for (int i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

restore::restore(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::restore)
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
quint64 restore::calculatePadding(quint64 size)
{
    return (512 - (size % 512)) % 512;
}

QString getRelativePath(const QString &filepath, const QString &dir)
{
    // 确保路径使用正斜杠
    QString normalizedFilePath = filepath;
    QString normalizedDir = dir;

    normalizedFilePath.replace("\\", "/");
    normalizedDir.replace("\\", "/");

    // 查找目录名在文件路径中的位置
    int index = normalizedFilePath.indexOf(normalizedDir);
    if (index == -1) {
        // 如果目录名未找到，直接返回文件名
        return QFileInfo(filepath).fileName();
    }

    // 截取从目录名开始的相对路径
    QString relativePath = normalizedFilePath.mid(index);

    return relativePath;
}



void restore::BrowseBuSource()
{
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

void restore::BrowseRstSource()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("选择恢复目录"), ui->rst_res->text());
    if (!path.isEmpty()) {
        ui->rst_res->setText(path);
    }
}

void restore::setPassword()
{
    password = ui->password->text();
    if (!this->password.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("密钥已设置成功！"));
    } else {
        QMessageBox::warning(this, tr("警告"), tr("密钥不能为空！"));
    }
}

bool restore::unpackFilesWithProgress(const QString &inputFilePath, const QString &restorePath, QProgressDialog &progressDialog)
{
    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开输入文件:" << inputFilePath;
        return false;
    }

    QString tempFilePath;
    if (!decompressWithZlibStream(inputFile, tempFilePath)) {
        qDebug() << "解压失败";
        inputFile.close();
        return false;
    }

    inputFile.close();

    QFile tempFile(tempFilePath);
    if (!tempFile.open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开临时解压文件:" << tempFilePath;
        return false;
    }

    QDataStream in(&tempFile);
    in.setByteOrder(QDataStream::LittleEndian);

    // 读取全局元数据
    QByteArray globalMetadata(METADATA_SIZE, '\0');
    if (in.readRawData(globalMetadata.data(), METADATA_SIZE) != METADATA_SIZE) {
        qDebug() << "读取全局元数据失败";
        tempFile.close();
        tempFile.remove();
        return false;
    }

    QString rootDirectoryName;
    QDataStream globalMetaStream(&globalMetadata, QIODevice::ReadOnly);
    globalMetaStream.setByteOrder(QDataStream::LittleEndian);
    QByteArray rootDirBytes;
    globalMetaStream >> rootDirBytes; // 读取根目录名称
    rootDirectoryName = QString::fromUtf8(rootDirBytes.trimmed());

    qDebug() << "恢复的根目录名称:" << rootDirectoryName;

    bool allSuccess = true;
    while (!in.atEnd()) {
        QByteArray metadata(METADATA_SIZE, '\0');
        if (in.readRawData(metadata.data(), METADATA_SIZE) != METADATA_SIZE) {
            break; // 无法读取文件元数据
        }

        QByteArray filePathBytes;
        quint64 fileSize;
        quint32 expectedCrc32;
        QDataStream metaStream(&metadata, QIODevice::ReadOnly);
        metaStream.setByteOrder(QDataStream::LittleEndian);
        metaStream >> filePathBytes >> fileSize >> expectedCrc32;

        QString filePath = QString::fromUtf8(filePathBytes.trimmed());
        if (filePath.isEmpty()) {
            break; // 无效文件路径
        }

        // 使用 getRelativePath 拼接恢复路径
        QString relativePath = getRelativePath(filePath, rootDirectoryName);
        QString targetFile = restorePath + "/" + relativePath;

        // 创建目标文件目录
        if (!QDir().mkpath(QFileInfo(targetFile).absolutePath())) {
            qDebug() << "无法创建目录:" << QFileInfo(targetFile).absolutePath();
            allSuccess = false;
            continue;
        }

        // 解密和写入文件
        QByteArray encryptedData(fileSize, 0);
        if (in.readRawData(encryptedData.data(), fileSize) != static_cast<qint64>(fileSize)) {
            allSuccess = false;
            continue;
        }

        QFile outFile(targetFile);
        if (!outFile.open(QIODevice::WriteOnly)) {
            allSuccess = false;
            continue;
        }

        QByteArray decryptedData = xorEncryptDecrypt(encryptedData, password.toUtf8());
        outFile.write(decryptedData);
        outFile.close();

        // 跳过填充数据
        quint64 paddingSize = calculatePadding(fileSize);
        in.skipRawData(paddingSize);

        // 更新进度条
        progressDialog.setValue(progressDialog.value() + 1);
        QCoreApplication::processEvents(); // 刷新 UI
    }

    tempFile.close();
    tempFile.remove();
    return allSuccess;
}

bool restore::decompressWithZlibStream(QIODevice &inputFile, QString &tempFilePath) {
    QTemporaryFile tempFile;
    tempFile.setAutoRemove(false); // 手动删除临时文件
    if (!tempFile.open()) {
        qDebug() << "无法创建临时文件用于解压!";
        return false;
    }
    tempFilePath = tempFile.fileName();

    z_stream strm;
    memset(&strm, 0, sizeof(strm));

    // 初始化解压流
    if (inflateInit(&strm) != Z_OK) {
        qDebug() << "inflateInit failed!";
        tempFile.close();
        return false;
    }

    const int bufferSize = 4096;  // 定义缓冲区大小
    char inBuffer[bufferSize];    // 输入缓冲区
    char outBuffer[bufferSize];   // 输出缓冲区

    int ret = Z_OK;  // inflate 返回值
    do {
        // 读取压缩数据块到输入缓冲区
        strm.avail_in = inputFile.read(inBuffer, bufferSize);
        if (strm.avail_in == 0) {
            // 如果没有更多数据可供读取，则退出循环
            break;
        }

        strm.next_in = reinterpret_cast<Bytef*>(inBuffer);  // 指向输入缓冲区

        // 解压循环，直到输出缓冲区耗尽
        do {
            strm.avail_out = bufferSize;  // 设置输出缓冲区大小
            strm.next_out = reinterpret_cast<Bytef*>(outBuffer);  // 指向输出缓冲区

            ret = inflate(&strm, Z_NO_FLUSH);  // 解压
            if (ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
                qDebug() << "Decompression error! Return code:" << ret;
                inflateEnd(&strm);  // 清理资源
                tempFile.close();
                tempFile.remove();
                return false;  // 返回失败
            }

            // 计算输出数据的大小
            int writeSize = bufferSize - strm.avail_out;

            // 将解压后的数据写入临时文件
            if (writeSize > 0) {
                if (tempFile.write(outBuffer, writeSize) != writeSize) {
                    qDebug() << "写入临时文件失败!";
                    inflateEnd(&strm);
                    tempFile.close();
                    tempFile.remove();
                    return false;  // 返回失败
                }
            }
        } while (strm.avail_out == 0);  // 输出缓冲区未耗尽时继续解压
    } while (ret != Z_STREAM_END && !inputFile.atEnd());  // 如果未解压完成且输入流未结束，继续解压

    // 释放解压资源
    inflateEnd(&strm);

    // 检查解压是否成功完成
    if (ret != Z_STREAM_END) {
        qDebug() << "Decompression did not reach Z_STREAM_END. Data may be incomplete.";
        tempFile.close();
        tempFile.remove();
        return false;  // 返回失败
    }

    qDebug() << "Decompression finished. Total decompressed size:" << tempFile.size();
    tempFile.close();  // 关闭临时文件
    return true;  // 解压成功
}


void restore::RestoreResources()
{
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

    // 打开压缩包并统计文件总数
    QFileInfo fileInfo(backupPath);
    if (!fileInfo.isFile()) {
        QMessageBox::warning(this, tr("警告"), tr("备份路径不是一个有效的文件：%1").arg(backupPath));
        return;
    }

    int totalFiles = countFilesInBackup(backupPath); // 调用新方法统计文件数
    qDebug() << "Total files to restore:" << totalFiles;

    if (totalFiles <= 0) {
        QMessageBox::warning(this, tr("警告"), tr("备份文件中未找到有效数据！"));
        return;
    }

    // 创建模态进度对话框
    QProgressDialog progressDialog(tr("恢复进行中，请稍候..."), tr("取消"), 0, totalFiles, this);
    progressDialog.setWindowModality(Qt::ApplicationModal);
    progressDialog.setWindowTitle(tr("恢复进度"));
    progressDialog.setValue(0); // 初始化进度值
    progressDialog.show();
    QCoreApplication::processEvents(); // 刷新事件循环

    // 恢复文件
    bool allSuccess = unpackFilesWithProgress(backupPath, restorePath, progressDialog);

    progressDialog.setValue(totalFiles); // 完成进度条

    if (allSuccess) {
        QMessageBox::information(this, tr("成功"), tr("所有文件恢复成功！"));
        clearAllText();
    } else {
        QMessageBox::critical(this, tr("错误"), tr("部分文件恢复失败！"));
    }
}


void restore::return_click()
{
    emit return_to_main();
    this->hide();
}

void restore::clearAllText()
{
    // 遍历当前窗口的所有子控件
    foreach (QObject *child, this->children()) {
        // 如果是 QLineEdit
        if (QLineEdit *lineEdit = qobject_cast<QLineEdit *>(child)) {
            lineEdit->clear();
        }
    }

    qDebug() << "All text fields have been cleared!";
}

int restore::countFilesInBackup(const QString &inputFilePath)
{
    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开输入文件:" << inputFilePath;
        return -1;
    }

    // 解压文件到临时文件
    QString tempFilePath;
    if (!decompressWithZlibStream(inputFile, tempFilePath)) {
        qDebug() << "解压失败";
        inputFile.close();
        return -1;
    }
    inputFile.close();

    QFile tempFile(tempFilePath);
    if (!tempFile.open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开临时解压文件:" << tempFilePath;
        return -1;
    }

    QDataStream in(&tempFile);
    in.setByteOrder(QDataStream::LittleEndian);

    QByteArray globalMetadata(METADATA_SIZE, '\0');
    if (in.readRawData(globalMetadata.data(), METADATA_SIZE) != METADATA_SIZE) {
        tempFile.close();
        tempFile.remove();
        return -1;
    }

    int fileCount = 0;
    while (!in.atEnd()) {
        QByteArray metadata(METADATA_SIZE, '\0');
        if (in.readRawData(metadata.data(), METADATA_SIZE) != METADATA_SIZE) {
            break;
        }

        QDataStream metaStream(&metadata, QIODevice::ReadOnly);
        metaStream.setByteOrder(QDataStream::LittleEndian);

        QByteArray filePathBytes;
        quint64 fileSize;
        quint32 expectedCrc32;
        metaStream >> filePathBytes >> fileSize >> expectedCrc32;

        quint64 paddingSize = calculatePadding(fileSize);
        in.skipRawData(fileSize + paddingSize);

        fileCount++;
    }

    tempFile.close();
    tempFile.remove();
    return fileCount;
}
