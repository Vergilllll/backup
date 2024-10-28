#include "backup.h"
#include "ui_backup.h"
#include <QDebug>


const int METADATA_SIZE = 512;

int bu_oldWidth;
int bu_oldHeight;
QList<QObject*> bu_objList;
QMap<QObject*, QRect> bu_objMap;

backup::backup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::backup)
{
    ui->setupUi(this);

    bu_oldWidth=this->width();
    bu_oldHeight=this->height();
    bu_objList = this->children();
     foreach (QObject* obj, bu_objList)
      {
          bu_objMap.insert(obj, obj->property("geometry").toRect());
      }

    connect(this->ui->res_button,SIGNAL(clicked(bool)),this,SLOT(BrowseSource()));
    connect(this->ui->directory_button,SIGNAL(clicked(bool)),this,SLOT(BrowseDirectory()));
    connect(this->ui->bu_button,SIGNAL(clicked(bool)),this,SLOT(BrowseBackup()));
    connect(this->ui->bu,SIGNAL(clicked(bool)),this,SLOT(BackupResources()));
    connect(this->ui->return_main,SIGNAL(clicked(bool)),this,SLOT(return_click()));

    isDirectoryPack = false;
}

backup::~backup()
{
    delete ui;
}

// 计算填充字节数
quint64 calculatePadding(quint64 size) {
    return (512 - (size % 512)) % 512;
}


void backup::BrowseSource(){
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

void backup::BrowseDirectory(){
    QString path = QFileDialog::getExistingDirectory(this, tr("选择备份数据目录"), ui->origin_res->text());
    if (!path.isEmpty()) {
        ui->origin_res->setText(path);
        isDirectoryPack = true;
    }
}

void backup::BrowseBackup(){
    QString path = QFileDialog::getExistingDirectory(this, tr("选择备份路径"), ui->bu_res->text());
    if (!path.isEmpty()) {
        ui->bu_res->setText(path);
    }
}



// 递归遍历目录并收集文件路径
void backup::collectFiles(const QString &dirPath, QList<QFileInfo> &files) {
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

bool backup::packFiles(const QList<QFileInfo> &files, const QString &outputFilePath) {
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
            //qDebug() << "filesize: " << fileInfo.size();

            // 写入元数据
            out.writeRawData(metadata.constData(), METADATA_SIZE);

            // 读取文件数据并写入

            if (inputFile.open(QIODevice::ReadOnly)) {
                QByteArray fileData = inputFile.readAll();
                out.writeRawData(fileData.constData(), fileData.size());
                //qDebug() << "fileData: " << fileData;
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


void backup::BackupResources(){
    QString sourcePathsStr = ui->origin_res->text();
        QString backupPath = ui->bu_res->text();

        if (sourcePathsStr.isEmpty() || backupPath.isEmpty()) {
            QMessageBox::information(this, tr("提示"), tr("请选择源路径和备份目录！"));
            return;
        }

        if (!QDir().mkpath(backupPath)) {
            QMessageBox::critical(this, tr("错误"), tr("无法创建备份目录：%1").arg(backupPath));
            return;
        }

        QStringList sourcePaths = sourcePathsStr.split(";", QString::SkipEmptyParts);

        QList<QFileInfo> files;
        foreach (const QString &sourcePath, sourcePaths) {
            QFileInfo fileInfo(sourcePath);
            //遍历目录下所有文件，空目录忽略
            if (fileInfo.isDir()) {
                collectFiles(sourcePath, files);
            } else if (fileInfo.isFile()) {
                files.append(fileInfo);
            } else {
                QMessageBox::warning(this, tr("警告"), tr("跳过无效项：%1").arg(sourcePath));
            }
        }

        if (files.isEmpty()) {
            QMessageBox::warning(this, tr("警告"), tr("没有找到可备份的文件。"));
            return;
        }

        // 生成输出文件路径
        QString outputFileName;
        if (sourcePaths.size() == 1) {
            QFileInfo sourceInfo(sourcePaths.first());
            if (sourceInfo.isDir()) {
                outputFileName = sourceInfo.fileName() + "_backup.dat";
            } else {
                outputFileName = sourceInfo.completeBaseName() + "_backup.dat";
            }
        } else {
            outputFileName = "multi_backup.dat"; // 如果有多个源路径，使用默认名称
        }

        QString outputFilePath = backupPath + "/" + outputFileName;
        if (packFiles(files, outputFilePath)) {
            QMessageBox::information(this, tr("成功"), tr("备份成功！"));
        } else {
            QMessageBox::critical(this, tr("错误"), tr("备份失败！"));
        }
}


void backup::return_click(){
    emit return_to_main();
    this->hide();
}


void backup::resizeEvent(QResizeEvent *event)
{
    int Width = this->width();
    int Height = this->height();

    double  scaleX = Width*1.0/bu_oldWidth*1.0;
    double  scaleY = Height*1.0/bu_oldHeight*1.0;
    QMap<QObject*, QRect>::iterator iter;
       for (iter = bu_objMap.begin(); iter != bu_objMap.end(); iter++)
       {
           iter.key()->setProperty("geometry", QRect(iter.value().x() * scaleX, iter.value().y() * scaleY,
                                                     iter.value().width() * scaleX, iter.value().height() * scaleY));
       }
}
