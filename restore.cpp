#include "restore.h"
#include "ui_restore.h"

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
void restore::RestoreResources(){
    QString backupPath = ui->bu_res->text();
        QString restorePath = ui->rst_res->text();
        if (backupPath.isEmpty() || restorePath.isEmpty()) {
            QMessageBox::information(this, tr("提示"), tr("请选择备份文件和恢复位置！"));
            return;
        }

        QFileInfo fileInfo(backupPath);
        if (fileInfo.isFile()) {
            // 处理单个文件
            QString restoreFile = restorePath + "/" + fileInfo.fileName();
            if (QFile::copy(backupPath, restoreFile)) {
                QMessageBox::information(this, tr("成功"), tr("恢复成功！"));
            } else {
                QMessageBox::critical(this, tr("错误"), tr("恢复失败！"));
            }
        } else {
            QMessageBox::warning(this, tr("警告"), tr("备份路径不是一个有效的文件：%1").arg(backupPath));
        }
}

void restore::return_click(){
    emit return_to_main();
    this->hide();
}
