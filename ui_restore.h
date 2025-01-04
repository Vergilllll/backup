/********************************************************************************
** Form generated from reading UI file 'restore.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTORE_H
#define UI_RESTORE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_restore
{
public:
    QLineEdit *rst_res;
    QPushButton *res_button;
    QLineEdit *bu_res;
    QLabel *rst_label;
    QPushButton *rst;
    QLabel *res_label;
    QPushButton *rst_button;
    QLabel *title;
    QPushButton *return_main;
    QLabel *label_pic;
    QLabel *pwd_label;
    QLineEdit *password;
    QPushButton *pwd_button;

    void setupUi(QWidget *restore)
    {
        if (restore->objectName().isEmpty())
            restore->setObjectName(QString::fromUtf8("restore"));
        restore->resize(469, 323);
        rst_res = new QLineEdit(restore);
        rst_res->setObjectName(QString::fromUtf8("rst_res"));
        rst_res->setGeometry(QRect(90, 120, 281, 20));
        res_button = new QPushButton(restore);
        res_button->setObjectName(QString::fromUtf8("res_button"));
        res_button->setGeometry(QRect(380, 68, 80, 23));
        bu_res = new QLineEdit(restore);
        bu_res->setObjectName(QString::fromUtf8("bu_res"));
        bu_res->setGeometry(QRect(90, 70, 281, 21));
        rst_label = new QLabel(restore);
        rst_label->setObjectName(QString::fromUtf8("rst_label"));
        rst_label->setGeometry(QRect(20, 120, 61, 20));
        rst = new QPushButton(restore);
        rst->setObjectName(QString::fromUtf8("rst"));
        rst->setGeometry(QRect(180, 230, 91, 51));
        res_label = new QLabel(restore);
        res_label->setObjectName(QString::fromUtf8("res_label"));
        res_label->setGeometry(QRect(20, 70, 151, 20));
        res_label->setTextFormat(Qt::AutoText);
        res_label->setScaledContents(false);
        rst_button = new QPushButton(restore);
        rst_button->setObjectName(QString::fromUtf8("rst_button"));
        rst_button->setGeometry(QRect(380, 118, 80, 23));
        title = new QLabel(restore);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(180, 20, 161, 31));
        return_main = new QPushButton(restore);
        return_main->setObjectName(QString::fromUtf8("return_main"));
        return_main->setGeometry(QRect(20, 20, 80, 31));
        label_pic = new QLabel(restore);
        label_pic->setObjectName(QString::fromUtf8("label_pic"));
        label_pic->setGeometry(QRect(0, 0, 469, 323));
        label_pic->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/2.png);"));
        pwd_label = new QLabel(restore);
        pwd_label->setObjectName(QString::fromUtf8("pwd_label"));
        pwd_label->setGeometry(QRect(20, 170, 71, 21));
        password = new QLineEdit(restore);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(90, 170, 281, 20));
        pwd_button = new QPushButton(restore);
        pwd_button->setObjectName(QString::fromUtf8("pwd_button"));
        pwd_button->setGeometry(QRect(380, 168, 80, 24));
        label_pic->raise();
        rst_res->raise();
        res_button->raise();
        bu_res->raise();
        rst_label->raise();
        rst->raise();
        res_label->raise();
        rst_button->raise();
        title->raise();
        return_main->raise();
        pwd_label->raise();
        password->raise();
        pwd_button->raise();

        retranslateUi(restore);

        QMetaObject::connectSlotsByName(restore);
    } // setupUi

    void retranslateUi(QWidget *restore)
    {
        restore->setWindowTitle(QCoreApplication::translate("restore", "\346\225\260\346\215\256\346\201\242\345\244\215", nullptr));
        res_button->setText(QCoreApplication::translate("restore", "\346\265\217\350\247\210", nullptr));
        rst_label->setText(QCoreApplication::translate("restore", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\201\242\345\244\215\350\267\257\345\276\204</span></p></body></html>", nullptr));
        rst->setText(QCoreApplication::translate("restore", "\350\277\233\350\241\214\346\201\242\345\244\215", nullptr));
        res_label->setText(QCoreApplication::translate("restore", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\225\260\346\215\256\350\267\257\345\276\204</span></p></body></html>", nullptr));
        rst_button->setText(QCoreApplication::translate("restore", "\346\265\217\350\247\210", nullptr));
        title->setText(QCoreApplication::translate("restore", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:700; color:#ffffff;\">\346\225\260\346\215\256\346\201\242\345\244\215\345\212\237\350\203\275</span></p></body></html>", nullptr));
        return_main->setText(QCoreApplication::translate("restore", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", nullptr));
        label_pic->setText(QString());
        pwd_label->setText(QCoreApplication::translate("restore", "<html><head/><body><p><span style=\" color:#ffffff;\">\350\247\243\345\257\206\345\257\206\351\222\245</span></p></body></html>", nullptr));
        pwd_button->setText(QCoreApplication::translate("restore", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class restore: public Ui_restore {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTORE_H
