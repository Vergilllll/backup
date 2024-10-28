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

private:
    Ui::restore *ui;

protected:
    signals:
    void return_to_main() ;

private slots:
    void BrowseBuSource();
    void BrowseRstSource();
    void RestoreResources();
    void return_click();
};

#endif // RESTORE_H
