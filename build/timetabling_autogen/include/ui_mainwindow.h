/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *navegation;
    QPushButton *generationButton;
    QPushButton *teacherDisponibilityButton;
    QPushButton *schedulesButton;
    QPushButton *cuatrimestresButton;
    QPushButton *groupButton;
    QPushButton *salonesButton;
    QLabel *sectionTitle;
    QStackedWidget *stackedWidget;
    QMenuBar *menubar;
    QMenu *menuTimetabling;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1231, 634);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: white;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        navegation = new QFrame(centralwidget);
        navegation->setObjectName(QString::fromUtf8("navegation"));
        navegation->setGeometry(QRect(0, 0, 1231, 61));
        navegation->setAutoFillBackground(false);
        navegation->setStyleSheet(QString::fromUtf8("background-color: #3498db; \n"
"color: black;\n"
"font-weight: semi-bold;       \n"
"font-size: 14px;"));
        navegation->setFrameShape(QFrame::Shape::StyledPanel);
        navegation->setFrameShadow(QFrame::Shadow::Raised);
        generationButton = new QPushButton(navegation);
        generationButton->setObjectName(QString::fromUtf8("generationButton"));
        generationButton->setGeometry(QRect(1100, 10, 111, 41));
        generationButton->setCursor(QCursor(Qt::PointingHandCursor));
        generationButton->setAutoFillBackground(false);
        generationButton->setStyleSheet(QString::fromUtf8("/* Estado Normal */\n"
"QPushButton {\n"
"    background-color: rgb(246, 245, 244);\n"
"    color: black;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Estado Hover (Cuando pasas el mouse) */\n"
"QPushButton:hover {\n"
"    background-color: rgb(153, 193, 241); /* Se pone verde */\n"
"}\n"
"\n"
"/* Estado Pressed (Cuando haces clic) */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(98, 160, 234);\n"
"} "));
        teacherDisponibilityButton = new QPushButton(navegation);
        teacherDisponibilityButton->setObjectName(QString::fromUtf8("teacherDisponibilityButton"));
        teacherDisponibilityButton->setGeometry(QRect(900, 10, 191, 41));
        teacherDisponibilityButton->setCursor(QCursor(Qt::PointingHandCursor));
        teacherDisponibilityButton->setAutoFillBackground(false);
        teacherDisponibilityButton->setStyleSheet(QString::fromUtf8("/* Estado Normal */\n"
"QPushButton {\n"
"    background-color: rgb(246, 245, 244);\n"
"    color: black;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Estado Hover (Cuando pasas el mouse) */\n"
"QPushButton:hover {\n"
"    background-color: rgb(153, 193, 241); /* Se pone verde */\n"
"}\n"
"\n"
"/* Estado Pressed (Cuando haces clic) */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(98, 160, 234);\n"
"} "));
        schedulesButton = new QPushButton(navegation);
        schedulesButton->setObjectName(QString::fromUtf8("schedulesButton"));
        schedulesButton->setGeometry(QRect(790, 10, 101, 41));
        schedulesButton->setCursor(QCursor(Qt::PointingHandCursor));
        schedulesButton->setAutoFillBackground(false);
        schedulesButton->setStyleSheet(QString::fromUtf8("/* Estado Normal */\n"
"QPushButton {\n"
"    background-color: rgb(246, 245, 244);\n"
"    color: black;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Estado Hover (Cuando pasas el mouse) */\n"
"QPushButton:hover {\n"
"    background-color: rgb(153, 193, 241); /* Se pone verde */\n"
"}\n"
"\n"
"/* Estado Pressed (Cuando haces clic) */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(98, 160, 234);\n"
"} "));
        cuatrimestresButton = new QPushButton(navegation);
        cuatrimestresButton->setObjectName(QString::fromUtf8("cuatrimestresButton"));
        cuatrimestresButton->setGeometry(QRect(650, 10, 131, 41));
        cuatrimestresButton->setCursor(QCursor(Qt::PointingHandCursor));
        cuatrimestresButton->setAutoFillBackground(false);
        cuatrimestresButton->setStyleSheet(QString::fromUtf8("/* Estado Normal */\n"
"QPushButton {\n"
"    background-color: rgb(246, 245, 244);\n"
"    color: black;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Estado Hover (Cuando pasas el mouse) */\n"
"QPushButton:hover {\n"
"    background-color: rgb(153, 193, 241); /* Se pone verde */\n"
"}\n"
"\n"
"/* Estado Pressed (Cuando haces clic) */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(98, 160, 234);\n"
"} "));
        cuatrimestresButton->setAutoDefault(false);
        groupButton = new QPushButton(navegation);
        groupButton->setObjectName(QString::fromUtf8("groupButton"));
        groupButton->setGeometry(QRect(550, 10, 91, 41));
        groupButton->setCursor(QCursor(Qt::PointingHandCursor));
        groupButton->setAutoFillBackground(false);
        groupButton->setStyleSheet(QString::fromUtf8("/* Estado Normal */\n"
"QPushButton {\n"
"    background-color: rgb(246, 245, 244);\n"
"    color: black;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Estado Hover (Cuando pasas el mouse) */\n"
"QPushButton:hover {\n"
"    background-color: rgb(153, 193, 241); /* Se pone verde */\n"
"}\n"
"\n"
"/* Estado Pressed (Cuando haces clic) */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(98, 160, 234);\n"
"} "));
        salonesButton = new QPushButton(navegation);
        salonesButton->setObjectName(QString::fromUtf8("salonesButton"));
        salonesButton->setGeometry(QRect(450, 10, 91, 41));
        salonesButton->setCursor(QCursor(Qt::PointingHandCursor));
        salonesButton->setAutoFillBackground(false);
        salonesButton->setStyleSheet(QString::fromUtf8("/* Estado Normal */\n"
"QPushButton {\n"
"    background-color: rgb(246, 245, 244);\n"
"    color: black;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Estado Hover (Cuando pasas el mouse) */\n"
"QPushButton:hover {\n"
"    background-color: rgb(153, 193, 241); /* Se pone verde */\n"
"}\n"
"\n"
"/* Estado Pressed (Cuando haces clic) */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(98, 160, 234);\n"
"} "));
        sectionTitle = new QLabel(navegation);
        sectionTitle->setObjectName(QString::fromUtf8("sectionTitle"));
        sectionTitle->setGeometry(QRect(30, 10, 151, 41));
        sectionTitle->setStyleSheet(QString::fromUtf8("font-size: 28px;\n"
"color: white;"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 60, 1231, 551));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setEnabled(false);
        menubar->setGeometry(QRect(0, 0, 1231, 23));
        menubar->setAutoFillBackground(false);
        menubar->setStyleSheet(QString::fromUtf8("background-color: rrgb(119, 118, 123);"));
        menuTimetabling = new QMenu(menubar);
        menuTimetabling->setObjectName(QString::fromUtf8("menuTimetabling"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuTimetabling->menuAction());

        retranslateUi(MainWindow);

        cuatrimestresButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        generationButton->setText(QCoreApplication::translate("MainWindow", "Generacion", nullptr));
        teacherDisponibilityButton->setText(QCoreApplication::translate("MainWindow", "Disponibilidad Maestros", nullptr));
        schedulesButton->setText(QCoreApplication::translate("MainWindow", "Horarios", nullptr));
        cuatrimestresButton->setText(QCoreApplication::translate("MainWindow", "Cuatrimestres", nullptr));
        groupButton->setText(QCoreApplication::translate("MainWindow", "Grupos", nullptr));
        salonesButton->setText(QCoreApplication::translate("MainWindow", "Salones", nullptr));
        sectionTitle->setText(QCoreApplication::translate("MainWindow", "Generacion", nullptr));
        menuTimetabling->setTitle(QCoreApplication::translate("MainWindow", "Timetabling", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
