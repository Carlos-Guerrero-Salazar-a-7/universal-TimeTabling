/********************************************************************************
** Form generated from reading UI file 'quarterswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUARTERSWIDGET_H
#define UI_QUARTERSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuartersWidget
{
public:
    QLabel *titleLabel;
    QLineEdit *searchLineEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QFrame *itemFrame;
    QHBoxLayout *horizontalLayout;
    QLabel *quarterNameLabel;
    QFrame *line1;
    QLabel *subjectsCountLabel;
    QFrame *line2;
    QLabel *hoursCountLabel;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *QuartersWidget)
    {
        if (QuartersWidget->objectName().isEmpty())
            QuartersWidget->setObjectName(QString::fromUtf8("QuartersWidget"));
        QuartersWidget->resize(1231, 551);
        QuartersWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        titleLabel = new QLabel(QuartersWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(30, 20, 301, 51));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 36px;\n"
"color: black;"));
        searchLineEdit = new QLineEdit(QuartersWidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(30, 90, 601, 41));
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: #e0e0e0;\n"
"border-radius: 20px;\n"
"padding-left: 15px;\n"
"font-size: 14px;\n"
"color: #606060;"));
        scrollArea = new QScrollArea(QuartersWidget);
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
        itemFrame = new QFrame(scrollAreaWidgetContents);
        itemFrame->setObjectName(QString::fromUtf8("itemFrame"));
        itemFrame->setMinimumSize(QSize(0, 40));
        itemFrame->setStyleSheet(QString::fromUtf8("background-color: #5c7c9e;\n"
"border-radius: 5px;"));
        horizontalLayout = new QHBoxLayout(itemFrame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        quarterNameLabel = new QLabel(itemFrame);
        quarterNameLabel->setObjectName(QString::fromUtf8("quarterNameLabel"));
        quarterNameLabel->setStyleSheet(QString::fromUtf8("color: white; font-weight: bold;"));

        horizontalLayout->addWidget(quarterNameLabel);

        line1 = new QFrame(itemFrame);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line1);

        subjectsCountLabel = new QLabel(itemFrame);
        subjectsCountLabel->setObjectName(QString::fromUtf8("subjectsCountLabel"));
        subjectsCountLabel->setStyleSheet(QString::fromUtf8("color: white; font-weight: bold;"));

        horizontalLayout->addWidget(subjectsCountLabel);

        line2 = new QFrame(itemFrame);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line2);

        hoursCountLabel = new QLabel(itemFrame);
        hoursCountLabel->setObjectName(QString::fromUtf8("hoursCountLabel"));
        hoursCountLabel->setStyleSheet(QString::fromUtf8("color: white; font-weight: bold;"));

        horizontalLayout->addWidget(hoursCountLabel);


        verticalLayout->addWidget(itemFrame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(QuartersWidget);

        QMetaObject::connectSlotsByName(QuartersWidget);
    } // setupUi

    void retranslateUi(QWidget *QuartersWidget)
    {
        QuartersWidget->setWindowTitle(QCoreApplication::translate("QuartersWidget", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("QuartersWidget", "Cuatrimestres", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("QuartersWidget", "Search", nullptr));
        quarterNameLabel->setText(QCoreApplication::translate("QuartersWidget", "Nombre del Cuatrimestre", nullptr));
        subjectsCountLabel->setText(QCoreApplication::translate("QuartersWidget", "Materias", nullptr));
        hoursCountLabel->setText(QCoreApplication::translate("QuartersWidget", "Horas", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuartersWidget: public Ui_QuartersWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUARTERSWIDGET_H
