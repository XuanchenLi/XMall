/********************************************************************************
** Form generated from reading UI file 'alertwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALERTWINDOW_H
#define UI_ALERTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlertWindow
{
public:
    QLabel *messageLabel;
    QPushButton *ackPushButton;

    void setupUi(QWidget *AlertWindow)
    {
        if (AlertWindow->objectName().isEmpty())
            AlertWindow->setObjectName(QString::fromUtf8("AlertWindow"));
        AlertWindow->resize(279, 145);
        AlertWindow->setStyleSheet(QString::fromUtf8("*{\n"
"background:rgb(40, 44, 50);\n"
"color:white;\n"
"}\n"
"\n"
"QFrame{\n"
"border:sold 10px rgba(0 ,0, 0)\n"
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
""));
        messageLabel = new QLabel(AlertWindow);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setGeometry(QRect(20, 20, 241, 71));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(11);
        messageLabel->setFont(font);
        messageLabel->setAlignment(Qt::AlignCenter);
        ackPushButton = new QPushButton(AlertWindow);
        ackPushButton->setObjectName(QString::fromUtf8("ackPushButton"));
        ackPushButton->setGeometry(QRect(70, 100, 141, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(12);
        ackPushButton->setFont(font1);
        ackPushButton->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(AlertWindow);

        QMetaObject::connectSlotsByName(AlertWindow);
    } // setupUi

    void retranslateUi(QWidget *AlertWindow)
    {
        AlertWindow->setWindowTitle(QCoreApplication::translate("AlertWindow", "Form", nullptr));
        messageLabel->setText(QCoreApplication::translate("AlertWindow", "TextLabel", nullptr));
        ackPushButton->setText(QCoreApplication::translate("AlertWindow", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AlertWindow: public Ui_AlertWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALERTWINDOW_H
