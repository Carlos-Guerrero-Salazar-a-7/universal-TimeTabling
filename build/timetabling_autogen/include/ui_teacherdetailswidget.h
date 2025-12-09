/********************************************************************************
** Form generated from reading UI file 'teacherdetailswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHERDETAILSWIDGET_H
#define UI_TEACHERDETAILSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TeacherDetailsWidget
{
public:
    QFrame *topBar;
    QPushButton *backButton;
    QPushButton *deleteButton;
    QPushButton *createButton;
    QLabel *titleLabel;
    QFrame *frame_2;
    QWidget *colorPicker;
    QLabel *colorLabel;
    QWidget *selectedColor;
    QFrame *frame_4;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *specialtyLabel;
    QLineEdit *specialtyLineEdit;
    QLabel *scheduleLabel;
    QComboBox *fromComboBox;
    QComboBox *toComboBox;

    void setupUi(QWidget *TeacherDetailsWidget)
    {
        if (TeacherDetailsWidget->objectName().isEmpty())
            TeacherDetailsWidget->setObjectName(QString::fromUtf8("TeacherDetailsWidget"));
        TeacherDetailsWidget->resize(1231, 551);
        TeacherDetailsWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        topBar = new QFrame(TeacherDetailsWidget);
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
        titleLabel = new QLabel(TeacherDetailsWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(160, 80, 301, 41));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 32px;\n"
"color: black;\n"
"font-weight: bold;"));
        frame_2 = new QFrame(TeacherDetailsWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(800, 160, 291, 121));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        colorPicker = new QWidget(frame_2);
        colorPicker->setObjectName(QString::fromUtf8("colorPicker"));
        colorPicker->setGeometry(QRect(10, 10, 101, 101));
        colorPicker->setStyleSheet(QString::fromUtf8("border-radius: 50px;\n"
"background-color: qconicalgradient(cx:0.5, cy:0.5, angle:90, stop:0 rgba(255, 0, 0, 255), stop:0.166 rgba(255, 255, 0, 255), stop:0.333 rgba(0, 255, 0, 255), stop:0.5 rgba(0, 255, 255, 255), stop:0.666 rgba(0, 0, 255, 255), stop:0.833 rgba(255, 0, 255, 255), stop:1 rgba(255, 0, 0, 255));"));
        colorLabel = new QLabel(frame_2);
        colorLabel->setObjectName(QString::fromUtf8("colorLabel"));
        colorLabel->setGeometry(QRect(120, 10, 151, 21));
        colorLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        selectedColor = new QWidget(frame_2);
        selectedColor->setObjectName(QString::fromUtf8("selectedColor"));
        selectedColor->setGeometry(QRect(120, 40, 161, 31));
        selectedColor->setStyleSheet(QString::fromUtf8("background-color: #007bff;\n"
"border-radius: 5px;"));
        frame_4 = new QFrame(TeacherDetailsWidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(160, 140, 561, 141));
        frame_4->setFrameShape(QFrame::Shape::StyledPanel);
        frame_4->setFrameShadow(QFrame::Shadow::Raised);
        nameLabel = new QLabel(frame_4);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(10, 0, 101, 21));
        nameLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        nameLineEdit = new QLineEdit(frame_4);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setGeometry(QRect(10, 20, 281, 31));
        nameLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));
        specialtyLabel = new QLabel(frame_4);
        specialtyLabel->setObjectName(QString::fromUtf8("specialtyLabel"));
        specialtyLabel->setGeometry(QRect(10, 60, 101, 21));
        specialtyLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        specialtyLineEdit = new QLineEdit(frame_4);
        specialtyLineEdit->setObjectName(QString::fromUtf8("specialtyLineEdit"));
        specialtyLineEdit->setGeometry(QRect(10, 90, 281, 31));
        specialtyLineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));
        scheduleLabel = new QLabel(frame_4);
        scheduleLabel->setObjectName(QString::fromUtf8("scheduleLabel"));
        scheduleLabel->setGeometry(QRect(330, 10, 221, 21));
        scheduleLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        fromComboBox = new QComboBox(frame_4);
        fromComboBox->addItem(QString());
        fromComboBox->setObjectName(QString::fromUtf8("fromComboBox"));
        fromComboBox->setGeometry(QRect(330, 40, 161, 31));
        fromComboBox->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));
        toComboBox = new QComboBox(frame_4);
        toComboBox->addItem(QString());
        toComboBox->setObjectName(QString::fromUtf8("toComboBox"));
        toComboBox->setGeometry(QRect(330, 80, 161, 31));
        toComboBox->setStyleSheet(QString::fromUtf8("border: 1px solid #ccc;\n"
"border-radius: 5px;\n"
"padding: 5px;"));

        retranslateUi(TeacherDetailsWidget);

        QMetaObject::connectSlotsByName(TeacherDetailsWidget);
    } // setupUi

    void retranslateUi(QWidget *TeacherDetailsWidget)
    {
        TeacherDetailsWidget->setWindowTitle(QCoreApplication::translate("TeacherDetailsWidget", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("TeacherDetailsWidget", "Regresar", nullptr));
        deleteButton->setText(QCoreApplication::translate("TeacherDetailsWidget", "Borrar maestro", nullptr));
        createButton->setText(QCoreApplication::translate("TeacherDetailsWidget", "Crear maestro", nullptr));
        titleLabel->setText(QCoreApplication::translate("TeacherDetailsWidget", "Datos del maestro", nullptr));
        colorLabel->setText(QCoreApplication::translate("TeacherDetailsWidget", "Color identificativo", nullptr));
        nameLabel->setText(QCoreApplication::translate("TeacherDetailsWidget", "Nombre", nullptr));
        nameLineEdit->setPlaceholderText(QCoreApplication::translate("TeacherDetailsWidget", "Lorem ipsum", nullptr));
        specialtyLabel->setText(QCoreApplication::translate("TeacherDetailsWidget", "Especialidad", nullptr));
        specialtyLineEdit->setPlaceholderText(QCoreApplication::translate("TeacherDetailsWidget", "Lorem ipsum", nullptr));
        scheduleLabel->setText(QCoreApplication::translate("TeacherDetailsWidget", "Horario de disponibilidad general", nullptr));
        fromComboBox->setItemText(0, QCoreApplication::translate("TeacherDetailsWidget", "Desde", nullptr));

        toComboBox->setItemText(0, QCoreApplication::translate("TeacherDetailsWidget", "Hasta", nullptr));

    } // retranslateUi

};

namespace Ui {
    class TeacherDetailsWidget: public Ui_TeacherDetailsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHERDETAILSWIDGET_H
