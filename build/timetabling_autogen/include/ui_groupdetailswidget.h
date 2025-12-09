/********************************************************************************
** Form generated from reading UI file 'groupdetailswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPDETAILSWIDGET_H
#define UI_GROUPDETAILSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupDetailsWidget
{
public:
    QFrame *topBar;
    QPushButton *backButton;
    QPushButton *deleteButton;
    QPushButton *createButton;
    QLabel *titleLabel;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *scheduleLabel;
    QComboBox *fromComboBox;
    QComboBox *toComboBox;
    QLabel *subjectsLabel;
    QFrame *subjectsFrame;
    QComboBox *quarterComboBox;
    QLabel *colorLabel;
    QWidget *colorPicker;
    QWidget *selectedColor;

    void setupUi(QWidget *GroupDetailsWidget)
    {
        if (GroupDetailsWidget->objectName().isEmpty())
            GroupDetailsWidget->setObjectName(QString::fromUtf8("GroupDetailsWidget"));
        GroupDetailsWidget->resize(1231, 551);
        GroupDetailsWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        topBar = new QFrame(GroupDetailsWidget);
        topBar->setObjectName(QString::fromUtf8("topBar"));
        topBar->setGeometry(QRect(0, 0, 1231, 61));
        topBar->setStyleSheet(QString::fromUtf8("background-color: #34495e;"));
        topBar->setFrameShape(QFrame::Shape::StyledPanel);
        topBar->setFrameShadow(QFrame::Shadow::Raised);
        backButton = new QPushButton(topBar);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(30, 15, 101, 31));
        backButton->setCursor(QCursor(Qt::PointingHandCursor));
        backButton->setStyleSheet(QString::fromUtf8("background-color: #2c3e50;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        deleteButton = new QPushButton(topBar);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(950, 15, 121, 31));
        deleteButton->setCursor(QCursor(Qt::PointingHandCursor));
        deleteButton->setStyleSheet(QString::fromUtf8("background-color: #e74c3c;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        createButton = new QPushButton(topBar);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setGeometry(QRect(1090, 15, 111, 31));
        createButton->setCursor(QCursor(Qt::PointingHandCursor));
        createButton->setStyleSheet(QString::fromUtf8("background-color: #2ecc71;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        titleLabel = new QLabel(GroupDetailsWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(160, 80, 301, 41));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 32px;\n"
"color: black;\n"
"font-weight: bold;"));
        nameLabel = new QLabel(GroupDetailsWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(160, 150, 101, 21));
        nameLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        nameLineEdit = new QLineEdit(GroupDetailsWidget);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setGeometry(QRect(160, 180, 281, 31));
        nameLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));
        scheduleLabel = new QLabel(GroupDetailsWidget);
        scheduleLabel->setObjectName(QString::fromUtf8("scheduleLabel"));
        scheduleLabel->setGeometry(QRect(500, 150, 151, 21));
        scheduleLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        fromComboBox = new QComboBox(GroupDetailsWidget);
        fromComboBox->addItem(QString());
        fromComboBox->setObjectName(QString::fromUtf8("fromComboBox"));
        fromComboBox->setGeometry(QRect(500, 180, 161, 31));
        fromComboBox->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));
        toComboBox = new QComboBox(GroupDetailsWidget);
        toComboBox->addItem(QString());
        toComboBox->setObjectName(QString::fromUtf8("toComboBox"));
        toComboBox->setGeometry(QRect(670, 180, 161, 31));
        toComboBox->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));
        subjectsLabel = new QLabel(GroupDetailsWidget);
        subjectsLabel->setObjectName(QString::fromUtf8("subjectsLabel"));
        subjectsLabel->setGeometry(QRect(160, 230, 101, 21));
        subjectsLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        subjectsFrame = new QFrame(GroupDetailsWidget);
        subjectsFrame->setObjectName(QString::fromUtf8("subjectsFrame"));
        subjectsFrame->setGeometry(QRect(160, 260, 271, 51));
        subjectsFrame->setStyleSheet(QString::fromUtf8("background-color: #5c7c9e;\n"
"border-radius: 5px;"));
        quarterComboBox = new QComboBox(subjectsFrame);
        quarterComboBox->addItem(QString());
        quarterComboBox->setObjectName(QString::fromUtf8("quarterComboBox"));
        quarterComboBox->setGeometry(QRect(10, 10, 250, 31));
        quarterComboBox->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;\n"
"background-color: white;"));
        colorLabel = new QLabel(GroupDetailsWidget);
        colorLabel->setObjectName(QString::fromUtf8("colorLabel"));
        colorLabel->setGeometry(QRect(280, 340, 151, 21));
        colorLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        colorPicker = new QWidget(GroupDetailsWidget);
        colorPicker->setObjectName(QString::fromUtf8("colorPicker"));
        colorPicker->setGeometry(QRect(160, 330, 101, 101));
        colorPicker->setStyleSheet(QString::fromUtf8("border-radius: 50px;\n"
"background-color: qconicalgradient(cx:0.5, cy:0.5, angle:90, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));"));
        selectedColor = new QWidget(GroupDetailsWidget);
        selectedColor->setObjectName(QString::fromUtf8("selectedColor"));
        selectedColor->setGeometry(QRect(280, 380, 161, 31));
        selectedColor->setStyleSheet(QString::fromUtf8("background-color: #00ff40;\n"
"border-radius: 5px;"));

        retranslateUi(GroupDetailsWidget);

        QMetaObject::connectSlotsByName(GroupDetailsWidget);
    } // setupUi

    void retranslateUi(QWidget *GroupDetailsWidget)
    {
        GroupDetailsWidget->setWindowTitle(QCoreApplication::translate("GroupDetailsWidget", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("GroupDetailsWidget", "Regresar", nullptr));
        deleteButton->setText(QCoreApplication::translate("GroupDetailsWidget", "Borrar Grupo", nullptr));
        createButton->setText(QCoreApplication::translate("GroupDetailsWidget", "Crear Grupo", nullptr));
        titleLabel->setText(QCoreApplication::translate("GroupDetailsWidget", "Datos del grupo", nullptr));
        nameLabel->setText(QCoreApplication::translate("GroupDetailsWidget", "Nombre", nullptr));
        nameLineEdit->setPlaceholderText(QCoreApplication::translate("GroupDetailsWidget", "Lorem ipsum", nullptr));
        scheduleLabel->setText(QCoreApplication::translate("GroupDetailsWidget", "Rango del horario", nullptr));
        fromComboBox->setItemText(0, QCoreApplication::translate("GroupDetailsWidget", "Desde", nullptr));

        toComboBox->setItemText(0, QCoreApplication::translate("GroupDetailsWidget", "Hasta", nullptr));

        subjectsLabel->setText(QCoreApplication::translate("GroupDetailsWidget", "Materias", nullptr));
        quarterComboBox->setItemText(0, QCoreApplication::translate("GroupDetailsWidget", "4to Trimestre 2025", nullptr));

        colorLabel->setText(QCoreApplication::translate("GroupDetailsWidget", "Color identificativo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupDetailsWidget: public Ui_GroupDetailsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPDETAILSWIDGET_H
