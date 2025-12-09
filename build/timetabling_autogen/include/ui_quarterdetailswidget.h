/********************************************************************************
** Form generated from reading UI file 'quarterdetailswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUARTERDETAILSWIDGET_H
#define UI_QUARTERDETAILSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuarterDetailsWidget
{
public:
    QFrame *topBar;
    QPushButton *backButton;
    QPushButton *applyButton;
    QLabel *titleLabel;
    QLabel *subjectsLabel;
    QTableWidget *subjectsTable;
    QPushButton *addSubjectButton;

    void setupUi(QWidget *QuarterDetailsWidget)
    {
        if (QuarterDetailsWidget->objectName().isEmpty())
            QuarterDetailsWidget->setObjectName(QString::fromUtf8("QuarterDetailsWidget"));
        QuarterDetailsWidget->resize(1231, 551);
        QuarterDetailsWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        topBar = new QFrame(QuarterDetailsWidget);
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
        applyButton = new QPushButton(topBar);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));
        applyButton->setGeometry(QRect(1050, 15, 151, 31));
        applyButton->setCursor(QCursor(Qt::PointingHandCursor));
        applyButton->setStyleSheet(QString::fromUtf8("background-color: #2ecc71;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        titleLabel = new QLabel(QuarterDetailsWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(160, 80, 401, 41));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 32px;\n"
"color: black;\n"
"font-weight: bold;"));
        subjectsLabel = new QLabel(QuarterDetailsWidget);
        subjectsLabel->setObjectName(QString::fromUtf8("subjectsLabel"));
        subjectsLabel->setGeometry(QRect(160, 130, 101, 21));
        subjectsLabel->setStyleSheet(QString::fromUtf8("font-size: 14px;\n"
"color: #555;"));
        subjectsTable = new QTableWidget(QuarterDetailsWidget);
        if (subjectsTable->columnCount() < 2)
            subjectsTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        subjectsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        subjectsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (subjectsTable->rowCount() < 1)
            subjectsTable->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        subjectsTable->setItem(0, 0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        subjectsTable->setItem(0, 1, __qtablewidgetitem3);
        subjectsTable->setObjectName(QString::fromUtf8("subjectsTable"));
        subjectsTable->setGeometry(QRect(160, 160, 601, 201));
        subjectsTable->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"    background-color: #5c7c9e;\n"
"    color: white;\n"
"    font-weight: bold;\n"
"    border: 1px solid #fff;\n"
"}\n"
"QTableWidget {\n"
"    gridline-color: #fff;\n"
"    background-color: #5c7c9e;\n"
"    color: white;\n"
"}\n"
"QTableWidget::item {\n"
"    border: 1px solid #fff;\n"
"}"));
        subjectsTable->setColumnCount(2);
        addSubjectButton = new QPushButton(QuarterDetailsWidget);
        addSubjectButton->setObjectName(QString::fromUtf8("addSubjectButton"));
        addSubjectButton->setGeometry(QRect(630, 370, 131, 31));
        addSubjectButton->setCursor(QCursor(Qt::PointingHandCursor));
        addSubjectButton->setStyleSheet(QString::fromUtf8("background-color: #d4ac0d;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));

        retranslateUi(QuarterDetailsWidget);

        QMetaObject::connectSlotsByName(QuarterDetailsWidget);
    } // setupUi

    void retranslateUi(QWidget *QuarterDetailsWidget)
    {
        QuarterDetailsWidget->setWindowTitle(QCoreApplication::translate("QuarterDetailsWidget", "Form", nullptr));
        backButton->setText(QCoreApplication::translate("QuarterDetailsWidget", "Regresar", nullptr));
        applyButton->setText(QCoreApplication::translate("QuarterDetailsWidget", "Aplicar Cambios", nullptr));
        titleLabel->setText(QCoreApplication::translate("QuarterDetailsWidget", "Datos del Cuatrimestre", nullptr));
        subjectsLabel->setText(QCoreApplication::translate("QuarterDetailsWidget", "Materias", nullptr));
        QTableWidgetItem *___qtablewidgetitem = subjectsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("QuarterDetailsWidget", "Materias", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = subjectsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("QuarterDetailsWidget", "Horas", nullptr));

        const bool __sortingEnabled = subjectsTable->isSortingEnabled();
        subjectsTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem2 = subjectsTable->item(0, 0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("QuarterDetailsWidget", "Materia", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = subjectsTable->item(0, 1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("QuarterDetailsWidget", "0", nullptr));
        subjectsTable->setSortingEnabled(__sortingEnabled);

        addSubjectButton->setText(QCoreApplication::translate("QuarterDetailsWidget", "+ Agregar materia", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QuarterDetailsWidget: public Ui_QuarterDetailsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUARTERDETAILSWIDGET_H
