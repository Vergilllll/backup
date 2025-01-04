#ifndef FILEFILTER_H
#define FILEFILTER_H

#include <QDialog>

namespace Ui {
class Filefilter;
}

class Filefilter : public QDialog
{
    Q_OBJECT

public:
    explicit Filefilter(QWidget *parent = nullptr);
    ~Filefilter();

protected:
signals:
    void return_to_backup();
    void sendfilterdPath(QString);

private:
    Ui::Filefilter *ui;
    QStringList getFilePathsInDirectory(const QString& directoryPath);
    QStringList filterFiles(const QStringList& filePaths,
                            const QStringList& selectedTypes, const QStringList& selectedNames,
                            const QDateTime& startTime, const QDateTime& endTime,
                            qint64 minSize, qint64 maxSize);
    void clearAllText();

private slots:
    void filterFilesAndShowResult();
    void return_click();
    void receivePath(QString);
};

#endif // FILEFILTER_H
