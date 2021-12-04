/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "piclineedit.h"

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QToolButton *minimizeToolButton;
    QToolButton *quitToolButton;
    QFrame *frame;
    QLabel *logoLabel;
    PicLineEdit *phonePicLineEdit;
    PicLineEdit *pswPicLineEdit;
    PicLineEdit *repswPicLineEdit;
    PicLineEdit *emailPicLineEdit;
    PicLineEdit *namePicLineEdit;
    QPushButton *registerPushButton;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName(QString::fromUtf8("Register"));
        Register->resize(430, 588);
        Register->setStyleSheet(QString::fromUtf8("*{\n"
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
        minimizeToolButton = new QToolButton(Register);
        minimizeToolButton->setObjectName(QString::fromUtf8("minimizeToolButton"));
        minimizeToolButton->setGeometry(QRect(390, -10, 20, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        font.setPointSize(16);
        font.setBold(true);
        minimizeToolButton->setFont(font);
        quitToolButton = new QToolButton(Register);
        quitToolButton->setObjectName(QString::fromUtf8("quitToolButton"));
        quitToolButton->setGeometry(QRect(410, 0, 20, 20));
        quitToolButton->setFont(font);
        frame = new QFrame(Register);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 431, 591));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        logoLabel = new QLabel(frame);
        logoLabel->setObjectName(QString::fromUtf8("logoLabel"));
        logoLabel->setGeometry(QRect(180, 20, 60, 60));
        logoLabel->setAlignment(Qt::AlignCenter);
        phonePicLineEdit = new PicLineEdit(frame);
        phonePicLineEdit->setObjectName(QString::fromUtf8("phonePicLineEdit"));
        phonePicLineEdit->setGeometry(QRect(50, 175, 331, 31));
        phonePicLineEdit->setAutoFillBackground(false);
        pswPicLineEdit = new PicLineEdit(frame);
        pswPicLineEdit->setObjectName(QString::fromUtf8("pswPicLineEdit"));
        pswPicLineEdit->setGeometry(QRect(50, 325, 331, 31));
        repswPicLineEdit = new PicLineEdit(frame);
        repswPicLineEdit->setObjectName(QString::fromUtf8("repswPicLineEdit"));
        repswPicLineEdit->setGeometry(QRect(50, 400, 331, 31));
        emailPicLineEdit = new PicLineEdit(frame);
        emailPicLineEdit->setObjectName(QString::fromUtf8("emailPicLineEdit"));
        emailPicLineEdit->setGeometry(QRect(50, 250, 331, 31));
        namePicLineEdit = new PicLineEdit(frame);
        namePicLineEdit->setObjectName(QString::fromUtf8("namePicLineEdit"));
        namePicLineEdit->setGeometry(QRect(50, 100, 331, 31));
        registerPushButton = new QPushButton(frame);
        registerPushButton->setObjectName(QString::fromUtf8("registerPushButton"));
        registerPushButton->setGeometry(QRect(110, 520, 201, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        registerPushButton->setFont(font1);
        registerPushButton->setCursor(QCursor(Qt::PointingHandCursor));
        frame->raise();
        minimizeToolButton->raise();
        quitToolButton->raise();

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "Form", nullptr));
        minimizeToolButton->setText(QCoreApplication::translate("Register", "_", nullptr));
        quitToolButton->setText(QCoreApplication::translate("Register", "\303\227", nullptr));
        logoLabel->setText(QCoreApplication::translate("Register", "LOGO", nullptr));
        registerPushButton->setText(QCoreApplication::translate("Register", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H
