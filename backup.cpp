#include "backup.h"
#include <QCryptographicHash>
#include <QDebug>
#include <QDateTime>
#include <zlib.h>
#include "ui_backup.h"

const int METADATA_SIZE = 512;

int bu_oldWidth;
int bu_oldHeight;
QList<QObject *> bu_objList;
QMap<QObject *, QRect> bu_objMap;

backup::backup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::backup)
{
    ui->setupUi(this);

    bu_oldWidth = this->width();
    bu_oldHeight = this->height();
    bu_objList = this->children();
    foreach (QObject *obj, bu_objList) {
        bu_objMap.insert(obj, obj->property("geometry").toRect());
    }

    ex = new extra();
    ex->hide();
    filter = new Filefilter();
    filter->hide();

    connect(this->ui->res_button, SIGNAL(clicked(bool)), this, SLOT(BrowseSource()));
    connect(this->ui->directory_button, SIGNAL(clicked(bool)), this, SLOT(BrowseDirectory()));
    connect(this->ui->bu_button, SIGNAL(clicked(bool)), this, SLOT(BrowseBackup()));
    connect(this->ui->bu, SIGNAL(clicked(bool)), this, SLOT(BackupResources()));
    connect(this->ui->return_main, SIGNAL(clicked(bool)), this, SLOT(return_click()));
    connect(this->ui->pwd_button, SIGNAL(clicked(bool)), this, SLOT(SetPassWord()));
    connect(this->ui->extra_button, SIGNAL(clicked(bool)), this, SLOT(extra_click()));
    connect(this->ui->fileFilter_button, SIGNAL(clicked(bool)), this, SLOT(filter_click()));
    connect(ex, &extra::backToMain, this, &backup::return_click);
    connect(filter, SIGNAL(return_to_backup()), this, SLOT(showBackup()));
    connect(filter, SIGNAL(sendfilterdPath(QString)), this, SLOT(changePath(QString)));
    isDirectoryPack = false;
}

backup::~backup()
{
    delete ui;
}

// 计算填充字节数
quint64 calculatePadding(quint64 size)
{
    return (512 - (size % 512)) % 512;
}

// XOR 加密/解密函数
QByteArray backup::xorEncryptDecrypt(const QByteArray &data, const QByteArray &key)
{
    QByteArray result(data.size(), 0);
    for (int i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}

void backup::BrowseSource()
{
    QFileDialog dialog(this, tr("选择备份数据"), ui->origin_res->text(), tr("所有文件 (*)"));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec()) {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty()) {
            // 将文件路径转换为字符串，并在LineEdit中显示
            ui->origin_res->setText(files.join(";"));
            isDirectoryPack = false;
        }
    };
}


void backup::BrowseDirectory()
{
    QString path = QFileDialog::getExistingDirectory(this,
                                                     tr("选择备份数据目录"),
                                                     ui->origin_res->text());
    if (!path.isEmpty()) {
        ui->origin_res->setText(path);
        isDirectoryPack = true;
    }
}

void backup::BrowseBackup()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("选择备份路径"), ui->bu_res->text());
    if (!path.isEmpty()) {
        ui->bu_res->setText(path);
    }
}

void backup::SetPassWord()
{
    password = ui->password->text();
    if (!this->password.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("密码已设置成功！"));
    } else {
        QMessageBox::warning(this, tr("警告"), tr("密码不能为空！"));
    }
}

// 递归遍历目录并收集文件路径
void backup::collectFiles(const QString &dirPath, QList<QFileInfo> &files)
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

void backup::BackupResources()
{
    QString sourcePathsStr = ui->origin_res->text();
    QString backupPath = ui->bu_res->text();

    if (sourcePathsStr.isEmpty() || backupPath.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("请选择源路径和备份目录！"));
        return;
    }

    if (this->password.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("请先设置密码！"));
        return;
    }

    if (!QDir().mkpath(backupPath)) {
        QMessageBox::critical(this, tr("错误"), tr("无法创建备份目录：%1").arg(backupPath));
        return;
    }

    QStringList sourcePaths = sourcePathsStr.split(";", Qt::SkipEmptyParts);

    if (sourcePaths.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("没有找到需要备份的路径。"));
        return;
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
                baseDirectory = sourceInfo.absolutePath(); // 以第一个目录为基准目录
            }
            rootDirectoryName = sourceInfo.fileName(); // 设置根目录名
            collectFiles(sourcePath, files);
        } else if (sourceInfo.isFile()) {
            // 如果是单个文件，直接加入列表
            files.append(sourceInfo);
            if (baseDirectory.isEmpty()) {
                baseDirectory = sourceInfo.absolutePath(); // 以第一个文件的路径为基准目录
            }
        } else {
            QMessageBox::warning(this, tr("警告"), tr("跳过无效路径：%1").arg(sourcePath));
        }
    }

    if (files.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("没有找到可备份的文件。"));
        return;
    }

    // 生成文件的相对路径
    foreach (const QFileInfo &fileInfo, files) {
        QString relativePath = QDir(baseDirectory).relativeFilePath(fileInfo.absoluteFilePath());
        relativePaths.append(relativePath);
    }

    // 确定备份文件名
    QString outputFilePath;
    if (sourcePaths.size() == 1) { // 单个路径（文件/目录）
        QFileInfo singlePathInfo(sourcePaths.first());
        if (singlePathInfo.isDir()) {
            outputFilePath = backupPath + "/" + singlePathInfo.fileName() + "_backup.dat";
        } else {
            outputFilePath = backupPath + "/" + singlePathInfo.completeBaseName() + "_backup.dat";
        }
    } else { // 多个路径
        QString uniqueFileName = QString("multi_backup_%1.dat")
                                     .arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));
        outputFilePath = backupPath + "/" + uniqueFileName;
    }

    // 创建模态进度对话框
    QProgressDialog progressDialog(tr("备份进行中，请稍候..."), tr("取消"), 0, files.size(), this);
    progressDialog.setWindowModality(Qt::ApplicationModal);
    progressDialog.setWindowTitle(tr("备份进度"));
    progressDialog.setCancelButton(nullptr); // 不允许用户取消
    progressDialog.show();

    // 将根目录名称传递到 packFiles 函数
    bool success = packFiles(files, relativePaths, outputFilePath, rootDirectoryName, progressDialog);

    // 压缩备份文件
    if (success) {
        QString compressedFilePath = outputFilePath + ".gz";
        compressWithZlib(outputFilePath, compressedFilePath);
        QFile::remove(outputFilePath); // 删除未压缩的临时备份文件
    }

    // 显示备份结果
    progressDialog.setValue(files.size()); // 进度完成
    if (success) {
        QMessageBox::information(this, tr("成功"), tr("所有文件备份并压缩成功！"));
        clearAllText();
    } else {
        QMessageBox::critical(this, tr("错误"), tr("备份失败！"));
    }
}


void backup::return_click()
{
    emit return_to_main();
    this->hide();
}

void backup::extra_click()
{
    this->hide();
    ex->show();
}

void backup::showBackup(){
    this->show();
}

void backup::changePath(QString paths){
    ui->origin_res->setText(paths);
}

void backup::filter_click()
{
    if (!QDir(ui->origin_res->text()).exists()||ui->origin_res->text().isEmpty()) {
        QMessageBox::warning(this, "路径错误", "请选择正确的目录！");
        return;
    }
    connect(this, SIGNAL(sendPath(QString)), filter, SLOT(receivePath(QString)));
    emit sendPath(ui->origin_res->text());
    this->hide();
    filter->show();
}

void backup::resizeEvent(QResizeEvent *event)
{
    int Width = this->width();
    int Height = this->height();

    double scaleX = Width * 1.0 / bu_oldWidth * 1.0;
    double scaleY = Height * 1.0 / bu_oldHeight * 1.0;
    QMap<QObject *, QRect>::iterator iter;
    for (iter = bu_objMap.begin(); iter != bu_objMap.end(); iter++) {
        iter.key()->setProperty("geometry",
                                QRect(iter.value().x() * scaleX,
                                      iter.value().y() * scaleY,
                                      iter.value().width() * scaleX,
                                      iter.value().height() * scaleY));
    }
}

void backup::compressWithZlib(const QString &inputFilePath, const QString &outputFilePath)
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

bool backup::packFiles(const QList<QFileInfo> &files, const QStringList &relativePaths,
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


void backup::clearAllText()
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
