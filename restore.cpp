#include "restore.h"
#include "ui_restore.h"
#include <QDebug>


const int METADATA_SIZE = 512;

restore::restore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::restore)
{
    ui->setupUi(this);
    connect(this->ui->res_button,SIGNAL(clicked(bool)),this,SLOT(BrowseBuSource()));
    connect(this->ui->rst_button,SIGNAL(clicked(bool)),this,SLOT(BrowseRstSource()));
    connect(this->ui->rst,SIGNAL(clicked(bool)),this,SLOT(RestoreResources()));
    connect(this->ui->return_main,SIGNAL(clicked(bool)),this,SLOT(return_click()));
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
    // 创建 QFileInfo 对象
    QFileInfo fileInfo(filepath);

    // 创建 QDir 对象
    QDir directory(dir);

    // 获取相对路径
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
    };
}
void restore::BrowseRstSource(){
    QString path = QFileDialog::getExistingDirectory(this, tr("选择恢复目录"), ui->rst_res->text());
    if (!path.isEmpty()) {
        ui->rst_res->setText(path);
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
    // 读取大文件

    QFileInfo dirname = QFileInfo(inputFilePath);
    qDebug()<<"dirname: "<<dirname.fileName();
    QString dir;
    if(dirname.isDir()){
        dir = dirname.absoluteFilePath();
        qDebug()<<"dir: "<<dir;
    }
    while (!in.atEnd()) {
        // 读取元数据
        QByteArray metadata(METADATA_SIZE, '\0');
        in.readRawData(metadata.data(), METADATA_SIZE);

        QByteArray filePathBytes;
        quint64 fileSize;
        QDataStream metaStream(&metadata, QIODevice::ReadOnly);
        metaStream.setByteOrder(QDataStream::LittleEndian);
        metaStream >> filePathBytes;
        metaStream >> fileSize;
        //qDebug()<< "filesize: "<<fileSize;

        // 检查文件路径和文件大小的有效性
        if (filePathBytes.isEmpty() ) {
            qDebug() << "Invalid file entry: filePath is empty ";
            break; // 停止读取，因为后续数据可能是无效的
        }

       // qDebug() << "begin mkdir ";


        if (metaStream.status() != QDataStream::Ok) {
            qDebug() << "invalid metadata";
            break;
        }

        // 提取文件名并构建目标文件路径

        QFileInfo fileInfo(QString::fromUtf8(filePathBytes.trimmed()));
        // QString targetFile = restorePath + "/" + fileInfo.fileName();
        // 提取文件名并构建目标文件路径
         //QString filePath = QString::fromUtf8(filePathBytes.trimmed());
        QString targetFile;
        if(!dir.isEmpty()){
            QString relativePath = getRelativePath(fileInfo.absoluteFilePath(),dir);
            targetFile = restorePath + "/" + relativePath;
            qDebug()<<"relativePath: "<<relativePath;

        }
        else{
            targetFile = restorePath + "/" + fileInfo.fileName();
        }

        qDebug() << "Restoring file to:" << targetFile;


        QDir().mkpath(QFileInfo(targetFile).absolutePath());

        // 读取文件数据
        if (fileSize > 0) {
            QByteArray fileData(fileSize, 0);
            in.readRawData(fileData.data(), fileSize);

            if (in.status() != QDataStream::Ok) {
                qDebug() << "can't read raw data";
                return false;
            }

            //qDebug() << "filedata: "<<fileData;
            //qDebug() << "filedata.data: "<<fileData.data();
            // 恢复文件
            QFile outFile(targetFile);
            if (outFile.open(QIODevice::WriteOnly)) {
            outFile.write(fileData);
            outFile.close();
            } else {
              qDebug() << "can't open outfile:" << targetFile;
              return false;
            }
        }else {
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
                    QMessageBox::critical(this, tr("错误"), tr("恢复文件 %1 失败！").arg(backupPath));
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
