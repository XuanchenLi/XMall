#include "menulistwidget.h"
#include "ui_menulistwidget.h"
#include <QLabel>
#include <QSplitter>
#include <QListWidget>
MenuListWidget::MenuListWidget(QObject *parent) :
    QWidgetAction(parent)
{

}

MenuListWidget::~MenuListWidget()
{

}

QWidget* MenuListWidget::createWidget(QWidget *parent)
{
    if(parent->inherits("QMenu")||parent->inherits("QToolBarr"))
    {
        // Splitter ??? Why!
        //QGridLayout *pLayout = new QGridLayout();
        QSplitter *splitter = new QSplitter(parent);
        QLabel *label = new QLabel;
        label->setText("类别1");
        splitter->addWidget(label);
        QListWidget* list1 = new QListWidget;
        list1->insertItem(0,tr("hah"));
        list1->insertItem(1,tr("hah2"));
        list1->insertItem(3,tr("hah3"));
        splitter->addWidget(list1);
        QLabel *label2 = new QLabel;
        label2->setText("类别2");
        splitter->addWidget(label2);
        QListWidget* list2 = new QListWidget;
        list2->insertItem(0,tr("hah"));
        list2->insertItem(1,tr("hah2"));
        list2->insertItem(3,tr("hah3"));
        splitter->addWidget(list2);
        return splitter;
    }
    return nullptr;
}
