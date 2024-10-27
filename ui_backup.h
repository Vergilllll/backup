/********************************************************************************
** Form generated from reading UI file 'backup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKUP_H
#define UI_BACKUP_H

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

    void setupUi(QWidget *backup)
    {
        if (backup->objectName().isEmpty())
            backup->setObjectName(QStringLiteral("backup"));
        backup->resize(402, 282);
        res_button = new QPushButton(backup);
        res_button->setObjectName(QStringLiteral("res_button"));
        res_button->setGeometry(QRect(290, 100, 80, 20));
        origin_res = new QLineEdit(backup);
        origin_res->setObjectName(QStringLiteral("origin_res"));
        origin_res->setGeometry(QRect(80, 70, 291, 21));
        bu_res = new QLineEdit(backup);
        bu_res->setObjectName(QStringLiteral("bu_res"));
        bu_res->setGeometry(QRect(80, 150, 291, 20));
        res_label = new QLabel(backup);
        res_label->setObjectName(QStringLiteral("res_label"));
        res_label->setGeometry(QRect(20, 70, 54, 12));
        bu_label = new QLabel(backup);
        bu_label->setObjectName(QStringLiteral("bu_label"));
        bu_label->setGeometry(QRect(13, 150, 61, 20));
        title = new QLabel(backup);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(180, 20, 71, 20));
        title->setStyleSheet(QStringLiteral(""));
        bu_button = new QPushButton(backup);
        bu_button->setObjectName(QStringLiteral("bu_button"));
        bu_button->setGeometry(QRect(290, 180, 80, 20));
        bu = new QPushButton(backup);
        bu->setObjectName(QStringLiteral("bu"));
        bu->setGeometry(QRect(170, 210, 91, 51));
        label = new QLabel(backup);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 402, 282));
        label->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/1.png);"));
        return_main = new QPushButton(backup);
        return_main->setObjectName(QStringLiteral("return_main"));
        return_main->setGeometry(QRect(40, 220, 80, 31));
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

        retranslateUi(backup);

        QMetaObject::connectSlotsByName(backup);
    } // setupUi

    void retranslateUi(QWidget *backup)
    {
        backup->setWindowTitle(QApplication::translate("backup", "Form", Q_NULLPTR));
        res_button->setText(QApplication::translate("backup", "\346\265\217\350\247\210", Q_NULLPTR));
        res_label->setText(QApplication::translate("backup", "\346\272\220\350\267\257\345\276\204", Q_NULLPTR));
        bu_label->setText(QApplication::translate("backup", "\345\244\207\344\273\275\350\267\257\345\276\204", Q_NULLPTR));
        title->setText(QApplication::translate("backup", "\345\244\207\344\273\275\345\212\237\350\203\275", Q_NULLPTR));
        bu_button->setText(QApplication::translate("backup", "\346\265\217\350\247\210", Q_NULLPTR));
        bu->setText(QApplication::translate("backup", "\350\277\233\350\241\214\345\244\207\344\273\275", Q_NULLPTR));
        label->setText(QString());
        return_main->setText(QApplication::translate("backup", "\350\277\224\345\233\236\344\270\273\347\225\214\351\235\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class backup: public Ui_backup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKUP_H
