#include "menulistwidget.h"
#include "ui_menulistwidget.h"
#include "menulistitem.h"
#include <QLabel>
#include <QSplitter>
#include <QListWidget>
MenuListWidget::MenuListWidget(QObject *parent,QVector<CategoryEntity>* category1 ,QVector<CategoryEntity>* category2 ,int start, int end) :
    QWidgetAction(parent),
    start(start),end(end),
    category1(category1),
    category2(category2)
{

}

MenuListWidget::~MenuListWidget()
{

}

QWidget* MenuListWidget::createWidget(QWidget *parent)
{

    if(parent->inherits("QMenu")||parent->inherits("QToolBarr"))
    {
        QSplitter *splitter = new QSplitter(parent);
        splitter->setMaximumWidth(500);
        for (int i = start; i <= end; ++i)
        {
            QSplitter *subSplitter = new QSplitter(Qt::Vertical, splitter);
            CategoryEntity root = category1->at(i);
            QLabel *label = new QLabel(root.getName(),subSplitter);
            label->setStyleSheet("color:rgb(46, 191, 255);");
            QListWidget* list = new QListWidget(subSplitter);
            for (int i = 0 ; i < category2->length(); ++i)
            {
                CategoryEntity category = category2->at(i);
                //qDebug()<<category1;
                //qDebug()<<category2;

                if(category.getParentId() == root.getId())
                {
                    //qDebug()<<category.getName();
                    MenuListItem* item = new MenuListItem();
                    item->setCategoryEntity(category);
                    item->setText(category.getName());
                    QListWidgetItem* pItem = new QListWidgetItem();
                    connect(item, &MenuListItem::changeCategory,father, &MainWindow::on_changeCategory);
                    list->addItem(pItem);
                    //item->setMaximumSize(110,25);
                    pItem->setSizeHint(item->size());
                    list->setItemWidget(pItem,item);
                }
            }

        }
        return splitter;
    }
    return nullptr;
}

MainWindow *MenuListWidget::getFather() const
{
    return father;
}

void MenuListWidget::setFather(MainWindow *newFather)
{
    father = newFather;
}

