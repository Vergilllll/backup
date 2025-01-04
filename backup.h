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

// 自定义哈希函数，用于 QChar 在 std::unordered_map 中的使用
struct QCharHash {
    std::size_t operator()(const QChar& key) const {
        return std::hash<ushort>()(key.unicode());
    }
};

// 哈夫曼树节点结构
struct HuffmanNode {
    QChar character;
    int frequency;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;

    HuffmanNode(QChar ch, int freq)
        : character(ch), frequency(freq), left(nullptr), right(nullptr) {}

    // 判断是否为叶子节点
    bool isLeaf() const {
        return !left && !right;
    }
};

// 比较器，用于优先队列（小顶堆）
struct CompareNode {
    bool operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) const {
        return a->frequency > b->frequency;
    }
};

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
