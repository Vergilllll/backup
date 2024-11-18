#ifndef BACKUP_H
#define BACKUP_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
namespace Ui {
class backup;
}

class backup : public QWidget
{
    Q_OBJECT

public:
    explicit backup(QWidget *parent = nullptr);
    ~backup();
    void resizeEvent(QResizeEvent *event);
    void collectFiles(const QString &dirPath, QList<QFileInfo> &files);
    bool packFiles(const QList<QFileInfo> &files, const QString &outputFilePath);
    QByteArray xorEncryptDecrypt(const QByteArray &data, const QByteArray &key);

protected:
    signals:
    void return_to_main() ;

private:
    Ui::backup *ui;
    bool isDirectoryPack;
    QString password;

private slots:
    void BrowseSource();
    void BrowseDirectory();
    void BrowseBackup();
    void BackupResources();
    void return_click();
    void SetPassWord();
};

#endif // BACKUP_H
