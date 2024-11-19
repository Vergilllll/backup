#include "extra.h"
#include "ui_extra.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QDataStream>
#include <QCryptographicHash>
#include <QDebug>
#include <QMenu>
#include <QCloseEvent>


const int METADATA_SIZE = 512;


extra::extra(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::extra)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(performBackup()));

    scheduledBackupRunning = false;

    connect(ui->browseButton, SIGNAL(clicked(bool)), this, SLOT(BrowseSource()));
    connect(ui->browseDirButton, SIGNAL(clicked(bool)), this, SLOT(BrowseDirectory()));
    connect(ui->browseBackupButton, SIGNAL(clicked(bool)), this, SLOT(BrowseBackupPath()));
    connect(ui->confirmButton, SIGNAL(clicked(bool)), this, SLOT(ConfirmSelection()));
    connect(ui->startScheduledButton, SIGNAL(clicked(bool)), this, SLOT(startScheduledBackup()));
    connect(ui->stopScheduledButton, SIGNAL(clicked(bool)), this, SLOT(stopScheduledBackup()));
    connect(ui->return_main, SIGNAL(clicked()), this, SLOT(showMainWindow()));
    connect(this->ui->pwd_confirm,SIGNAL(clicked(bool)),this,SLOT(SetPassWord()));
    // 创建系统托盘图标
    createTrayIcon();
}

extra::~extra()
{
    delete ui;
}

void extra::createTrayIcon() {
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/new/prefix1/icon.png"));  // 设置托盘图标的图标
    trayIcon->show();

    restoreAction = new QAction(tr("返回界面"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showMainWindow()));

    quitAction = new QAction(tr("关闭软件"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(closeApplication()));

    QMenu *trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}


void extra::BrowseSource(){
    QFileDialog dialog(this, tr("选择备份数据"), ui->sourcePath->text(), tr("所有文件 (*)"));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec()) {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty()) {
            // 将文件路径转换为字符串，并在LineEdit中显示
            ui->sourcePath->setText(files.join(";"));
            //isDirectoryPack = false;
        }
    };
}

void extra::BrowseDirectory() {
    QString path = QFileDialog::getExistingDirectory(this, tr("选择目录"), ui->sourcePath->text());
    if (!path.isEmpty()) {
        ui->sourcePath->setText(path);
    }
}

void extra::BrowseBackupPath() {
    QString path = QFileDialog::getExistingDirectory(this, tr("选择备份路径"), ui->backupPath->text());
    if (!path.isEmpty()) {
        ui->backupPath->setText(path);
    }
}

void extra::ConfirmSelection() {
    QString sourcePath = ui->sourcePath->text();
    QString backupPath = ui->backupPath->text();

    if (sourcePath.isEmpty() || backupPath.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请选择文件或目录和备份路径！"));
        return;
    }

    QFileInfo fileInfo(sourcePath);
    BackupEntry entry;
    entry.sourcePath = sourcePath;
    entry.isDirectory = fileInfo.isDir();
    entry.backupPath = backupPath;
    backupEntries.append(entry);

    QMessageBox::information(this, tr("提示"), tr("选择已确认！"));
    ui->sourcePath->clear();
    ui->backupPath->clear();
}

void extra::startScheduledBackup() {
    if (!scheduledBackupRunning) {
        int interval = ui->intervalSpinBox->value();
        if (interval <= 0) {
            QMessageBox::critical(this, tr("错误"), tr("时间间隔必须大于0分钟！"));
            return;
        }

        if (this->password.isEmpty()) {
             QMessageBox::warning(this, tr("警告"), tr("请先设置密码！"));
             return;
         }

        interval *= 60 * 1000; // 将分钟转换为毫秒
        timer->start(interval);
        scheduledBackupRunning = true;
        QMessageBox::information(this, tr("提示"), tr("定时备份已启动！"));
    }
}

void extra::stopScheduledBackup() {
    if (scheduledBackupRunning) {
        timer->stop();
        scheduledBackupRunning = false;
        QMessageBox::information(this, tr("提示"), tr("定时备份已停止！"));
    }
}

void extra::performBackup() {
    foreach (const BackupEntry &entry, backupEntries) {
        if (entry.backupPath.isEmpty()) {
            QMessageBox::information(this, tr("提示"), tr("请选择备份路径！"));
            continue;
        }

        QList<QFileInfo> files;
        if (entry.isDirectory) {  // 是目录
            collectFiles(entry.sourcePath, files);
        } else {  // 是文件
            files.append(QFileInfo(entry.sourcePath));
        }

        if (files.isEmpty()) {
            QMessageBox::warning(this, tr("警告"), tr("没有找到可备份的文件。"));
            continue;
        }
        // 提取源文件或目录的名称
        QFileInfo sourceInfo(entry.sourcePath);
        QString sourceName = sourceInfo.fileName();

        // 生成备份文件名
        QString outputFileName = "backup_" + sourceName + "_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".dat";
        QString outputFilePath = entry.backupPath + "/" + outputFileName;

        if (packFiles(files, outputFilePath,entry.isDirectory)) {
            QMessageBox::information(this, tr("成功"), tr("备份成功！"));
        } else {
            QMessageBox::critical(this, tr("错误"), tr("备份失败！"));
        }
    }
}

void extra::collectFiles(const QString &dirPath, QList<QFileInfo> &files) {
    QDir dir(dirPath);
    QFileInfoList entries = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);

    for (const QFileInfo &entry : entries) {
        if (entry.isDir()) {
            collectFiles(entry.absoluteFilePath(), files);
        } else if (entry.isFile()) {
            files.append(entry);
        }
    }
}

bool extra::packFiles(const QList<QFileInfo> &files, const QString &outputFilePath, bool isDirectoryPack) {
    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&outputFile);
    out.setByteOrder(QDataStream::LittleEndian); // 设置字节序，确保一致性

    // 记录原始目录的根路径
    QString originalRootPath;
    if (isDirectoryPack && !files.isEmpty()) {
        originalRootPath = QFileInfo(files.first().absoluteFilePath()).absolutePath();
    }

    // 写入全局元数据
    QByteArray globalMetadata(METADATA_SIZE, '\0');
    QDataStream globalMetaStream(&globalMetadata, QIODevice::WriteOnly);
    globalMetaStream.setByteOrder(QDataStream::LittleEndian);
    globalMetaStream << isDirectoryPack;
    if (isDirectoryPack) {
        QByteArray originalRootPathBytes = originalRootPath.toUtf8();
        globalMetaStream << originalRootPathBytes;
    }
    out.writeRawData(globalMetadata.constData(), METADATA_SIZE);

    foreach (const QFileInfo &fileInfo, files) {
        if (fileInfo.isFile()) {
            // 文件元数据
            QByteArray filePathBytes = fileInfo.absoluteFilePath().toUtf8();
            quint64 fileSize = fileInfo.size();

            // 计算文件的 CRC32 校验值
            QFile inputFile(fileInfo.absoluteFilePath());
            quint32 crc32;
            if (inputFile.open(QIODevice::ReadOnly)) {
                QByteArray fileData = inputFile.readAll();
                crc32 = qChecksum(fileData.constData(), fileData.size());
                inputFile.close();
            } else {
                qDebug() << "can't open input file:" << fileInfo.absoluteFilePath();
                return false;
            }

            // 确保元数据部分为512字节
            QByteArray metadata(METADATA_SIZE, '\0');
            QDataStream metaStream(&metadata, QIODevice::WriteOnly);
            metaStream.setByteOrder(QDataStream::LittleEndian);
            metaStream << filePathBytes;
            metaStream << fileSize;
            metaStream << crc32; // 添加 CRC32 校验值

            // 写入元数据
            out.writeRawData(metadata.constData(), METADATA_SIZE);

            // 读取文件数据并加密
            if (inputFile.open(QIODevice::ReadOnly)) {
                QByteArray fileData = inputFile.readAll();
                QByteArray encryptedData = xorEncryptDecrypt(fileData, password.toUtf8());
                out.writeRawData(encryptedData.constData(), encryptedData.size());
                inputFile.close();
            } else {
                qDebug() << "can't open input file:" << fileInfo.absoluteFilePath();
                return false;
            }

            // 写入填充
            quint64 paddingSize = calculatePadding(fileSize);
            QByteArray padding(paddingSize, '\0');
            out.writeRawData(padding.constData(), padding.size());
        }
    }

    outputFile.close();
    return true;
}

QByteArray extra::xorEncryptDecrypt(const QByteArray &data, const QByteArray &key) {
    QByteArray result(data.size(), 0);
    for (int i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

void extra::SetPassWord() {
    password = ui->password->text();
    if (!this->password.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("密码已设置成功！"));
    } else {
        QMessageBox::warning(this, tr("警告"), tr("密码不能为空！"));
    }
}


quint64 extra::calculatePadding(quint64 fileSize) {
    return (512 - (fileSize % 512)) % 512;
}

void extra::showMainWindow() {
    this->hide();  // 隐藏当前窗口
    emit backToMain();  // 发送返回backup的信号
}

void extra::onWindowClose() {
    this->hide();
    trayIcon->showMessage(tr("备份工具"), tr("程序已最小化到托盘"), QSystemTrayIcon::Information, 5000);
}

void extra::closeEvent(QCloseEvent *event) {
    onWindowClose();
    event->ignore();  // 忽略关闭事件，使窗口隐藏而不是关闭
}

void extra::closeApplication() {
    this->close();  // 关闭应用程序
}
