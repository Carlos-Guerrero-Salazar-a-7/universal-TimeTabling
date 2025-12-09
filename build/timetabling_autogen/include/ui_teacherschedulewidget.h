/********************************************************************************
** Form generated from reading UI file 'teacherschedulewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHERSCHEDULEWIDGET_H
#define UI_TEACHERSCHEDULEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TeacherScheduleWidget
{
public:
    QFrame *topBar;
    QPushButton *backButton;
    QPushButton *exportButton;
    QLabel *nameLabel;
    QTableWidget *scheduleTable;

    void setupUi(QWidget *TeacherScheduleWidget)
    {
        if (TeacherScheduleWidget->objectName().isEmpty())
            TeacherScheduleWidget->setObjectName(QString::fromUtf8("TeacherScheduleWidget"));
        TeacherScheduleWidget->resize(1231, 551);
        TeacherScheduleWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        topBar = new QFrame(TeacherScheduleWidget);
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
        exportButton = new QPushButton(topBar);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setGeometry(QRect(1090, 15, 111, 31));
        exportButton->setCursor(QCursor(Qt::PointingHandCursor));
        exportButton->setStyleSheet(QString::fromUtf8("background-color: #2ecc71;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        nameLabel = new QLabel(TeacherScheduleWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(160, 80, 301, 41));
        nameLabel->setStyleSheet(QString::fromUtf8("font-size: 24px;\n"
"color: #555;\n"
"font-weight: bold;"));
        scheduleTable = new QTableWidget(TeacherScheduleWidget);
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
        if (scheduleTable->rowCount() < 10)
            scheduleTable->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        scheduleTable->setItem(0, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        scheduleTable->setItem(1, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        scheduleTable->setItem(2, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        scheduleTable->setItem(3, 0, __qtablewidgetitem9);
        scheduleTable->setObjectName(QString::fromUtf8("scheduleTable"));
        scheduleTable->setGeometry(QRect(260, 150, 631, 331));
        scheduleTable->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"    background-color: #4a5c8c;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border: 1px solid #ddd;\n"
"}\n"
"QTableWidget {\n"
"    gridline-color: #ddd;\n"
"}\n"
"QTableWidget::item {\n"
"    border: 1px solid #ddd;\n"
"}"));
        scheduleTable->setRowCount(10);
        scheduleTable->setColumnCount(6);

        retranslateUi(TeacherScheduleWidget);

        QMetaObject::connectSlotsByName(TeacherScheduleWidget);
    } // setupUi

    void retranslateUi(QWidget *TeacherScheduleWidget)
    {
        TeacherScheduleWidget->setWindowTitle(QCoreApplication::translate("TeacherScheduleWidget", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("TeacherScheduleWidget", "Regresar", nullptr));
        exportButton->setText(QCoreApplication::translate("TeacherScheduleWidget", "Exportar", nullptr));
        nameLabel->setText(QCoreApplication::translate("TeacherScheduleWidget", "Nombre", nullptr));
        QTableWidgetItem *___qtablewidgetitem = scheduleTable->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TeacherScheduleWidget", "L", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = scheduleTable->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TeacherScheduleWidget", "M", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = scheduleTable->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("TeacherScheduleWidget", "M", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = scheduleTable->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("TeacherScheduleWidget", "J", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = scheduleTable->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("TeacherScheduleWidget", "V", nullptr));

        const bool __sortingEnabled = scheduleTable->isSortingEnabled();
        scheduleTable->setSortingEnabled(false);
        scheduleTable->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class TeacherScheduleWidget: public Ui_TeacherScheduleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHERSCHEDULEWIDGET_H
