#include "filefilter.h"
#include "qdir.h"
#include "ui_filefilter.h"
#include <QMessageBox>
#include "QDateTime"

Filefilter::Filefilter(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Filefilter)
{
    ui->setupUi(this);

    // 设置占位符文本
    ui->pathTextBox->setPlaceholderText("请输入目录路径，例如：C:/example/directory");
    ui->typesTextBox->setPlaceholderText("文件类型，例如：txt,docx,pdf");
    ui->namesTextBox->setPlaceholderText("文件名关键字，例如：example;test;sample");
    ui->startTimeTextBox->setPlaceholderText("开始时间，例如：2023-01-01 00:00:00");
    ui->endTimeTextBox->setPlaceholderText("结束时间，例如：2023-12-31 23:59:59");
    ui->minSizeTextBox->setPlaceholderText("0");
    ui->maxSizeTextBox->setPlaceholderText("100");

    connect(this->ui->filterButton, SIGNAL(clicked(bool)), this, SLOT(filterFilesAndShowResult()));
    connect(this->ui->returnButton, SIGNAL(clicked(bool)), this, SLOT(return_click()));
}

Filefilter::~Filefilter()
{
    delete ui;
}

void Filefilter::receivePath(QString dirPath){
    this->ui->pathTextBox->setText(dirPath);
}

QStringList Filefilter::getFilePathsInDirectory(const QString& directoryPath) {
    QStringList filePaths;
    QDir directory(directoryPath);
    QStringList fileNames = directory.entryList(QDir::Files);
    for (const QString& fileName : fileNames) {
        QString filePath = directoryPath + "/" + fileName;
        filePaths.append(filePath);
    }
    return filePaths;
}

QStringList Filefilter::filterFiles(const QStringList& filePaths,
                                    const QStringList& selectedTypes, const QStringList& selectedNames,
                                    const QDateTime& startTime, const QDateTime& endTime,
                                    qint64 minSize, qint64 maxSize) {
    QStringList filteredFiles;
    for (const QString& filePath : filePaths) {
        QFileInfo fileInfo(filePath);

        // 类型筛选
        if (!selectedTypes.isEmpty()) {
            QString fileExtension = fileInfo.suffix();
            bool typeMatched = false;
            for (const QString& type : selectedTypes) {
                if (type == fileExtension) {
                    typeMatched = true;
                    break;
                }
            }
            if (!typeMatched) {
                continue;
            }
        }

        // 名字筛选
        if (!selectedNames.isEmpty()) {
            QString fileName = fileInfo.fileName();
            bool nameMatched = false;
            for (const QString& name : selectedNames) {
                if (fileName.indexOf(name) != -1) {
                    nameMatched = true;
                    break;
                }
            }
            if (!nameMatched) {
                continue;
            }
        }
        // 时间筛选
        if (startTime.isValid() && endTime.isValid()) {
            QDateTime lastModified = fileInfo.lastModified();
            if (lastModified < startTime || lastModified > endTime) {
                continue;
            }
        }
        // 尺寸筛选（按 MB 计算）
        qint64 fileSizeMB = fileInfo.size() / (1024 * 1024); // 将字节转换为 MB
        if (fileSizeMB < minSize || fileSizeMB > maxSize) {
            continue;
        }
        filteredFiles.append(filePath);
    }
    return filteredFiles;
}

void Filefilter::filterFilesAndShowResult() {
    QString selectedPathFromUi = ui->pathTextBox->text().trimmed();
    if (!QDir(selectedPathFromUi).exists()) {
        QMessageBox::warning(this, "路径错误", "请选择正确的目录！");
        return;
    }

    QString selectedTypesStrFromUi = ui->typesTextBox->text().trimmed();
    QStringList selectedTypes;
    if (!selectedTypesStrFromUi.isEmpty()) {
        QStringList rawTypeList = selectedTypesStrFromUi.split(",");
        for (const QString& rawType : rawTypeList) {
            selectedTypes.append(rawType.trimmed());
        }
    }

    QString selectedNamesStrFromUi = ui->namesTextBox->text().trimmed();
    QStringList selectedNames;
    if (!selectedNamesStrFromUi.isEmpty()) {
        QStringList rawNameList = selectedNamesStrFromUi.split(";");
        for (const QString& rawName : rawNameList) {
            selectedNames.append(rawName.trimmed());
        }
    }

    QString startTimeStrFromUi = ui->startTimeTextBox->text().trimmed();
    QDateTime startTime;
    if (!startTimeStrFromUi.isEmpty()) {
        startTime = QDateTime::fromString(startTimeStrFromUi, "yyyy-MM-dd hh:mm:ss");
        if (!startTime.isValid()) {
            QMessageBox::warning(this, "时间格式错误", "开始时间格式输入有误，请重新输入！");
            return;
        }
    }

    QString endTimeStrFromUi = ui->endTimeTextBox->text().trimmed();
    QDateTime endTime;
    if (!endTimeStrFromUi.isEmpty()) {
        endTime = QDateTime::fromString(endTimeStrFromUi, "yyyy-MM-dd hh:mm:ss");
        if (!endTime.isValid()) {
            QMessageBox::warning(this, "时间格式错误", "结束时间格式输入有误，请重新输入！");
            return;
        }
    }

    qint64 minSize = 0;
    QString minSizeStrFromUi = ui->minSizeTextBox->text().trimmed();
    bool ok;
    if (!minSizeStrFromUi.isEmpty()) {
        minSize = minSizeStrFromUi.toLongLong(&ok);
        if (!ok || minSize < 0) {
            QMessageBox::warning(this, "尺寸错误", "最小尺寸输入有误，请重新输入！");
            return;
        }
    }

    qint64 maxSize = 1000;
    QString maxSizeStrFromUi = ui->maxSizeTextBox->text().trimmed();
    if (!maxSizeStrFromUi.isEmpty()) {
        maxSize = maxSizeStrFromUi.toLongLong(&ok);
        if (!ok || maxSize < 0) {
            QMessageBox::warning(this, "尺寸错误", "最大尺寸输入有误，请重新输入！");
            return;
        }
    }

    QStringList filePaths = getFilePathsInDirectory(selectedPathFromUi);
    QStringList filteredFiles = filterFiles(filePaths, selectedTypes, selectedNames,
                                            startTime, endTime, minSize, maxSize);

    // 显示筛选结果
    QString resultMsg = QString("筛选后共找到 %1 个文件，部分文件如下：\n").arg(filteredFiles.size());
    for (int i = 0; i < qMin(5, filteredFiles.size()); i++) {  // 显示前5个文件名，可调整
        resultMsg += filteredFiles.at(i) + "\n";
    }
    int buttonClicked = QMessageBox::question(this, "筛选结果", resultMsg, QMessageBox::Ok | QMessageBox::Cancel);
    if (buttonClicked == QMessageBox::Ok) {
        this->ui->pathTextBox->setText(filteredFiles.join(";"));
        emit sendfilterdPath(ui->pathTextBox->text());
        return_click();
    }
}

void Filefilter::return_click() {
    this->hide();
    emit return_to_backup();
}

void Filefilter::clearAllText()
{
    // 遍历当前窗口的所有子控件
    foreach (QObject *child, this->children()) {
        // 如果是 QLineEdit
        if (QLineEdit *lineEdit = qobject_cast<QLineEdit *>(child)) {
            lineEdit->clear();
        }
    }
}
