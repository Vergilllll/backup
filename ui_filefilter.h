/********************************************************************************
** Form generated from reading UI file 'filefilter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEFILTER_H
#define UI_FILEFILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Filefilter
{
public:
    QPushButton *filterButton;
    QPushButton *returnButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *typesTextBox;
    QLabel *label_5;
    QLineEdit *namesTextBox;
    QLineEdit *pathTextBox;
    QLabel *label_7;
    QLineEdit *maxSizeTextBox;
    QLabel *label;
    QLineEdit *startTimeTextBox;
    QLabel *label_4;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *minSizeTextBox;
    QLineEdit *endTimeTextBox;
    QLabel *label_8;

    void setupUi(QDialog *Filefilter)
    {
        if (Filefilter->objectName().isEmpty())
            Filefilter->setObjectName(QString::fromUtf8("Filefilter"));
        Filefilter->resize(452, 368);
        filterButton = new QPushButton(Filefilter);
        filterButton->setObjectName(QString::fromUtf8("filterButton"));
        filterButton->setGeometry(QRect(150, 330, 121, 31));
        returnButton = new QPushButton(Filefilter);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));
        returnButton->setGeometry(QRect(10, 10, 61, 28));
        layoutWidget = new QWidget(Filefilter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 421, 291));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        typesTextBox = new QLineEdit(layoutWidget);
        typesTextBox->setObjectName(QString::fromUtf8("typesTextBox"));

        gridLayout->addWidget(typesTextBox, 1, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        namesTextBox = new QLineEdit(layoutWidget);
        namesTextBox->setObjectName(QString::fromUtf8("namesTextBox"));

        gridLayout->addWidget(namesTextBox, 2, 1, 1, 1);

        pathTextBox = new QLineEdit(layoutWidget);
        pathTextBox->setObjectName(QString::fromUtf8("pathTextBox"));

        gridLayout->addWidget(pathTextBox, 0, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        maxSizeTextBox = new QLineEdit(layoutWidget);
        maxSizeTextBox->setObjectName(QString::fromUtf8("maxSizeTextBox"));

        gridLayout->addWidget(maxSizeTextBox, 6, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(100, 20));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        startTimeTextBox = new QLineEdit(layoutWidget);
        startTimeTextBox->setObjectName(QString::fromUtf8("startTimeTextBox"));

        gridLayout->addWidget(startTimeTextBox, 3, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        minSizeTextBox = new QLineEdit(layoutWidget);
        minSizeTextBox->setObjectName(QString::fromUtf8("minSizeTextBox"));

        gridLayout->addWidget(minSizeTextBox, 5, 1, 1, 1);

        endTimeTextBox = new QLineEdit(layoutWidget);
        endTimeTextBox->setObjectName(QString::fromUtf8("endTimeTextBox"));

        gridLayout->addWidget(endTimeTextBox, 4, 1, 1, 1);

        label_8 = new QLabel(Filefilter);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(0, 0, 481, 381));
        label_8->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/1.png);"));
        label_8->raise();
        filterButton->raise();
        returnButton->raise();
        layoutWidget->raise();

        retranslateUi(Filefilter);

        QMetaObject::connectSlotsByName(Filefilter);
    } // setupUi

    void retranslateUi(QDialog *Filefilter)
    {
        Filefilter->setWindowTitle(QCoreApplication::translate("Filefilter", "\350\207\252\345\256\232\344\271\211\345\244\207\344\273\275", nullptr));
        filterButton->setText(QCoreApplication::translate("Filefilter", "\347\255\233\351\200\211\346\226\207\344\273\266", nullptr));
        returnButton->setText(QCoreApplication::translate("Filefilter", "\350\277\224\345\233\236", nullptr));
        label_3->setText(QCoreApplication::translate("Filefilter", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\226\207\344\273\266\345\220\215</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("Filefilter", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\234\200\345\260\217\345\260\272\345\257\270\357\274\210MB\357\274\211</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("Filefilter", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\226\207\344\273\266\350\267\257\345\276\204</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("Filefilter", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\226\207\344\273\266\347\261\273\345\236\213</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("Filefilter", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\210\252\346\255\242\346\227\266\351\227\264</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Filefilter", "<html><head/><body><p><span style=\" color:#ffffff;\">\345\274\200\345\247\213\346\227\266\351\227\264</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("Filefilter", "<html><head/><body><p><span style=\" color:#ffffff;\">\346\234\200\345\244\247\345\260\272\345\257\270(MB)</span></p></body></html>", nullptr));
        label_8->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Filefilter: public Ui_Filefilter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEFILTER_H
