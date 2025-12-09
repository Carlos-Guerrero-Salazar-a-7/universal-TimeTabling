/********************************************************************************
** Form generated from reading UI file 'scheduleswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULESWIDGET_H
#define UI_SCHEDULESWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SchedulesWidget
{
public:
    QLabel *titleLabel;
    QWidget *toggleContainer;
    QHBoxLayout *horizontalLayout;
    QPushButton *maestroButton;
    QPushButton *grupoButton;
    QLineEdit *searchLineEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QFrame *itemFrame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nameLabel;
    QFrame *line1;
    QLabel *subjectsLabel;
    QFrame *line2;
    QLabel *hoursLabel;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *SchedulesWidget)
    {
        if (SchedulesWidget->objectName().isEmpty())
            SchedulesWidget->setObjectName(QString::fromUtf8("SchedulesWidget"));
        SchedulesWidget->resize(1231, 551);
        SchedulesWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        titleLabel = new QLabel(SchedulesWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(30, 20, 201, 51));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 36px;\n"
"color: black;"));
        toggleContainer = new QWidget(SchedulesWidget);
        toggleContainer->setObjectName(QString::fromUtf8("toggleContainer"));
        toggleContainer->setGeometry(QRect(30, 80, 601, 51));
        horizontalLayout = new QHBoxLayout(toggleContainer);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        maestroButton = new QPushButton(toggleContainer);
        maestroButton->setObjectName(QString::fromUtf8("maestroButton"));
        maestroButton->setMinimumSize(QSize(0, 40));
        maestroButton->setCursor(QCursor(Qt::PointingHandCursor));
        maestroButton->setStyleSheet(QString::fromUtf8("background-color: #5c7c9e;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));

        horizontalLayout->addWidget(maestroButton);

        grupoButton = new QPushButton(toggleContainer);
        grupoButton->setObjectName(QString::fromUtf8("grupoButton"));
        grupoButton->setMinimumSize(QSize(0, 40));
        grupoButton->setCursor(QCursor(Qt::PointingHandCursor));
        grupoButton->setStyleSheet(QString::fromUtf8("background-color: #5c7c9e;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));

        horizontalLayout->addWidget(grupoButton);

        searchLineEdit = new QLineEdit(SchedulesWidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(30, 140, 601, 41));
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: #e0e0e0;\n"
"border-radius: 20px;\n"
"padding-left: 15px;\n"
"font-size: 14px;\n"
"color: #606060;"));
        scrollArea = new QScrollArea(SchedulesWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(30, 200, 761, 331));
        scrollArea->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: transparent;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 761, 331));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        itemFrame = new QFrame(scrollAreaWidgetContents);
        itemFrame->setObjectName(QString::fromUtf8("itemFrame"));
        itemFrame->setMinimumSize(QSize(0, 40));
        itemFrame->setStyleSheet(QString::fromUtf8("background-color: #5c7c9e;\n"
"border-radius: 5px;"));
        horizontalLayout_2 = new QHBoxLayout(itemFrame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 10, 0);
        nameLabel = new QLabel(itemFrame);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setStyleSheet(QString::fromUtf8("color: white; font-weight: bold;"));

        horizontalLayout_2->addWidget(nameLabel);

        line1 = new QFrame(itemFrame);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setFrameShape(QFrame::HLine);
        line1->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line1);

        subjectsLabel = new QLabel(itemFrame);
        subjectsLabel->setObjectName(QString::fromUtf8("subjectsLabel"));
        subjectsLabel->setStyleSheet(QString::fromUtf8("color: white; font-weight: bold;"));

        horizontalLayout_2->addWidget(subjectsLabel);

        line2 = new QFrame(itemFrame);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setFrameShape(QFrame::HLine);
        line2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line2);

        hoursLabel = new QLabel(itemFrame);
        hoursLabel->setObjectName(QString::fromUtf8("hoursLabel"));
        hoursLabel->setStyleSheet(QString::fromUtf8("color: white; font-weight: bold;"));

        horizontalLayout_2->addWidget(hoursLabel);


        verticalLayout->addWidget(itemFrame);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(SchedulesWidget);

        QMetaObject::connectSlotsByName(SchedulesWidget);
    } // setupUi

    void retranslateUi(QWidget *SchedulesWidget)
    {
        SchedulesWidget->setWindowTitle(QCoreApplication::translate("SchedulesWidget", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("SchedulesWidget", "Horarios", nullptr));
        maestroButton->setText(QCoreApplication::translate("SchedulesWidget", "Maestro", nullptr));
        grupoButton->setText(QCoreApplication::translate("SchedulesWidget", "Grupo", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("SchedulesWidget", "Search", nullptr));
        nameLabel->setText(QCoreApplication::translate("SchedulesWidget", "Nombreplaceholder", nullptr));
        subjectsLabel->setText(QCoreApplication::translate("SchedulesWidget", "Materias", nullptr));
        hoursLabel->setText(QCoreApplication::translate("SchedulesWidget", "horas", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SchedulesWidget: public Ui_SchedulesWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULESWIDGET_H
