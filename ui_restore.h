/********************************************************************************
** Form generated from reading UI file 'restore.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTORE_H
#define UI_RESTORE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            restore->setObjectName(QStringLiteral("restore"));
        restore->resize(469, 323);
        rst_res = new QLineEdit(restore);
        rst_res->setObjectName(QStringLiteral("rst_res"));
        rst_res->setGeometry(QRect(80, 120, 291, 20));
        res_button = new QPushButton(restore);
        res_button->setObjectName(QStringLiteral("res_button"));
        res_button->setGeometry(QRect(380, 70, 80, 20));
        bu_res = new QLineEdit(restore);
        bu_res->setObjectName(QStringLiteral("bu_res"));
        bu_res->setGeometry(QRect(80, 70, 291, 21));
        rst_label = new QLabel(restore);
        rst_label->setObjectName(QStringLiteral("rst_label"));
        rst_label->setGeometry(QRect(20, 120, 61, 20));
        rst = new QPushButton(restore);
        rst->setObjectName(QStringLiteral("rst"));
        rst->setGeometry(QRect(310, 240, 91, 51));
        res_label = new QLabel(restore);
        res_label->setObjectName(QStringLiteral("res_label"));
        res_label->setGeometry(QRect(20, 70, 151, 20));
        rst_button = new QPushButton(restore);
        rst_button->setObjectName(QStringLiteral("rst_button"));
        rst_button->setGeometry(QRect(380, 120, 80, 20));
        title = new QLabel(restore);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(160, 20, 131, 20));
        return_main = new QPushButton(restore);
        return_main->setObjectName(QStringLiteral("return_main"));
        return_main->setGeometry(QRect(20, 220, 80, 31));
        label_pic = new QLabel(restore);
        label_pic->setObjectName(QStringLiteral("label_pic"));
        label_pic->setGeometry(QRect(0, 0, 469, 323));
        label_pic->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/2.png);"));
        pwd_label = new QLabel(restore);
        pwd_label->setObjectName(QStringLiteral("pwd_label"));
        pwd_label->setGeometry(QRect(20, 170, 54, 12));
        password = new QLineEdit(restore);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(80, 170, 291, 20));
        pwd_button = new QPushButton(restore);
        pwd_button->setObjectName(QStringLiteral("pwd_button"));
        pwd_button->setGeometry(QRect(380, 170, 80, 20));
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
        restore->setWindowTitle(QApplication::translate("restore", "Form", Q_NULLPTR));
        res_button->setText(QApplication::translate("restore", "\346\265\217\350\247\210", Q_NULLPTR));
        rst_label->setText(QApplication::translate("restore", "\346\201\242\345\244\215\350\267\257\345\276\204", Q_NULLPTR));
        rst->setText(QApplication::translate("restore", "\350\277\233\350\241\214\346\201\242\345\244\215", Q_NULLPTR));
        res_label->setText(QApplication::translate("restore", "\346\225\260\346\215\256\350\267\257\345\276\204", Q_NULLPTR));
        rst_button->setText(QApplication::translate("restore", "\346\265\217\350\247\210", Q_NULLPTR));
        title->setText(QApplication::translate("restore", "\346\225\260\346\215\256\346\201\242\345\244\215\345\212\237\350\203\275", Q_NULLPTR));
        return_main->setText(QApplication::translate("restore", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", Q_NULLPTR));
        label_pic->setText(QString());
        pwd_label->setText(QApplication::translate("restore", "\350\247\243\345\257\206\345\257\206\351\222\245", Q_NULLPTR));
        pwd_button->setText(QApplication::translate("restore", "\347\241\256\350\256\244\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class restore: public Ui_restore {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTORE_H
