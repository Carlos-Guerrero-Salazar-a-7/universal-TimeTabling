/********************************************************************************
** Form generated from reading UI file 'saloneswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SALONESWIDGET_H
#define UI_SALONESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SalonesWidget
{
public:
    QLabel *titleLabel;
    QLineEdit *searchLineEdit;
    QPushButton *addButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QPushButton *item1;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SalonesWidget)
    {
        if (SalonesWidget->objectName().isEmpty())
            SalonesWidget->setObjectName(QString::fromUtf8("SalonesWidget"));
        SalonesWidget->resize(1231, 551);
        SalonesWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        titleLabel = new QLabel(SalonesWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(30, 20, 201, 51));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 36px;\n"
"color: black;"));
        searchLineEdit = new QLineEdit(SalonesWidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(30, 90, 601, 41));
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: #e0e0e0;\n"
"border-radius: 20px;\n"
"padding-left: 15px;\n"
"font-size: 14px;\n"
"color: #606060;"));
        addButton = new QPushButton(SalonesWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(660, 90, 131, 41));
        addButton->setCursor(QCursor(Qt::PointingHandCursor));
        addButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4cd964;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #42bd56;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #3aa34a;\n"
"}"));
        scrollArea = new QScrollArea(SalonesWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(30, 150, 761, 381));
        scrollArea->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: transparent;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 761, 381));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        item1 = new QPushButton(scrollAreaWidgetContents);
        item1->setObjectName(QString::fromUtf8("item1"));
        item1->setMinimumSize(QSize(0, 40));
        item1->setStyleSheet(QString::fromUtf8("background-color: #5c7c9e;\n"
"color: white;\n"
"border-radius: 5px;\n"
"text-align: left;\n"
"padding-left: 20px;\n"
"font-weight: bold;"));

        verticalLayout->addWidget(item1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(SalonesWidget);

        QMetaObject::connectSlotsByName(SalonesWidget);
    } // setupUi

    void retranslateUi(QWidget *SalonesWidget)
    {
        SalonesWidget->setWindowTitle(QCoreApplication::translate("SalonesWidget", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("SalonesWidget", "Salon", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("SalonesWidget", "Search", nullptr));
        addButton->setText(QCoreApplication::translate("SalonesWidget", "+", nullptr));
        item1->setText(QCoreApplication::translate("SalonesWidget", "salonplacerholdername", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SalonesWidget: public Ui_SalonesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SALONESWIDGET_H
