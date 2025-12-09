/********************************************************************************
** Form generated from reading UI file 'generationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATIONWIDGET_H
#define UI_GENERATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerationWidget
{
public:
    QPlainTextEdit *consoleLog;
    QPushButton *deleteSchedule;
    QPushButton *createSchedule;
    QTextEdit *teachersCountLabel;
    QTextEdit *roomsCountLabel;
    QTextEdit *coursesCountLabel;
    QTextEdit *groupCountLabel;

    void setupUi(QWidget *GenerationWidget)
    {
        if (GenerationWidget->objectName().isEmpty())
            GenerationWidget->setObjectName(QString::fromUtf8("GenerationWidget"));
        GenerationWidget->resize(1231, 551);
        GenerationWidget->setStyleSheet(QString::fromUtf8("background-color: white;"));
        consoleLog = new QPlainTextEdit(GenerationWidget);
        consoleLog->setObjectName(QString::fromUtf8("consoleLog"));
        consoleLog->setGeometry(QRect(270, 150, 691, 341));
        consoleLog->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 56, 70); \n"
"color: white; \n"
"border-radius: 10px"));
        consoleLog->setReadOnly(true);
        deleteSchedule = new QPushButton(GenerationWidget);
        deleteSchedule->setObjectName(QString::fromUtf8("deleteSchedule"));
        deleteSchedule->setGeometry(QRect(270, 120, 131, 26));
        deleteSchedule->setStyleSheet(QString::fromUtf8("/* Estado Normal */\n"
"QPushButton {\n"
"    background-color: rgb(246, 97, 81);\n"
"    color: black;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Estado Hover (Cuando pasas el mouse) */\n"
"QPushButton:hover {\n"
"    background-color: rgb(237, 51, 59); /* Se pone verde */\n"
"}\n"
"\n"
"/* Estado Pressed (Cuando haces clic) */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(165, 29, 45);\n"
"} "));
        createSchedule = new QPushButton(GenerationWidget);
        createSchedule->setObjectName(QString::fromUtf8("createSchedule"));
        createSchedule->setGeometry(QRect(840, 120, 121, 26));
        createSchedule->setStyleSheet(QString::fromUtf8("/* Estado Normal */\n"
"QPushButton {\n"
"    background-color: rgb(87, 227, 137);\n"
"    color: black;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Estado Hover (Cuando pasas el mouse) */\n"
"QPushButton:hover {\n"
"    background-color: rgb(51, 209, 122); /* Se pone verde */\n"
"}\n"
"\n"
"/* Estado Pressed (Cuando haces clic) */\n"
"QPushButton:pressed {\n"
"    background-color: rgb(46, 194, 126);\n"
"} "));
        teachersCountLabel = new QTextEdit(GenerationWidget);
        teachersCountLabel->setObjectName(QString::fromUtf8("teachersCountLabel"));
        teachersCountLabel->setGeometry(QRect(270, 70, 121, 31));
        teachersCountLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(28, 113, 216);\n"
"border-radius: 10px;\n"
""));
        teachersCountLabel->setReadOnly(true);
        roomsCountLabel = new QTextEdit(GenerationWidget);
        roomsCountLabel->setObjectName(QString::fromUtf8("roomsCountLabel"));
        roomsCountLabel->setGeometry(QRect(470, 70, 121, 31));
        roomsCountLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(28, 113, 216);\n"
"border-radius: 10px;\n"
""));
        roomsCountLabel->setReadOnly(true);
        coursesCountLabel = new QTextEdit(GenerationWidget);
        coursesCountLabel->setObjectName(QString::fromUtf8("coursesCountLabel"));
        coursesCountLabel->setGeometry(QRect(670, 70, 121, 31));
        coursesCountLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(28, 113, 216);\n"
"border-radius: 10px;\n"
""));
        coursesCountLabel->setReadOnly(true);
        groupCountLabel = new QTextEdit(GenerationWidget);
        groupCountLabel->setObjectName(QString::fromUtf8("groupCountLabel"));
        groupCountLabel->setGeometry(QRect(840, 70, 121, 31));
        groupCountLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(28, 113, 216);\n"
"border-radius: 10px;\n"
""));
        groupCountLabel->setReadOnly(true);

        retranslateUi(GenerationWidget);

        QMetaObject::connectSlotsByName(GenerationWidget);
    } // setupUi

    void retranslateUi(QWidget *GenerationWidget)
    {
        GenerationWidget->setWindowTitle(QCoreApplication::translate("GenerationWidget", "Form", nullptr));
        deleteSchedule->setText(QCoreApplication::translate("GenerationWidget", "Borrar Horarios", nullptr));
        createSchedule->setText(QCoreApplication::translate("GenerationWidget", "Crear Horarios", nullptr));
        teachersCountLabel->setHtml(QCoreApplication::translate("GenerationWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Maestros: </span></p></body></html>", nullptr));
        roomsCountLabel->setHtml(QCoreApplication::translate("GenerationWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Salones: </span></p></body></html>", nullptr));
        coursesCountLabel->setHtml(QCoreApplication::translate("GenerationWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Materias: </span></p></body></html>", nullptr));
        groupCountLabel->setHtml(QCoreApplication::translate("GenerationWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu Sans'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Grupos: </span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GenerationWidget: public Ui_GenerationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATIONWIDGET_H
