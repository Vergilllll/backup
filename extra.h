#ifndef EXTRA_H
#define EXTRA_H

#include <QFileInfo>
#include <QFileSystemWatcher>
#include <QList>
#include <QMessageBox>
#include <QPair>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QVector>
#include <QWidget>
#include <QProgressDialog>
#include "filefilter.h"
#include <zlib.h>

namespace Ui {
class extra;
}

class extra : public QWidget
{
    Q_OBJECT

public:
    explicit extra(QWidget *parent = nullptr);
    ~extra();

protected:
    void closeEvent(QCloseEvent *event); // 声明 closeEvent 方法

private slots:
    void BrowseSource();
    void BrowseDirectory();
    void BrowseBackupPath();
    void ConfirmScheduledBackup();
    void ConfirmRealTimeBackup();
    void startScheduledBackup();
    void stopScheduledBackup();
    void startRealTimeBackup();
    void stopRealTimeBackup();
    void onTimeout();
    void showMainWindow();   // 返回主界面的槽函数
    void onWindowClose();    // 窗口关闭时的槽函数
    void closeApplication(); // 关闭软件的槽函数
    void SetPassWord();
    void onFileChanged(const QString &path);
    void onDirectoryChanged(const QString &path);
    void filter_click();
    void changePath(QString);
    void showExtra();

signals:
    void backToMain();
    void sendPath(QString);

private:
    Ui::extra *ui;
    Filefilter *filter;
    struct BackupEntry
    {
        QString sourcePath; // 源路径
        bool isDirectory;   // 是否为目录
        QString backupPath; // 备份路径
    };
    //QVector<BackupEntry> backupEntries;  // 存储所有备份条目
    QVector<BackupEntry> scheduledBackupEntries; // 存储定时备份条目
    QVector<BackupEntry> realTimeBackupEntries;  // 存储实时备份条目
    QTimer *timer;
    bool scheduledBackupRunning;
    bool realTimeBackupRunning;
    QString password;            // 密码
    QSystemTrayIcon *trayIcon;   // 系统托盘图标
    QAction *restoreAction;      // 返回主界面的菜单项
    QAction *quitAction;         // 关闭软件的菜单项
    QFileSystemWatcher *watcher; // 文件系统监视器

    void createTrayIcon(); // 创建系统托盘图标
    quint64 calculatePadding(quint64 fileSize);
    QByteArray xorEncryptDecrypt(const QByteArray &data, const QByteArray &key);
    void collectFiles(const QString &dirPath, QList<QFileInfo> &files);
    void performBackup(bool isScheduled);
    bool packFiles(const QList<QFileInfo> &files,
                   const QString &outputFilePath,bool isDirectoryPack);
    void clearAllText();
    void compressWithZlib(const QString &inputFilePath, const QString &outputFilePath);
    bool packFiles(const QList<QFileInfo> &files, const QStringList &relativePaths,
                          const QString &outputFilePath, const QString &rootDirectoryName,
                          QProgressDialog &progressDialog);
};

#endif // EXTRA_H
