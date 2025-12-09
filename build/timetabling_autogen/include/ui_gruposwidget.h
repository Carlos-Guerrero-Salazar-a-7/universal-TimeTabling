/********************************************************************************
** Form generated from reading UI file 'gruposwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRUPOSWIDGET_H
#define UI_GRUPOSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GruposWidget
{
public:
    QLabel *titleLabel;
    QLineEdit *searchLineEdit;
    QPushButton *createGroupButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QFrame *groupItem;
    QLabel *groupNameLabel;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QTableWidget *groupTable;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *GruposWidget)
    {
        if (GruposWidget->objectName().isEmpty())
            GruposWidget->setObjectName(QString::fromUtf8("GruposWidget"));
        GruposWidget->resize(1231, 551);
        GruposWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        titleLabel = new QLabel(GruposWidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(30, 20, 201, 51));
        titleLabel->setStyleSheet(QString::fromUtf8("font-size: 36px;\n"
"color: black;"));
        searchLineEdit = new QLineEdit(GruposWidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(30, 90, 601, 41));
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: #e0e0e0;\n"
"border-radius: 20px;\n"
"padding-left: 15px;\n"
"font-size: 14px;\n"
"color: #606060;"));
        createGroupButton = new QPushButton(GruposWidget);
        createGroupButton->setObjectName(QString::fromUtf8("createGroupButton"));
        createGroupButton->setGeometry(QRect(660, 90, 131, 41));
        createGroupButton->setCursor(QCursor(Qt::PointingHandCursor));
        createGroupButton->setStyleSheet(QString::fromUtf8("background-color: #4cd964;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        scrollArea = new QScrollArea(GruposWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(30, 150, 801, 381));
        scrollArea->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: transparent;"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 801, 381));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupItem = new QFrame(scrollAreaWidgetContents);
        groupItem->setObjectName(QString::fromUtf8("groupItem"));
        groupItem->setMinimumSize(QSize(0, 200));
        groupItem->setStyleSheet(QString::fromUtf8("background-color: #f9f9f9;\n"
"border-radius: 5px;"));
        groupNameLabel = new QLabel(groupItem);
        groupNameLabel->setObjectName(QString::fromUtf8("groupNameLabel"));
        groupNameLabel->setGeometry(QRect(10, 10, 201, 31));
        groupNameLabel->setStyleSheet(QString::fromUtf8("font-size: 18px;\n"
"color: black;\n"
"font-weight: bold;"));
        deleteButton = new QPushButton(groupItem);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(580, 10, 91, 31));
        deleteButton->setStyleSheet(QString::fromUtf8("background-color: #e74c3c;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        editButton = new QPushButton(groupItem);
        editButton->setObjectName(QString::fromUtf8("editButton"));
        editButton->setGeometry(QRect(690, 10, 91, 31));
        editButton->setStyleSheet(QString::fromUtf8("background-color: #d4ac0d;\n"
"color: white;\n"
"border-radius: 5px;\n"
"font-weight: bold;"));
        groupTable = new QTableWidget(groupItem);
        if (groupTable->columnCount() < 3)
            groupTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        groupTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        groupTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        groupTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (groupTable->rowCount() < 1)
            groupTable->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        groupTable->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        groupTable->setItem(0, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        groupTable->setItem(0, 2, __qtablewidgetitem5);
        groupTable->setObjectName(QString::fromUtf8("groupTable"));
        groupTable->setGeometry(QRect(10, 50, 771, 141));
        groupTable->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
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
        groupTable->setColumnCount(3);

        verticalLayout->addWidget(groupItem);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(GruposWidget);

        QMetaObject::connectSlotsByName(GruposWidget);
    } // setupUi

    void retranslateUi(QWidget *GruposWidget)
    {
        GruposWidget->setWindowTitle(QCoreApplication::translate("GruposWidget", "Form", nullptr));
        titleLabel->setText(QCoreApplication::translate("GruposWidget", "Grupos", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("GruposWidget", "Search", nullptr));
        createGroupButton->setText(QCoreApplication::translate("GruposWidget", "+ Crear Grupo", nullptr));
        groupNameLabel->setText(QCoreApplication::translate("GruposWidget", "Nombre del Grupo", nullptr));
        deleteButton->setText(QCoreApplication::translate("GruposWidget", "Eliminar", nullptr));
        editButton->setText(QCoreApplication::translate("GruposWidget", "Editar", nullptr));
        QTableWidgetItem *___qtablewidgetitem = groupTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("GruposWidget", "Materias", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = groupTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("GruposWidget", "Horas", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = groupTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("GruposWidget", "Maestro", nullptr));

        const bool __sortingEnabled = groupTable->isSortingEnabled();
        groupTable->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = groupTable->item(0, 0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("GruposWidget", "Materia", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = groupTable->item(0, 1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("GruposWidget", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = groupTable->item(0, 2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("GruposWidget", "Maestro", nullptr));
        groupTable->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class GruposWidget: public Ui_GruposWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRUPOSWIDGET_H
