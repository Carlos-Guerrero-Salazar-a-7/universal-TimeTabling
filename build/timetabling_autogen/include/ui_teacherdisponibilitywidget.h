/********************************************************************************
** Form generated from reading UI file 'teacherdisponibilitywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHERDISPONIBILITYWIDGET_H
#define UI_TEACHERDISPONIBILITYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TeacherDisponibilityWidget
{
public:
    QLabel *titleLabel;
    QLineEdit *searchLineEdit;
    QPushButton *addTeacherButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QFrame *teacherCard;
    QLabel *teacherNameLabel;
    QPushButton *editButton;
    QTableWidget *scheduleTable;

    void setupUi(QWidget *TeacherDisponibilityWidget)
    {
        if (TeacherDisponibilityWidget->objectName().isEmpty())
            TeacherDisponibilityWidget->setObjectName(QString::fromUtf8("TeacherDisponibilityWidget"));
        TeacherDisponibilityWidget->resize(1231, 551);
        TeacherDisponibilityWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        titleLabel = new QLabel(TeacherDisponibilityWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(30, 20, 401, 51));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 36px;\n"
"color: black;"));
        searchLineEdit = new QLineEdit(TeacherDisponibilityWidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(30, 90, 721, 41));
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: #e0e0e0;\n"
"border-radius: 20px;\n"
"padding-left: 15px;\n"
"font-size: 14px;\n"
"color: #606060;"));
        addTeacherButton = new QPushButton(TeacherDisponibilityWidget);
        addTeacherButton->setObjectName(QString::fromUtf8("addTeacherButton"));
        addTeacherButton->setGeometry(QRect(780, 90, 151, 41));
        addTeacherButton->setCursor(QCursor(Qt::PointingHandCursor));
        addTeacherButton->setStyleSheet(QString::fromUtf8("background-color: #333333;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        scrollArea = new QScrollArea(TeacherDisponibilityWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(30, 150, 1171, 381));
        scrollArea->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: transparent;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1171, 381));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        teacherCard = new QFrame(scrollAreaWidgetContents);
        teacherCard->setObjectName(QString::fromUtf8("teacherCard"));
        teacherCard->setMinimumSize(QSize(550, 300));
        teacherCard->setStyleSheet(QString::fromUtf8("background-color: #f9f9f9;\n"
"border-radius: 5px;"));
        teacherNameLabel = new QLabel(teacherCard);
        teacherNameLabel->setObjectName(QString::fromUtf8("teacherNameLabel"));
        teacherNameLabel->setGeometry(QRect(10, 10, 301, 31));
        teacherNameLabel->setStyleSheet(QString::fromUtf8("font-size: 18px;\n"
"color: black;\n"
"font-weight: bold;"));
        editButton = new QPushButton(teacherCard);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setGeometry(QRect(530, 10, 91, 31));
        editButton->setStyleSheet(QString::fromUtf8("background-color: #333333;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        scheduleTable = new QTableWidget(teacherCard);
        if (scheduleTable->columnCount() < 6)
            scheduleTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        scheduleTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        scheduleTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        scheduleTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        scheduleTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        scheduleTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        scheduleTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (scheduleTable->rowCount() < 9)
            scheduleTable->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        scheduleTable->setItem(0, 0, __qtablewidgetitem6);
        scheduleTable->setObjectName(QString::fromUtf8("scheduleTable"));
        scheduleTable->setGeometry(QRect(10, 50, 621, 301));
        scheduleTable->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"    background-color: #4a5c8c;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border: 1px solid #fff;\n"
"    font-size: 10px;\n"
"}\n"
"QTableWidget {\n"
"    gridline-color: #fff;\n"
"    background-color: #4a5c8c;\n"
"    color: white;\n"
"    font-size: 10px;\n"
"}\n"
"QTableWidget::item {\n"
"    border: 1px solid #fff;\n"
"}"));
        scheduleTable->setRowCount(9);
        scheduleTable->setColumnCount(6);

        gridLayout->addWidget(teacherCard, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(TeacherDisponibilityWidget);

        QMetaObject::connectSlotsByName(TeacherDisponibilityWidget);
    } // setupUi

    void retranslateUi(QWidget *TeacherDisponibilityWidget)
    {
        TeacherDisponibilityWidget->setWindowTitle(QCoreApplication::translate("TeacherDisponibilityWidget", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "Disponibilidad Maestros", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("TeacherDisponibilityWidget", "Search", nullptr));
        addTeacherButton->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "+ Agregar Maestro", nullptr));
        teacherNameLabel->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "Nombre del Maestro", nullptr));
        editButton->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "Editar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = scheduleTable->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "L", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = scheduleTable->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "M", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = scheduleTable->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "M", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = scheduleTable->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "J", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = scheduleTable->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "V", nullptr));

        const bool __sortingEnabled = scheduleTable->isSortingEnabled();
        scheduleTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem5 = scheduleTable->item(0, 0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("TeacherDisponibilityWidget", "7:00 - 7:54", nullptr));
        scheduleTable->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class TeacherDisponibilityWidget: public Ui_TeacherDisponibilityWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHERDISPONIBILITYWIDGET_H
