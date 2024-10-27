#include "backup.h"
#include "ui_backup.h"


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
    connect(this->ui->bu_button,SIGNAL(clicked(bool)),this,SLOT(BrowseBackup()));
    connect(this->ui->bu,SIGNAL(clicked(bool)),this,SLOT(BackupResources()));
    connect(this->ui->return_main,SIGNAL(clicked(bool)),this,SLOT(return_click()));
}

backup::~backup()
{
    delete ui;
}

void backup::BrowseSource(){
    QFileDialog dialog(this, tr("选择备份数据"), ui->origin_res->text(), tr("所有文件 (*)"));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec()) {
        QStringList files = dialog.selectedFiles();
        if (!files.isEmpty()) {
            // 将文件路径转换为字符串，并在LineEdit中显示
            ui->origin_res->setText(files.join(";"));
        }
    };
}

void backup::BrowseBackup(){
    QString path = QFileDialog::getExistingDirectory(this, tr("选择备份目录"), ui->bu_res->text());
    if (!path.isEmpty()) {
        ui->bu_res->setText(path);
    }
}

void backup::BackupResources(){
    QString sourcePathsStr = ui->origin_res->text();
    QString backupPath = ui->bu_res->text();

    if (sourcePathsStr.isEmpty() || backupPath.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("请选择源文件和备份目录！"));
        return;
    }

    if (!QDir().mkpath(backupPath)) {
        QMessageBox::critical(this, tr("错误"), tr("无法创建备份目录：%1").arg(backupPath));
        return;
    }

    QStringList sourcePaths = sourcePathsStr.split(";");
    bool success = true;

    foreach (const QString &sourcePath, sourcePaths) {
        QFileInfo fileInfo(sourcePath);
        if (fileInfo.isFile()) {
            // 处理单个文件
            QString backupFile = backupPath + "/" + fileInfo.fileName();
            if (!QFile::copy(sourcePath, backupFile)) {
                success = false;
                break;
            }
        } else {
            QMessageBox::warning(this, tr("警告"), tr("跳过非文件项：%1").arg(sourcePath));
        }
    }

    if (success) {
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
