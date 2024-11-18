#ifndef RESTORE_H
#define RESTORE_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class restore;
}

class restore : public QWidget
{
    Q_OBJECT

public:
    explicit restore(QWidget *parent = nullptr);
    ~restore();
    bool unpackFiles(const QString &inputFilePath, const QString &restorePath);
    quint64 calculatePadding(quint64 size);
    QByteArray xorEncryptDecrypt(const QByteArray &data, const QByteArray &key);

private:
    Ui::restore *ui;
    QString password;
    bool checkPassword(const QByteArray &fileData, const QByteArray &decryptedData) const;

protected:
    signals:
    void return_to_main() ;

private slots:
    void BrowseBuSource();
    void BrowseRstSource();
    void RestoreResources();
    void return_click();
    void setPassword();
};

#endif // RESTORE_H
