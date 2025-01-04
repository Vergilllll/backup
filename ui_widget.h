/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QWidget *centralwidget;
    QLabel *title;
    QLabel *pic;
    QPushButton *backup;
    QPushButton *restore;

    void setupUi(QMainWindow *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QString::fromUtf8("widget"));
        widget->resize(387, 266);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(widget);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        title = new QLabel(centralwidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(120, 40, 181, 41));
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        pic = new QLabel(centralwidget);
        pic->setObjectName(QString::fromUtf8("pic"));
        pic->setGeometry(QRect(0, 0, 387, 266));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pic->sizePolicy().hasHeightForWidth());
        pic->setSizePolicy(sizePolicy1);
        pic->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/1.png);"));
        backup = new QPushButton(centralwidget);
        backup->setObjectName(QString::fromUtf8("backup"));
        backup->setGeometry(QRect(150, 110, 80, 41));
        sizePolicy.setHeightForWidth(backup->sizePolicy().hasHeightForWidth());
        backup->setSizePolicy(sizePolicy);
        restore = new QPushButton(centralwidget);
        restore->setObjectName(QString::fromUtf8("restore"));
        restore->setGeometry(QRect(150, 180, 80, 41));
        sizePolicy.setHeightForWidth(restore->sizePolicy().hasHeightForWidth());
        restore->setSizePolicy(sizePolicy);
        widget->setCentralWidget(centralwidget);
        pic->raise();
        backup->raise();
        restore->raise();
        title->raise();

        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QMainWindow *widget)
    {
        widget->setWindowTitle(QCoreApplication::translate("widget", "\346\225\260\346\215\256\345\244\207\344\273\275\350\275\257\344\273\266", nullptr));
        title->setText(QCoreApplication::translate("widget", "<html><head/><body><p><span style=\" font-size:14pt; font-weight:700; color:#ffffff;\">\346\225\260\346\215\256\345\244\207\344\273\275\350\275\257\344\273\266</span></p></body></html>", nullptr));
        pic->setText(QString());
        backup->setText(QCoreApplication::translate("widget", "\345\244\207\344\273\275", nullptr));
        restore->setText(QCoreApplication::translate("widget", "\346\201\242\345\244\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
