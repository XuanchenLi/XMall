/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QFrame *mainFrame;
    QLineEdit *accountLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginPushButton;
    QPushButton *quitPushButton;
    QLabel *titleLabel;
    QLabel *logoLabel;
    QToolButton *minimizeToolButton;
    QToolButton *quitToolButton;
    QFrame *subFrame;
    QLabel *registerLabel;
    QPushButton *registerPushButton;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(480, 270);
        Login->setMinimumSize(QSize(0, 0));
        Login->setMaximumSize(QSize(1280, 580));
        Login->setStyleSheet(QString::fromUtf8("*{\n"
"background:rgb(40, 44, 50);\n"
"color:white;\n"
"}\n"
"\n"
"QFrame{\n"
"border:sold 10px rgba(0 ,0, 0)\n"
"}\n"
"\n"
"#subFrame{\n"
"border-top-width:1px;\n"
"border-top-style:solid;\n"
"border-top-color:QLinearGradient(x1:0, y1: 1, x2: 1, y2: 1, stop: 0 white , stop: 1 black);\n"
"}\n"
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
"#loginPushButton{\n"
"border:0px solid ;\n"
"border-radius:3px; \n"
"}\n"
"\n"
"#loginPushButton:pressed{\n"
"border:1px solid;\n"
"border-radius:3px; \n"
"}\n"
"\n"
"QLineEdit{\n"
"border: 1px sol"
                        "id #A0A0A0;\n"
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
        mainFrame = new QFrame(Login);
        mainFrame->setObjectName(QString::fromUtf8("mainFrame"));
        mainFrame->setGeometry(QRect(0, 0, 480, 270));
        mainFrame->setFrameShape(QFrame::StyledPanel);
        mainFrame->setFrameShadow(QFrame::Raised);
        accountLineEdit = new QLineEdit(mainFrame);
        accountLineEdit->setObjectName(QString::fromUtf8("accountLineEdit"));
        accountLineEdit->setGeometry(QRect(70, 60, 341, 31));
        passwordLineEdit = new QLineEdit(mainFrame);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setGeometry(QRect(70, 110, 341, 31));
        loginPushButton = new QPushButton(mainFrame);
        loginPushButton->setObjectName(QString::fromUtf8("loginPushButton"));
        loginPushButton->setGeometry(QRect(70, 160, 161, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        loginPushButton->setFont(font);
        loginPushButton->setCursor(QCursor(Qt::PointingHandCursor));
        quitPushButton = new QPushButton(mainFrame);
        quitPushButton->setObjectName(QString::fromUtf8("quitPushButton"));
        quitPushButton->setGeometry(QRect(250, 160, 161, 31));
        quitPushButton->setFont(font);
        quitPushButton->setCursor(QCursor(Qt::PointingHandCursor));
        titleLabel = new QLabel(mainFrame);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(10, 0, 71, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(10);
        font1.setBold(true);
        titleLabel->setFont(font1);
        logoLabel = new QLabel(mainFrame);
        logoLabel->setObjectName(QString::fromUtf8("logoLabel"));
        logoLabel->setGeometry(QRect(210, 10, 49, 49));
        logoLabel->setAlignment(Qt::AlignCenter);
        minimizeToolButton = new QToolButton(mainFrame);
        minimizeToolButton->setObjectName(QString::fromUtf8("minimizeToolButton"));
        minimizeToolButton->setGeometry(QRect(440, -10, 20, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Consolas")});
        font2.setPointSize(16);
        font2.setBold(true);
        minimizeToolButton->setFont(font2);
        quitToolButton = new QToolButton(mainFrame);
        quitToolButton->setObjectName(QString::fromUtf8("quitToolButton"));
        quitToolButton->setGeometry(QRect(460, 0, 20, 20));
        quitToolButton->setFont(font2);
        subFrame = new QFrame(Login);
        subFrame->setObjectName(QString::fromUtf8("subFrame"));
        subFrame->setGeometry(QRect(0, 210, 480, 80));
        subFrame->setMinimumSize(QSize(0, 0));
        subFrame->setMaximumSize(QSize(16777215, 80));
        subFrame->setFrameShape(QFrame::StyledPanel);
        subFrame->setFrameShadow(QFrame::Raised);
        registerLabel = new QLabel(subFrame);
        registerLabel->setObjectName(QString::fromUtf8("registerLabel"));
        registerLabel->setGeometry(QRect(70, 20, 141, 21));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font3.setPointSize(11);
        registerLabel->setFont(font3);
        registerPushButton = new QPushButton(subFrame);
        registerPushButton->setObjectName(QString::fromUtf8("registerPushButton"));
        registerPushButton->setGeometry(QRect(210, 10, 201, 31));
        registerPushButton->setFont(font);
        registerPushButton->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login", nullptr));
        accountLineEdit->setText(QString());
        accountLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "\346\211\213\346\234\272\345\217\267\347\231\273\345\275\225", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        loginPushButton->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        quitPushButton->setText(QCoreApplication::translate("Login", "\345\217\226\346\266\210", nullptr));
        titleLabel->setText(QCoreApplication::translate("Login", "XMall \347\231\273\345\275\225", nullptr));
        logoLabel->setText(QCoreApplication::translate("Login", "logo", nullptr));
        minimizeToolButton->setText(QCoreApplication::translate("Login", "_", nullptr));
        quitToolButton->setText(QCoreApplication::translate("Login", "\303\227", nullptr));
        registerLabel->setText(QCoreApplication::translate("Login", "\350\277\230\346\262\241\346\234\211 XMall \350\264\246\346\210\267\357\274\237", nullptr));
        registerPushButton->setText(QCoreApplication::translate("Login", "\345\210\233\345\273\272\344\270\200\344\270\252\346\226\260\347\232\204\350\264\246\346\210\267...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
