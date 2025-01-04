/********************************************************************************
** Form generated from reading UI file 'backup.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKUP_H
#define UI_BACKUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_backup
{
public:
    QPushButton *res_button;
    QLineEdit *origin_res;
    QLineEdit *bu_res;
    QLabel *res_label;
    QLabel *bu_label;
    QLabel *title;
    QPushButton *bu_button;
    QPushButton *bu;
    QLabel *label;
    QPushButton *return_main;
    QPushButton *directory_button;
    QPushButton *pwd_button;
    QLabel *password_label;
    QLineEdit *password;
    QPushButton *extra_button;
    QPushButton *fileFilter_button;
    QLabel *label_2;

    void setupUi(QWidget *backup)
    {
        if (backup->objectName().isEmpty())
            backup->setObjectName(QString::fromUtf8("backup"));
        backup->resize(469, 323);
        res_button = new QPushButton(backup);
        res_button->setObjectName(QString::fromUtf8("res_button"));
        res_button->setGeometry(QRect(380, 69, 80, 23));
        origin_res = new QLineEdit(backup);
        origin_res->setObjectName(QString::fromUtf8("origin_res"));
        origin_res->setGeometry(QRect(80, 70, 291, 21));
        bu_res = new QLineEdit(backup);
        bu_res->setObjectName(QString::fromUtf8("bu_res"));
        bu_res->setGeometry(QRect(80, 150, 291, 20));
        res_label = new QLabel(backup);
        res_label->setObjectName(QString::fromUtf8("res_label"));
        res_label->setGeometry(QRect(20, 70, 54, 12));
        bu_label = new QLabel(backup);
        bu_label->setObjectName(QString::fromUtf8("bu_label"));
        bu_label->setGeometry(QRect(13, 150, 61, 20));
        title = new QLabel(backup);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(190, 20, 131, 31));
        title->setStyleSheet(QString::fromUtf8(""));
        bu_button = new QPushButton(backup);
        bu_button->setObjectName(QString::fromUtf8("bu_button"));
        bu_button->setGeometry(QRect(380, 149, 71, 23));
        bu = new QPushButton(backup);
        bu->setObjectName(QString::fromUtf8("bu"));
        bu->setGeometry(QRect(80, 250, 101, 51));
        label = new QLabel(backup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 469, 323));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/1.png);"));
        return_main = new QPushButton(backup);
        return_main->setObjectName(QString::fromUtf8("return_main"));
        return_main->setGeometry(QRect(20, 20, 81, 31));
        directory_button = new QPushButton(backup);
        directory_button->setObjectName(QString::fromUtf8("directory_button"));
        directory_button->setGeometry(QRect(80, 110, 91, 23));
        pwd_button = new QPushButton(backup);
        pwd_button->setObjectName(QString::fromUtf8("pwd_button"));
        pwd_button->setGeometry(QRect(380, 199, 81, 22));
        password_label = new QLabel(backup);
        password_label->setObjectName(QString::fromUtf8("password_label"));
        password_label->setGeometry(QRect(10, 200, 61, 20));
        password = new QLineEdit(backup);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(80, 200, 291, 20));
        extra_button = new QPushButton(backup);
        extra_button->setObjectName(QString::fromUtf8("extra_button"));
        extra_button->setGeometry(QRect(270, 250, 101, 51));
        fileFilter_button = new QPushButton(backup);
        fileFilter_button->setObjectName(QString::fromUtf8("fileFilter_button"));
        fileFilter_button->setGeometry(QRect(230, 110, 91, 23));
        label_2 = new QLabel(backup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 111, 121, 21));
        label->raise();
        res_button->raise();
        origin_res->raise();
        bu_res->raise();
        res_label->raise();
        bu_label->raise();
        title->raise();
        bu_button->raise();
        bu->raise();
        return_main->raise();
        directory_button->raise();
        pwd_button->raise();
        password_label->raise();
        password->raise();
        extra_button->raise();
        fileFilter_button->raise();
        label_2->raise();

        retranslateUi(backup);

        QMetaObject::connectSlotsByName(backup);
    } // setupUi

    void retranslateUi(QWidget *backup)
    {
        backup->setWindowTitle(QCoreApplication::translate("backup", "\345\244\207\344\273\275", nullptr));
        res_button->setText(QCoreApplication::translate("backup", "\346\265\217\350\247\210\346\226\207\344\273\266", nullptr));
        res_label->setText(QCoreApplication::translate("backup", "\346\272\220\350\267\257\345\276\204", nullptr));
        bu_label->setText(QCoreApplication::translate("backup", "\345\244\207\344\273\275\350\267\257\345\276\204", nullptr));
        title->setText(QCoreApplication::translate("backup", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">\345\244\207\344\273\275\345\212\237\350\203\275</span></p></body></html>", nullptr));
        bu_button->setText(QCoreApplication::translate("backup", "\346\265\217\350\247\210", nullptr));
        bu->setText(QCoreApplication::translate("backup", "\350\277\233\350\241\214\345\244\207\344\273\275", nullptr));
        label->setText(QString());
        return_main->setText(QCoreApplication::translate("backup", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
        directory_button->setText(QCoreApplication::translate("backup", "\346\265\217\350\247\210\347\233\256\345\275\225", nullptr));
        pwd_button->setText(QCoreApplication::translate("backup", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        password_label->setText(QCoreApplication::translate("backup", "\345\212\240\345\257\206\345\257\206\347\240\201", nullptr));
        extra_button->setText(QCoreApplication::translate("backup", "\346\233\264\345\244\232\345\244\207\344\273\275\350\256\276\347\275\256", nullptr));
        fileFilter_button->setText(QCoreApplication::translate("backup", "\351\253\230\347\272\247\347\255\233\351\200\211", nullptr));
        label_2->setText(QCoreApplication::translate("backup", "<html><head/><body><p><span style=\" font-weight:700; color:#ffeef8;\">\357\274\210\345\205\210\351\200\211\346\213\251\347\233\256\345\275\225\357\274\211</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class backup: public Ui_backup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKUP_H
