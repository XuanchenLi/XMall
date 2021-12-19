#include "orderlistwidget.h"
#include "ui_orderlistwidget.h"
#include "Service/HttpProxy.h"
#include "orderlistitem.h"
#include <QJsonArray>
extern QString GET_HOST();
OrderListWidget::OrderListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderListWidget)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(msliderChanged(int)),  this , SLOT(onScrollBarMoved(int)));
    connect(ui->listWidget, SIGNAL(reachedBottom()),  this , SLOT(onReachedBottom()));
}

OrderListWidget::~OrderListWidget()
{
    clear();
    delete ui;
}
void  OrderListWidget::onScrollBarMoved( int  v)
{

}

void  OrderListWidget::onReachedBottom()
{

}

void OrderListWidget::setVector(QString orderSn)
{
    clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/item/orderSn/" + orderSn);
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray items = jsonObject["orderItemEntityList"].toArray();
        for (int i =0; i<items.count(); ++i)
        {
            OrderListItem* item = new OrderListItem;
            item->setItem(OrderItemEntity::parseJson(items[i].toObject()));
            itemVector.push_back(item);
        }
    }
//    for (int i =0; i<items.count(); ++i)
//    {
//        OrderListItem* item = new OrderListItem;
//        item->setItem(items[i]);
//        itemVector.push_back(item);
//    }
}
void OrderListWidget::clear()
{
    curIndex = 0;
    for (auto item: itemVector)
    {
        delete item;
    }
    itemVector.clear();
}
void OrderListWidget::insert(OrderListItem *item)
{
    if (item == nullptr)
    {
        qDebug()<<"空指针";
        return;
    }
    QListWidgetItem* pItem = new QListWidgetItem();
    ui->listWidget->addItem(pItem);
    pItem->setSizeHint(item->size());
    ui->listWidget->setItemWidget(pItem,item);
}
void OrderListWidget::play(QString orderSn)
{
    this->orderSn = orderSn;
    ui->listWidget->clear();
    setVector(orderSn);
    for(curIndex = 0; curIndex < itemVector.length(); ++curIndex)
    {
        insert(itemVector[curIndex]);
    }

}
