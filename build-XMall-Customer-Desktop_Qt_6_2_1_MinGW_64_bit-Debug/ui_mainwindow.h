/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("*{\n"
"background:rgb(40, 44, 50);\n"
"color:white;\n"
"}\n"
"\n"
"QFrame{\n"
"border:sold 10px rgba(0 ,0, 0)\n"
"}\n"
"\n"
"\n"
"QLineEdit{\n"
"background-color:rgb(58. 104. 148);\n"
"}\n"
"\n"
"QPushButton{\n"
"background-color:QLinearGradient(x1:0, y1: 0, x2: 1, y2: 0, stop: 0 rgb(71,191,255) , stop: 1 rgb(23, 78, 115));\n"
"border-style:solid;\n"
"border-color:white;\n"
"border-radius:3px;\n"
"border:0px solid ;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"background-color:QLinearGradient(x1:0, y1: 0, x2: 1, y2: 0, stop: 0 rgb(71,191,255) , stop: 1 rgb(23, 78, 115));\n"
"border-style:solid;\n"
"border-radius:3px;\n"
"border:1px solid;\n"
"}\n"
"\n"
"\n"
"\n"
"QLineEdit{\n"
"border: 1px solid #A0A0A0;\n"
"background-color:rgb(65, 65, 65);\n"
"color:white;\n"
"}\n"
"\n"
"\n"
"QLineEdit:hover { \n"
"	border: 1px solid #298DFF;\n"
"	border-radius: 3px;\n"
"	selection-color: #F2F2F2;\n"
"}\n"
"\n"
"QLineEdit[EchoMode=\"2\"] {lineedit-password-character:42;}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "XMall", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
