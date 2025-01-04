#ifndef BACKUP_H
#define BACKUP_H

#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include "extra.h"
#include "filefilter.h"
#include <QProgressDialog>

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
    bool packFiles(const QList<QFileInfo> &files, const QStringList &relativePaths,
                           const QString &outputFilePath, const QString &rootDirectoryName,
                           QProgressDialog &progressDialog);
    QByteArray xorEncryptDecrypt(const QByteArray &data, const QByteArray &key);
    void compressWithZlib(const QString &inputFilePath, const QString &outputFilePath);
    void clearAllText();

protected:
signals:
    void return_to_main();
    void sendPath(QString);

private:
    Ui::backup *ui;
    extra *ex;
    Filefilter *filter;
    bool isDirectoryPack;
    QString password;

private slots:
    void BrowseSource();
    void BrowseDirectory();
    void BrowseBackup();
    void BackupResources();
    void return_click();
    void extra_click();
    void SetPassWord();
    void filter_click();
    void showBackup();
    void changePath(QString);
};


#endif // BACKUP_H
