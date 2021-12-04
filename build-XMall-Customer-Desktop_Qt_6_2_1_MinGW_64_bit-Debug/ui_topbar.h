/********************************************************************************
** Form generated from reading UI file 'topbar.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOPBAR_H
#define UI_TOPBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TopBar
{
public:
    QPushButton *exitPushButton;
    QPushButton *minimizePushButton;
    QPushButton *screenPushButton;

    void setupUi(QWidget *TopBar)
    {
        if (TopBar->objectName().isEmpty())
            TopBar->setObjectName(QString::fromUtf8("TopBar"));
        TopBar->resize(941, 27);
        exitPushButton = new QPushButton(TopBar);
        exitPushButton->setObjectName(QString::fromUtf8("exitPushButton"));
        exitPushButton->setGeometry(QRect(920, 0, 21, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        font.setPointSize(16);
        exitPushButton->setFont(font);
        exitPushButton->setCursor(QCursor(Qt::PointingHandCursor));
        exitPushButton->setFocusPolicy(Qt::NoFocus);
        minimizePushButton = new QPushButton(TopBar);
        minimizePushButton->setObjectName(QString::fromUtf8("minimizePushButton"));
        minimizePushButton->setGeometry(QRect(880, -10, 20, 31));
        minimizePushButton->setFont(font);
        minimizePushButton->setCursor(QCursor(Qt::PointingHandCursor));
        screenPushButton = new QPushButton(TopBar);
        screenPushButton->setObjectName(QString::fromUtf8("screenPushButton"));
        screenPushButton->setGeometry(QRect(900, 0, 21, 21));

        retranslateUi(TopBar);

        QMetaObject::connectSlotsByName(TopBar);
    } // setupUi

    void retranslateUi(QWidget *TopBar)
    {
        TopBar->setWindowTitle(QCoreApplication::translate("TopBar", "Form", nullptr));
        exitPushButton->setText(QCoreApplication::translate("TopBar", "\303\227", nullptr));
        minimizePushButton->setText(QCoreApplication::translate("TopBar", "_", nullptr));
        screenPushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TopBar: public Ui_TopBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOPBAR_H
