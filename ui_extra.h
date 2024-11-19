/********************************************************************************
** Form generated from reading UI file 'extra.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXTRA_H
#define UI_EXTRA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
    QPushButton *confirmButton;
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

    void setupUi(QWidget *extra)
    {
        if (extra->objectName().isEmpty())
            extra->setObjectName(QStringLiteral("extra"));
        extra->resize(481, 337);
        res_label = new QLabel(extra);
        res_label->setObjectName(QStringLiteral("res_label"));
        res_label->setGeometry(QRect(10, 80, 54, 12));
        path_label = new QLabel(extra);
        path_label->setObjectName(QStringLiteral("path_label"));
        path_label->setGeometry(QRect(10, 130, 61, 20));
        browseBackupButton = new QPushButton(extra);
        browseBackupButton->setObjectName(QStringLiteral("browseBackupButton"));
        browseBackupButton->setGeometry(QRect(370, 130, 80, 20));
        return_main = new QPushButton(extra);
        return_main->setObjectName(QStringLiteral("return_main"));
        return_main->setGeometry(QRect(10, 240, 80, 31));
        confirmButton = new QPushButton(extra);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));
        confirmButton->setGeometry(QRect(360, 160, 101, 31));
        browseDirButton = new QPushButton(extra);
        browseDirButton->setObjectName(QStringLiteral("browseDirButton"));
        browseDirButton->setGeometry(QRect(370, 100, 80, 20));
        title = new QLabel(extra);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(180, 20, 111, 20));
        title->setStyleSheet(QStringLiteral(""));
        label = new QLabel(extra);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 469, 323));
        label->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/1.png);"));
        backupPath = new QLineEdit(extra);
        backupPath->setObjectName(QStringLiteral("backupPath"));
        backupPath->setGeometry(QRect(70, 130, 291, 20));
        timer_label = new QLabel(extra);
        timer_label->setObjectName(QStringLiteral("timer_label"));
        timer_label->setGeometry(QRect(10, 190, 81, 20));
        browseButton = new QPushButton(extra);
        browseButton->setObjectName(QStringLiteral("browseButton"));
        browseButton->setGeometry(QRect(370, 80, 80, 20));
        startScheduledButton = new QPushButton(extra);
        startScheduledButton->setObjectName(QStringLiteral("startScheduledButton"));
        startScheduledButton->setGeometry(QRect(180, 190, 81, 41));
        sourcePath = new QLineEdit(extra);
        sourcePath->setObjectName(QStringLiteral("sourcePath"));
        sourcePath->setGeometry(QRect(70, 80, 291, 21));
        stopScheduledButton = new QPushButton(extra);
        stopScheduledButton->setObjectName(QStringLiteral("stopScheduledButton"));
        stopScheduledButton->setGeometry(QRect(270, 190, 81, 41));
        intervalSpinBox = new QSpinBox(extra);
        intervalSpinBox->setObjectName(QStringLiteral("intervalSpinBox"));
        intervalSpinBox->setGeometry(QRect(100, 190, 71, 22));
        pwd_label = new QLabel(extra);
        pwd_label->setObjectName(QStringLiteral("pwd_label"));
        pwd_label->setGeometry(QRect(10, 160, 54, 12));
        password = new QLineEdit(extra);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(70, 160, 141, 20));
        pwd_confirm = new QPushButton(extra);
        pwd_confirm->setObjectName(QStringLiteral("pwd_confirm"));
        pwd_confirm->setGeometry(QRect(220, 160, 81, 20));
        label->raise();
        res_label->raise();
        path_label->raise();
        browseBackupButton->raise();
        return_main->raise();
        confirmButton->raise();
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

        retranslateUi(extra);

        QMetaObject::connectSlotsByName(extra);
    } // setupUi

    void retranslateUi(QWidget *extra)
    {
        extra->setWindowTitle(QApplication::translate("extra", "Form", Q_NULLPTR));
        res_label->setText(QApplication::translate("extra", "\346\272\220\350\267\257\345\276\204", Q_NULLPTR));
        path_label->setText(QApplication::translate("extra", "\345\244\207\344\273\275\350\267\257\345\276\204", Q_NULLPTR));
        browseBackupButton->setText(QApplication::translate("extra", "\346\265\217\350\247\210", Q_NULLPTR));
        return_main->setText(QApplication::translate("extra", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("extra", "\347\241\256\350\256\244\350\267\257\345\276\204", Q_NULLPTR));
        browseDirButton->setText(QApplication::translate("extra", "\346\265\217\350\247\210\347\233\256\345\275\225", Q_NULLPTR));
        title->setText(QApplication::translate("extra", "\345\256\232\346\227\266/\345\256\236\346\227\266\345\244\207\344\273\275\345\212\237\350\203\275", Q_NULLPTR));
        label->setText(QString());
        timer_label->setText(QApplication::translate("extra", "\345\256\232\346\227\266\345\244\207\344\273\275\351\227\264\351\232\224", Q_NULLPTR));
        browseButton->setText(QApplication::translate("extra", "\346\265\217\350\247\210\346\226\207\344\273\266", Q_NULLPTR));
        startScheduledButton->setText(QApplication::translate("extra", "\350\277\233\350\241\214\345\256\232\346\227\266\345\244\207\344\273\275", Q_NULLPTR));
        stopScheduledButton->setText(QApplication::translate("extra", "\345\201\234\346\255\242\345\256\232\346\227\266\345\244\207\344\273\275", Q_NULLPTR));
        pwd_label->setText(QApplication::translate("extra", "\345\212\240\345\257\206\345\257\206\347\240\201", Q_NULLPTR));
        pwd_confirm->setText(QApplication::translate("extra", "\347\241\256\350\256\244\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class extra: public Ui_extra {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXTRA_H
