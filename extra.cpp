#include "extra.h"
#include <QCloseEvent>
#include <QCryptographicHash>
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QMessageBox>
#include "ui_extra.h"


const int METADATA_SIZE = 512;

extra::extra(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::extra)
{
    ui->setupUi(this);

    filter = new Filefilter();
    filter->hide();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    scheduledBackupRunning = false;
    realTimeBackupRunning = false;
    ui->intervalSpinBox->setSuffix(" 分钟");

    connect(ui->browseButton, SIGNAL(clicked(bool)), this, SLOT(BrowseSource()));
    connect(ui->browseDirButton, SIGNAL(clicked(bool)), this, SLOT(BrowseDirectory()));
    connect(ui->browseBackupButton, SIGNAL(clicked(bool)), this, SLOT(BrowseBackupPath()));
    connect(ui->confirmScheduledButton, SIGNAL(clicked(bool)), this, SLOT(ConfirmScheduledBackup()));
    connect(ui->confirmRealTimeButton, SIGNAL(clicked(bool)), this, SLOT(ConfirmRealTimeBackup()));
    connect(ui->startScheduledButton, SIGNAL(clicked(bool)), this, SLOT(startScheduledBackup()));
    connect(ui->stopScheduledButton, SIGNAL(clicked(bool)), this, SLOT(stopScheduledBackup()));
    connect(ui->startRealTimeButton, SIGNAL(clicked(bool)), this, SLOT(startRealTimeBackup()));
    connect(ui->stopRealTimeButton, SIGNAL(clicked(bool)), this, SLOT(stopRealTimeBackup()));
    connect(ui->return_main, SIGNAL(clicked()), this, SLOT(showMainWindow()));
    connect(this->ui->pwd_confirm, SIGNAL(clicked(bool)), this, SLOT(SetPassWord()));
    connect(this->ui->fileFilter_button, SIGNAL(clicked(bool)), this, SLOT(filter_click()));
    connect(filter, SIGNAL(sendfilterdPath(QString)), this, SLOT(changePath(QString)));
    connect(filter, SIGNAL(return_to_extra()), this, SLOT(showExtra()));
    // 创建系统托盘图标
    createTrayIcon();

    // 初始化文件系统监视器
    watcher = new QFileSystemWatcher(this);
    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(onFileChanged(QString)));
    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(onDirectoryChanged(QString)));
}

extra::~extra()
{
    delete ui;
}

void extra::changePath(QString paths){
    ui->sourcePath->setText(paths);
}

void extra::showExtra(){
    this->show();
}

void extra::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/new/prefix1/icon.png")); // 设置托盘图标的图标
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

void extra::BrowseSource()
{
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

void extra::BrowseDirectory()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("选择目录"), ui->sourcePath->text());
    if (!path.isEmpty()) {
        ui->sourcePath->setText(path);
    }
}



void extra::BrowseBackupPath()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                                     tr("选择备份路径"),
                                                     ui->backupPath->text());
    if (!path.isEmpty()) {
        ui->backupPath->setText(path);
    }
}

void extra::ConfirmScheduledBackup()
{
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
    scheduledBackupEntries.append(entry);

    QMessageBox::information(this, tr("提示"), tr("定时备份已添加！"));
}

void extra::ConfirmRealTimeBackup()
{
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
    realTimeBackupEntries.append(entry);

    // 添加到文件系统监视器
    if (entry.isDirectory) {
        watcher->addPath(entry.sourcePath);
    } else {
        watcher->addPath(entry.sourcePath);
    }

    QMessageBox::information(this, tr("提示"), tr("实时备份已添加！"));
}

void extra::startScheduledBackup()
{
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

void extra::stopScheduledBackup()
{
    if (scheduledBackupRunning) {
        timer->stop();
        scheduledBackupRunning = false;
        QMessageBox::information(this, tr("提示"), tr("定时备份已停止！"));
    }
}

void extra::startRealTimeBackup()
{
    if (!realTimeBackupRunning) {
        if (this->password.isEmpty()) {
            QMessageBox::warning(this, tr("警告"), tr("请先设置密码！"));
            return;
        }

        realTimeBackupRunning = true;
        QMessageBox::information(this, tr("提示"), tr("实时备份已启动！"));
    }
}

void extra::stopRealTimeBackup()
{
    if (realTimeBackupRunning) {
        realTimeBackupRunning = false;
        QMessageBox::information(this, tr("提示"), tr("实时备份已停止！"));
    }
}

void extra::performBackup(bool isScheduled)
{
    QVector<BackupEntry> &entries = isScheduled ? scheduledBackupEntries : realTimeBackupEntries;
    QString successMessage = isScheduled ? tr("定时备份成功！") : tr("实时备份成功！");
    QString failureMessage = isScheduled ? tr("定时备份失败！") : tr("实时备份失败！");

    foreach (const BackupEntry &entry, entries) {
        if (entry.backupPath.isEmpty()) {
            QMessageBox::information(this, tr("提示"), tr("请选择备份路径！"));
            continue;
        }

        // 支持以 ';' 拼接的多个源路径
        QStringList sourcePaths = entry.sourcePath.split(";", Qt::SkipEmptyParts);
        if (sourcePaths.isEmpty()) {
            QMessageBox::warning(this, tr("警告"), tr("没有找到需要备份的路径。"));
            continue;
        }

        QList<QFileInfo> files;
        QStringList relativePaths; // 用于存储相对路径信息
        QString baseDirectory;    // 基准目录
        QString rootDirectoryName; // 用于存储备份的根目录名

        foreach (const QString &sourcePath, sourcePaths) {
            QFileInfo sourceInfo(sourcePath);

            if (sourceInfo.isDir()) {
                // 如果是目录，递归收集所有文件
                if (baseDirectory.isEmpty()) {
                    baseDirectory = sourceInfo.absolutePath(); // 设置第一个目录为基准目录
                }
                rootDirectoryName = sourceInfo.fileName(); // 设置根目录名
                collectFiles(sourcePath, files);
            } else if (sourceInfo.isFile()) {
                // 如果是单个文件，直接加入列表
                files.append(sourceInfo);
                if (baseDirectory.isEmpty()) {
                    baseDirectory = sourceInfo.absolutePath(); // 以第一个文件路径为基准目录
                }
            } else {
                QMessageBox::warning(this, tr("警告"), tr("跳过无效路径：%1").arg(sourcePath));
                continue;
            }
        }

        if (files.isEmpty()) {
            QMessageBox::warning(this, tr("警告"), tr("没有找到可备份的文件。"));
            continue;
        }

        // 生成文件的相对路径
        foreach (const QFileInfo &fileInfo, files) {
            QString relativePath = QDir(baseDirectory).relativeFilePath(fileInfo.absoluteFilePath());
            relativePaths.append(relativePath);
        }

        // 确定备份文件名
        QString outputFilePath;
        QString uniqueFileName;
        if (sourcePaths.size() == 1) { // 单个路径（文件或目录）
            QFileInfo singlePathInfo(sourcePaths.first());
            if (singlePathInfo.isDir()) {
                uniqueFileName = singlePathInfo.fileName() + "_backup";
                outputFilePath = entry.backupPath + "/" + uniqueFileName + "_" +
                                 QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + ".dat";
            } else {
                uniqueFileName = singlePathInfo.completeBaseName() + "_backup";
                outputFilePath = entry.backupPath + "/" + uniqueFileName + "_" +
                                 QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + ".dat";
            }
        } else { // 多个路径
            uniqueFileName = "multi_backup";
            outputFilePath = entry.backupPath + "/" + uniqueFileName + "_" +
                             QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + ".dat";
        }

        // 删除同名但时间较旧的备份文件
        QDir backupDir(entry.backupPath);
        QStringList filters = { uniqueFileName + "_*.dat.gz" }; // 查找同名的压缩备份文件
        QStringList backupFiles = backupDir.entryList(filters, QDir::Files, QDir::Time); // 按时间排序

        // 遍历同名文件，删除时间较旧的文件
        for (const QString &backupFile : backupFiles) {
            QString fullPath = entry.backupPath + "/" + backupFile;
            if (fullPath != outputFilePath + ".gz") { // 保留当前备份文件
                QFile::remove(fullPath);
            }
        }

        // 创建模态进度对话框
        QProgressDialog progressDialog(tr("备份进行中，请稍候..."), tr("取消"), 0, files.size(), this);
        progressDialog.setWindowModality(Qt::ApplicationModal);
        progressDialog.setWindowTitle(tr("备份进度"));
        progressDialog.setCancelButton(nullptr); // 禁止取消
        progressDialog.show();

        // 调用打包函数
        bool success = packFiles(files, relativePaths, outputFilePath, rootDirectoryName, progressDialog);

        // 压缩备份文件
        if (success) {
            QString compressedFilePath = outputFilePath + ".gz";
            compressWithZlib(outputFilePath, compressedFilePath);
            QFile::remove(outputFilePath); // 删除未压缩的临时备份文件
        }

        // 显示备份结果
        progressDialog.setValue(files.size()); // 更新进度
        if (success) {
            QMessageBox::information(this, tr("成功"), successMessage);
        } else {
            QMessageBox::critical(this, tr("错误"), failureMessage);
        }
    }
}

void extra::onTimeout()
{
    performBackup(true); // 调用定时备份
}

void extra::collectFiles(const QString &dirPath, QList<QFileInfo> &files)
{
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

QByteArray extra::xorEncryptDecrypt(const QByteArray &data, const QByteArray &key)
{
    QByteArray result(data.size(), 0);
    for (int i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

void extra::SetPassWord()
{
    password = ui->password->text();
    if (!this->password.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("密码已设置成功！"));
    } else {
        QMessageBox::warning(this, tr("警告"), tr("密码不能为空！"));
    }
}

quint64 extra::calculatePadding(quint64 fileSize)
{
    return (512 - (fileSize % 512)) % 512;
}

void extra::showMainWindow()
{
    this->hide();      // 隐藏当前窗口
    emit backToMain(); // 发送返回backup的信号
}

void extra::onWindowClose()
{
    this->hide();
    trayIcon->showMessage(tr("备份工具"),
                          tr("程序已最小化到托盘"),
                          QSystemTrayIcon::Information,
                          5000);
}

void extra::closeEvent(QCloseEvent *event)
{
    // 创建一个消息框，询问用户是否确认关闭软件
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("确认关闭"));
    msgBox.setText(tr("是否确认关闭软件？关闭后备份功能将停止"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    // 设置按钮文本
    QPushButton *yesButton = qobject_cast<QPushButton *>(msgBox.button(QMessageBox::Yes));
    yesButton->setText(tr("关闭"));
    QPushButton *noButton = qobject_cast<QPushButton *>(msgBox.button(QMessageBox::No));
    noButton->setText(tr("最小化到托盘"));

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        // 用户点击“关闭”，停止定时和实时备份功能，并关闭软件
        stopScheduledBackup();
        stopRealTimeBackup();
        event->accept(); // 接受关闭事件
    } else {
        // 用户点击“最小化到托盘”，隐藏窗口而不是关闭
        onWindowClose();
        event->ignore(); // 忽略关闭事件
    }
}

void extra::closeApplication()
{
    this->close(); // 关闭应用程序
}

void extra::onFileChanged(const QString &path)
{
    if (realTimeBackupRunning) {
        // 找到对应的备份条目并执行备份
        for (BackupEntry &entry : realTimeBackupEntries) {
            if (entry.sourcePath == path) {
                performBackup(false); // 调用实时备份
                break;
            }
        }
    }
}

void extra::onDirectoryChanged(const QString &path)
{
    if (realTimeBackupRunning) {
        // 找到对应的备份条目并执行备份
        for (BackupEntry &entry : realTimeBackupEntries) {
            if (entry.sourcePath == path) {
                performBackup(false); // 调用实时备份
                break;
            }
        }
    }
}

void extra::filter_click()
{
    if (!QDir(ui->sourcePath->text()).exists()||ui->sourcePath->text().isEmpty()) {
        QMessageBox::warning(this, "路径错误", "请选择正确的目录！");
        return;
    }
    connect(this, SIGNAL(sendPath(QString)), filter, SLOT(receivePath(QString)));
    emit sendPath(ui->sourcePath->text());
    this->hide();
    filter->show();
}

bool extra::packFiles(const QList<QFileInfo> &files, const QStringList &relativePaths,
                       const QString &outputFilePath, const QString &rootDirectoryName,
                       QProgressDialog &progressDialog)
{
    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, tr("错误"), tr("无法创建备份文件：%1").arg(outputFilePath));
        return false;
    }

    QDataStream out(&outputFile);
    out.setByteOrder(QDataStream::LittleEndian); // 设置字节序，确保一致性

    // 写入全局元数据
    QByteArray globalMetadata(METADATA_SIZE, '\0');
    QDataStream globalMetaStream(&globalMetadata, QIODevice::WriteOnly);
    globalMetaStream.setByteOrder(QDataStream::LittleEndian);

    // 写入目录名称到全局元数据（如果有）
    if (!rootDirectoryName.isEmpty()) {
        globalMetaStream << rootDirectoryName.toUtf8();
    }

    out.writeRawData(globalMetadata.constData(), METADATA_SIZE);

    // 逐个文件写入
    for (int i = 0; i < files.size(); ++i) {
        const QFileInfo &fileInfo = files.at(i);
        const QString &relativePath = relativePaths.at(i);

        QFile inputFile(fileInfo.absoluteFilePath());
        if (!inputFile.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("警告"), tr("无法读取文件：%1").arg(fileInfo.fileName()));
            continue;
        }

        QByteArray fileData = inputFile.readAll();
        inputFile.close();

        // 加密文件数据
        QByteArray encryptedData = xorEncryptDecrypt(fileData, password.toUtf8());

        // 计算元数据
        quint32 crc32 = qChecksum(fileData.constData(), fileData.size());
        quint64 compressedSize = encryptedData.size();
        quint64 fileSize = compressedSize;

        QByteArray metadata;
        QDataStream metaStream(&metadata, QIODevice::WriteOnly);
        metaStream.setByteOrder(QDataStream::LittleEndian);
        metaStream << relativePath.toUtf8(); // 写入相对路径
        metaStream << fileSize;
        metaStream << crc32;

        // 确保元数据大小固定
        if (metadata.size() < METADATA_SIZE) {
            metadata.append(QByteArray(METADATA_SIZE - metadata.size(), '\0'));
        } else if (metadata.size() > METADATA_SIZE) {
            metadata = metadata.left(METADATA_SIZE);
        }

        out.writeRawData(metadata.constData(), METADATA_SIZE);
        out.writeRawData(encryptedData.constData(), encryptedData.size());

        quint64 paddingSize = calculatePadding(compressedSize);
        if (paddingSize > 0) {
            QByteArray padding(paddingSize, '\0');
            out.writeRawData(padding.constData(), padding.size());
        }

        // 更新进度条
        progressDialog.setValue(i + 1);
        QCoreApplication::processEvents(); // 刷新 UI 事件循环
    }

    outputFile.close();
    return true;
}


void extra::clearAllText()
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

void extra::compressWithZlib(const QString &inputFilePath, const QString &outputFilePath)
{
    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open input file for reading.";
        return;
    }

    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Cannot open output file for writing.";
        return;
    }

    // 使用分块读取文件，避免一次性加载整个文件
    z_stream strm;
    memset(&strm, 0, sizeof(strm));
    deflateInit(&strm, Z_DEFAULT_COMPRESSION);

    QByteArray buffer;
    char tempBuffer[4096];  // 定义一个较小的缓冲区

    int flush;
    do {
        // 按块读取文件数据
        buffer = inputFile.read(4096);
        if (buffer.isEmpty()) {
            flush = Z_FINISH;
        } else {
            flush = Z_NO_FLUSH;
        }

        strm.avail_in = buffer.size();
        strm.next_in = reinterpret_cast<Bytef*>(buffer.data());

        do {
            strm.avail_out = sizeof(tempBuffer);
            strm.next_out = reinterpret_cast<Bytef*>(tempBuffer);

            deflate(&strm, flush);

            outputFile.write(tempBuffer, sizeof(tempBuffer) - strm.avail_out);

        } while (strm.avail_out == 0);

    } while (flush != Z_FINISH);

    deflateEnd(&strm);

    inputFile.close();
    outputFile.close();

    // 删除原始文件
    if (QFile::remove(inputFilePath)) {
        qDebug() << "Original file deleted successfully:" << inputFilePath;
    } else {
        qDebug() << "Failed to delete original file:" << inputFilePath;
    }

    qDebug() << "File compressed successfully with zlib!";
}
