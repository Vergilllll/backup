/********************************************************************************
** Form generated from reading UI file 'extra.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRA_H
#define UI_EXTRA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_extra
{
public:
    QLabel *res_label;
    QLabel *path_label;
    QPushButton *browseBackupButton;
    QPushButton *return_main;
    QPushButton *confirmScheduledButton;
    QPushButton *browseDirButton;
    QLabel *title;
    QLabel *label;
    QLineEdit *backupPath;
    QLabel *timer_label;
    QPushButton *browseButton;
    QPushButton *startScheduledButton;
    QLineEdit *sourcePath;
    QPushButton *stopScheduledButton;
    QSpinBox *intervalSpinBox;
    QLabel *pwd_label;
    QLineEdit *password;
    QPushButton *pwd_confirm;
    QPushButton *confirmRealTimeButton;
    QPushButton *startRealTimeButton;
    QPushButton *stopRealTimeButton;
    QPushButton *fileFilter_button;
    QLabel *label_2;

    void setupUi(QWidget *extra)
    {
        if (extra->objectName().isEmpty())
            extra->setObjectName(QString::fromUtf8("extra"));
        extra->resize(481, 337);
        res_label = new QLabel(extra);
        res_label->setObjectName(QString::fromUtf8("res_label"));
        res_label->setGeometry(QRect(10, 80, 81, 21));
        path_label = new QLabel(extra);
        path_label->setObjectName(QString::fromUtf8("path_label"));
        path_label->setGeometry(QRect(7, 150, 61, 20));
        browseBackupButton = new QPushButton(extra);
        browseBackupButton->setObjectName(QString::fromUtf8("browseBackupButton"));
        browseBackupButton->setGeometry(QRect(370, 149, 80, 23));
        return_main = new QPushButton(extra);
        return_main->setObjectName(QString::fromUtf8("return_main"));
        return_main->setGeometry(QRect(10, 30, 80, 31));
        confirmScheduledButton = new QPushButton(extra);
        confirmScheduledButton->setObjectName(QString::fromUtf8("confirmScheduledButton"));
        confirmScheduledButton->setGeometry(QRect(330, 190, 101, 31));
        browseDirButton = new QPushButton(extra);
        browseDirButton->setObjectName(QString::fromUtf8("browseDirButton"));
        browseDirButton->setGeometry(QRect(70, 110, 80, 23));
        title = new QLabel(extra);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(160, 30, 191, 31));
        title->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(extra);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 481, 337));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/1.png);"));
        backupPath = new QLineEdit(extra);
        backupPath->setObjectName(QString::fromUtf8("backupPath"));
        backupPath->setGeometry(QRect(70, 150, 291, 20));
        timer_label = new QLabel(extra);
        timer_label->setObjectName(QString::fromUtf8("timer_label"));
        timer_label->setGeometry(QRect(10, 250, 101, 20));
        browseButton = new QPushButton(extra);
        browseButton->setObjectName(QString::fromUtf8("browseButton"));
        browseButton->setGeometry(QRect(370, 79, 80, 23));
        startScheduledButton = new QPushButton(extra);
        startScheduledButton->setObjectName(QString::fromUtf8("startScheduledButton"));
        startScheduledButton->setGeometry(QRect(20, 290, 111, 41));
        sourcePath = new QLineEdit(extra);
        sourcePath->setObjectName(QString::fromUtf8("sourcePath"));
        sourcePath->setGeometry(QRect(70, 80, 291, 21));
        stopScheduledButton = new QPushButton(extra);
        stopScheduledButton->setObjectName(QString::fromUtf8("stopScheduledButton"));
        stopScheduledButton->setGeometry(QRect(140, 290, 101, 41));
        intervalSpinBox = new QSpinBox(extra);
        intervalSpinBox->setObjectName(QString::fromUtf8("intervalSpinBox"));
        intervalSpinBox->setGeometry(QRect(110, 249, 101, 22));
        pwd_label = new QLabel(extra);
        pwd_label->setObjectName(QString::fromUtf8("pwd_label"));
        pwd_label->setGeometry(QRect(10, 209, 81, 21));
        password = new QLineEdit(extra);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(80, 210, 121, 20));
        pwd_confirm = new QPushButton(extra);
        pwd_confirm->setObjectName(QString::fromUtf8("pwd_confirm"));
        pwd_confirm->setGeometry(QRect(210, 207, 71, 26));
        confirmRealTimeButton = new QPushButton(extra);
        confirmRealTimeButton->setObjectName(QString::fromUtf8("confirmRealTimeButton"));
        confirmRealTimeButton->setGeometry(QRect(330, 230, 101, 31));
        startRealTimeButton = new QPushButton(extra);
        startRealTimeButton->setObjectName(QString::fromUtf8("startRealTimeButton"));
        startRealTimeButton->setGeometry(QRect(250, 290, 111, 41));
        stopRealTimeButton = new QPushButton(extra);
        stopRealTimeButton->setObjectName(QString::fromUtf8("stopRealTimeButton"));
        stopRealTimeButton->setGeometry(QRect(370, 290, 101, 41));
        fileFilter_button = new QPushButton(extra);
        fileFilter_button->setObjectName(QString::fromUtf8("fileFilter_button"));
        fileFilter_button->setGeometry(QRect(210, 110, 80, 23));
        label_2 = new QLabel(extra);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(290, 111, 121, 21));
        label->raise();
        res_label->raise();
        path_label->raise();
        browseBackupButton->raise();
        return_main->raise();
        confirmScheduledButton->raise();
        browseDirButton->raise();
        title->raise();
        backupPath->raise();
        timer_label->raise();
        browseButton->raise();
        startScheduledButton->raise();
        sourcePath->raise();
        stopScheduledButton->raise();
        intervalSpinBox->raise();
        pwd_label->raise();
        password->raise();
        pwd_confirm->raise();
        confirmRealTimeButton->raise();
        startRealTimeButton->raise();
        stopRealTimeButton->raise();
        fileFilter_button->raise();
        label_2->raise();

        retranslateUi(extra);

        QMetaObject::connectSlotsByName(extra);
    } // setupUi

    void retranslateUi(QWidget *extra)
    {
        extra->setWindowTitle(QCoreApplication::translate("extra", "\345\256\232\346\227\266/\345\256\236\346\227\266\345\244\207\344\273\275", nullptr));
        res_label->setText(QCoreApplication::translate("extra", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\272\220\350\267\257\345\276\204</span></p></body></html>", nullptr));
        path_label->setText(QCoreApplication::translate("extra", "<html><head/><body><p><span style=\" color:#ffffff;\">\345\244\207\344\273\275\350\267\257\345\276\204</span></p></body></html>", nullptr));
        browseBackupButton->setText(QCoreApplication::translate("extra", "\346\265\217\350\247\210", nullptr));
        return_main->setText(QCoreApplication::translate("extra", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
        confirmScheduledButton->setText(QCoreApplication::translate("extra", "\350\256\276\347\275\256\345\256\232\346\227\266\350\267\257\345\276\204", nullptr));
        browseDirButton->setText(QCoreApplication::translate("extra", "\346\265\217\350\247\210\347\233\256\345\275\225", nullptr));
        title->setText(QCoreApplication::translate("extra", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">\345\256\232\346\227\266/\345\256\236\346\227\266\345\244\207\344\273\275\345\212\237\350\203\275</span></p></body></html>", nullptr));
        label->setText(QString());
        timer_label->setText(QCoreApplication::translate("extra", "<html><head/><body><p><span style=\" color:#ffffff;\">\345\256\232\346\227\266\345\244\207\344\273\275\351\227\264\351\232\224</span></p></body></html>", nullptr));
        browseButton->setText(QCoreApplication::translate("extra", "\346\265\217\350\247\210\346\226\207\344\273\266", nullptr));
        startScheduledButton->setText(QCoreApplication::translate("extra", "\350\277\233\350\241\214\345\256\232\346\227\266\345\244\207\344\273\275", nullptr));
        stopScheduledButton->setText(QCoreApplication::translate("extra", "\345\201\234\346\255\242\345\256\232\346\227\266\345\244\207\344\273\275", nullptr));
        pwd_label->setText(QCoreApplication::translate("extra", "<html><head/><body><p><span style=\" color:#ffffff;\">\345\212\240\345\257\206\345\257\206\347\240\201</span></p></body></html>", nullptr));
        pwd_confirm->setText(QCoreApplication::translate("extra", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        confirmRealTimeButton->setText(QCoreApplication::translate("extra", "\350\256\276\347\275\256\345\256\236\346\227\266\350\267\257\345\276\204", nullptr));
        startRealTimeButton->setText(QCoreApplication::translate("extra", "\350\277\233\350\241\214\345\256\236\346\227\266\345\244\207\344\273\275", nullptr));
        stopRealTimeButton->setText(QCoreApplication::translate("extra", "\345\201\234\346\255\242\345\256\236\346\227\266\345\244\207\344\273\275", nullptr));
        fileFilter_button->setText(QCoreApplication::translate("extra", "\351\253\230\347\272\247\347\255\233\351\200\211", nullptr));
        label_2->setText(QCoreApplication::translate("extra", "<html><head/><body><p><span style=\" font-weight:700; color:#ffeef8;\">\357\274\210\345\205\210\351\200\211\346\213\251\347\233\256\345\275\225\357\274\211</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class extra: public Ui_extra {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRA_H
