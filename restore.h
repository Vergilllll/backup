#ifndef RESTORE_H
#define RESTORE_H

#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>
#include <zlib.h>
#include <QTemporaryFile>
#include <QProgressDialog>

namespace Ui {
class restore;
}

class restore : public QWidget
{
    Q_OBJECT

public:
    explicit restore(QWidget *parent = nullptr);
    ~restore();
    bool unpackFilesWithProgress(const QString &inputFilePath, const QString &restorePath, QProgressDialog &progressDialog);
    quint64 calculatePadding(quint64 size);
    QByteArray xorEncryptDecrypt(const QByteArray &data, const QByteArray &key);
    bool decompressWithZlibStream(QIODevice &inputFile, QString &tempFilePath);
    void clearAllText();
    int countFilesInBackup(const QString &inputFilePath);

private:
    Ui::restore *ui;
    QString password;
    bool checkPassword(const QByteArray &fileData, const QByteArray &decryptedData) const;

protected:
signals:
    void return_to_main();

private slots:
    void BrowseBuSource();
    void BrowseRstSource();
    void RestoreResources();
    void return_click();
    void setPassword();
};

#endif // RESTORE_H
