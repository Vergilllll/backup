/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            widget->setObjectName(QStringLiteral("widget"));
        widget->resize(387, 266);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(widget);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        title = new QLabel(centralwidget);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(130, 30, 141, 31));
        sizePolicy.setHeightForWidth(title->sizePolicy().hasHeightForWidth());
        title->setSizePolicy(sizePolicy);
        pic = new QLabel(centralwidget);
        pic->setObjectName(QStringLiteral("pic"));
        pic->setGeometry(QRect(0, 0, 387, 266));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pic->sizePolicy().hasHeightForWidth());
        pic->setSizePolicy(sizePolicy1);
        pic->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/1.png);"));
        backup = new QPushButton(centralwidget);
        backup->setObjectName(QStringLiteral("backup"));
        backup->setGeometry(QRect(150, 110, 80, 41));
        sizePolicy.setHeightForWidth(backup->sizePolicy().hasHeightForWidth());
        backup->setSizePolicy(sizePolicy);
        restore = new QPushButton(centralwidget);
        restore->setObjectName(QStringLiteral("restore"));
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
        widget->setWindowTitle(QApplication::translate("widget", "widget", Q_NULLPTR));
        title->setText(QApplication::translate("widget", "\346\225\260\346\215\256\345\244\207\344\273\275\350\275\257\344\273\266", Q_NULLPTR));
        pic->setText(QString());
        backup->setText(QApplication::translate("widget", "\345\244\207\344\273\275", Q_NULLPTR));
        restore->setText(QApplication::translate("widget", "\346\201\242\345\244\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
