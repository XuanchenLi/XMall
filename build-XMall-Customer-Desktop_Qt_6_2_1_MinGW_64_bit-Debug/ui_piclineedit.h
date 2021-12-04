/********************************************************************************
** Form generated from reading UI file 'piclineedit.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICLINEEDIT_H
#define UI_PICLINEEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PicLineEdit
{
public:
    QLabel *picLabel;
    QLineEdit *lineEdit;

    void setupUi(QWidget *PicLineEdit)
    {
        if (PicLineEdit->objectName().isEmpty())
            PicLineEdit->setObjectName(QString::fromUtf8("PicLineEdit"));
        PicLineEdit->resize(303, 32);
        picLabel = new QLabel(PicLineEdit);
        picLabel->setObjectName(QString::fromUtf8("picLabel"));
        picLabel->setGeometry(QRect(0, 0, 31, 31));
        picLabel->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(PicLineEdit);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 0, 271, 31));

        retranslateUi(PicLineEdit);

        QMetaObject::connectSlotsByName(PicLineEdit);
    } // setupUi

    void retranslateUi(QWidget *PicLineEdit)
    {
        PicLineEdit->setWindowTitle(QCoreApplication::translate("PicLineEdit", "Form", nullptr));
        picLabel->setText(QCoreApplication::translate("PicLineEdit", "Pic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PicLineEdit: public Ui_PicLineEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICLINEEDIT_H
