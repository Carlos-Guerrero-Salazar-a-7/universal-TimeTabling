/********************************************************************************
** Form generated from reading UI file 'groupschedulewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPSCHEDULEWIDGET_H
#define UI_GROUPSCHEDULEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupScheduleWidget
{
public:
    QFrame *topBar;
    QPushButton *backButton;
    QPushButton *exportButton;
    QLabel *nameLabel;
    QTableWidget *scheduleTable;

    void setupUi(QWidget *GroupScheduleWidget)
    {
        if (GroupScheduleWidget->objectName().isEmpty())
            GroupScheduleWidget->setObjectName(QString::fromUtf8("GroupScheduleWidget"));
        GroupScheduleWidget->resize(1231, 551);
        GroupScheduleWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        topBar = new QFrame(GroupScheduleWidget);
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
        nameLabel = new QLabel(GroupScheduleWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(160, 80, 301, 41));
        nameLabel->setStyleSheet(QString::fromUtf8("font-size: 24px;\n"
"color: #555;\n"
"font-weight: bold;"));
        scheduleTable = new QTableWidget(GroupScheduleWidget);
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

        retranslateUi(GroupScheduleWidget);

        QMetaObject::connectSlotsByName(GroupScheduleWidget);
    } // setupUi

    void retranslateUi(QWidget *GroupScheduleWidget)
    {
        GroupScheduleWidget->setWindowTitle(QCoreApplication::translate("GroupScheduleWidget", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("GroupScheduleWidget", "Regresar", nullptr));
        exportButton->setText(QCoreApplication::translate("GroupScheduleWidget", "Exportar", nullptr));
        nameLabel->setText(QCoreApplication::translate("GroupScheduleWidget", "Nombre Grupo", nullptr));
        QTableWidgetItem *___qtablewidgetitem = scheduleTable->horizontalHeaderItem(1);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GroupScheduleWidget", "L", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = scheduleTable->horizontalHeaderItem(2);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GroupScheduleWidget", "M", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = scheduleTable->horizontalHeaderItem(3);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GroupScheduleWidget", "M", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = scheduleTable->horizontalHeaderItem(4);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GroupScheduleWidget", "J", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = scheduleTable->horizontalHeaderItem(5);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GroupScheduleWidget", "V", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupScheduleWidget: public Ui_GroupScheduleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPSCHEDULEWIDGET_H
