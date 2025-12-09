/********************************************************************************
** Form generated from reading UI file 'roomdetailswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMDETAILSWIDGET_H
#define UI_ROOMDETAILSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoomDetailsWidget
{
public:
    QFrame *topBar;
    QPushButton *backButton;
    QPushButton *deleteButton;
    QPushButton *createButton;
    QLabel *titleLabel;
    QLabel *edificioLabel;
    QLineEdit *edificioLineEdit;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QLabel *especialidadLabel;
    QLineEdit *especialidadLineEdit;

    void setupUi(QWidget *RoomDetailsWidget)
    {
        if (RoomDetailsWidget->objectName().isEmpty())
            RoomDetailsWidget->setObjectName(QString::fromUtf8("RoomDetailsWidget"));
        RoomDetailsWidget->resize(1231, 551);
        RoomDetailsWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        topBar = new QFrame(RoomDetailsWidget);
        topBar->setObjectName(QString::fromUtf8("topBar"));
        topBar->setGeometry(QRect(0, 0, 1231, 61));
        topBar->setStyleSheet(QString::fromUtf8("background-color: #34495e;"));
        topBar->setFrameShape(QFrame::StyledPanel);
        topBar->setFrameShadow(QFrame::Raised);
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
        titleLabel = new QLabel(RoomDetailsWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(160, 80, 301, 41));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 32px;\n"
"color: black;\n"
"font-weight: bold;"));
        edificioLabel = new QLabel(RoomDetailsWidget);
        edificioLabel->setObjectName(QString::fromUtf8("edificioLabel"));
        edificioLabel->setGeometry(QRect(160, 150, 101, 21));
        edificioLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        edificioLineEdit = new QLineEdit(RoomDetailsWidget);
        edificioLineEdit->setObjectName(QString::fromUtf8("edificioLineEdit"));
        edificioLineEdit->setGeometry(QRect(160, 180, 281, 31));
        edificioLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));
        idLabel = new QLabel(RoomDetailsWidget);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));
        idLabel->setGeometry(QRect(480, 150, 101, 21));
        idLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        idLineEdit = new QLineEdit(RoomDetailsWidget);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));
        idLineEdit->setGeometry(QRect(480, 180, 281, 31));
        idLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));
        especialidadLabel = new QLabel(RoomDetailsWidget);
        especialidadLabel->setObjectName(QString::fromUtf8("especialidadLabel"));
        especialidadLabel->setGeometry(QRect(160, 240, 101, 21));
        especialidadLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        especialidadLineEdit = new QLineEdit(RoomDetailsWidget);
        especialidadLineEdit->setObjectName(QString::fromUtf8("especialidadLineEdit"));
        especialidadLineEdit->setGeometry(QRect(160, 270, 281, 31));
        especialidadLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));

        retranslateUi(RoomDetailsWidget);

        QMetaObject::connectSlotsByName(RoomDetailsWidget);
    } // setupUi

    void retranslateUi(QWidget *RoomDetailsWidget)
    {
        RoomDetailsWidget->setWindowTitle(QCoreApplication::translate("RoomDetailsWidget", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("RoomDetailsWidget", "Regresar", nullptr));
        deleteButton->setText(QCoreApplication::translate("RoomDetailsWidget", "Borrar Salon", nullptr));
        createButton->setText(QCoreApplication::translate("RoomDetailsWidget", "Crear Salon", nullptr));
        titleLabel->setText(QCoreApplication::translate("RoomDetailsWidget", "Datos del salon", nullptr));
        edificioLabel->setText(QCoreApplication::translate("RoomDetailsWidget", "Edificio", nullptr));
        edificioLineEdit->setPlaceholderText(QCoreApplication::translate("RoomDetailsWidget", "Lorem ipsum", nullptr));
        idLabel->setText(QCoreApplication::translate("RoomDetailsWidget", "ID", nullptr));
        idLineEdit->setPlaceholderText(QCoreApplication::translate("RoomDetailsWidget", "Lorem ipsum", nullptr));
        especialidadLabel->setText(QCoreApplication::translate("RoomDetailsWidget", "Especialidad", nullptr));
        especialidadLineEdit->setPlaceholderText(QCoreApplication::translate("RoomDetailsWidget", "Ninguna", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoomDetailsWidget: public Ui_RoomDetailsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMDETAILSWIDGET_H
