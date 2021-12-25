#include "orderviewwidget.h"
#include "ui_orderviewwidget.h"
#include "Service/HttpProxy.h"
#include <QJsonArray>
#include <QJsonDocument>
extern QString GET_HOST();
OrderViewWidget::OrderViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderViewWidget)
{
    ui->setupUi(this);
    for (int i = 0 ; i <= STATUS_NUMBER; ++i)
    {
        orderVectors.append(QVector<OrderViewItem*>());
    }
}

OrderViewWidget::~OrderViewWidget()
{
    clear();
    delete ui;
}

const QString &OrderViewWidget::getPhone() const
{
    return phone;
}

void OrderViewWidget::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

int OrderViewWidget::getCurStatus() const
{
    return curStatus;
}

void OrderViewWidget::setCurStatus(int newCurStatus)
{
    curStatus = newCurStatus;
}
void OrderViewWidget::setVector(int status)
{
    clear(status);
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/phone/" + phone +"/status/" + QString::number(status));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray products = jsonObject["orderEntityList"].toArray();
        for (int i =0; i<products.count(); ++i)
        {
            OrderViewItem* item = new OrderViewItem;
            item->setOrder(OrderEntity::parseJson(products[i].toObject()));
            orderVectors[status].append(item);
        }
    }

}

void OrderViewWidget::setVector()
{
    clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    for (int j = 0; j < STATUS_NUMBER; ++j){
        httpProxy->get(GET_HOST() + "/order/phone/" + phone +"/status/" + QString::number(j));
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() == "SUCCESS")
        {
         QJsonArray orders = jsonObject["orderEntityList"].toArray();
            for (int i =0; i<orders.count(); ++i)
            {
                OrderViewItem* item = new OrderViewItem;
                item->setOrder(OrderEntity::parseJson(orders[i].toObject()));
                orderVectors[STATUS_NUMBER].append(item);
            }
        }
    }

}



void OrderViewWidget::insert(OrderViewItem* item)
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

void OrderViewWidget::clear(int status)
{
    curIndex = 0;
    ui->listWidget->clear();
    orderVectors[status].clear();
    orderVectors[status].squeeze();
}
void OrderViewWidget::clear()
{
    curIndex = 0;
    ui->listWidget->clear();
//    for (int i = 0 ; i < orderVectors.length(); ++i)
//    {
//        auto vector = orderVectors[i];
//        for(auto it = vector.begin(); it != vector.end(); ++it)
//            {
//                if(*it != nullptr)
//                {
//                    delete (*it);
//                    (*it) = nullptr;
//                }

//            }
//            vector.clear();
//            vector.squeeze();
//    }

    orderVectors[STATUS_NUMBER].clear();
    orderVectors[STATUS_NUMBER].squeeze();
}
void OrderViewWidget::play(int status)
{

    //if(status == STATUS_NUMBER) return;
    curStatus = status;
    setVector(status);
    for(curIndex = 0; curIndex < orderVectors[status].size(); ++curIndex)
    {
        insert(orderVectors[status][curIndex]);
    }

}
void OrderViewWidget::play()
{

    curStatus = STATUS_NUMBER;
    //ui->listWidget->clear();
    setVector();
    for(curIndex = 0; curIndex < orderVectors[STATUS_NUMBER].size(); ++curIndex)
    {

        insert(orderVectors[STATUS_NUMBER][curIndex]);
    }
//        while(!ui->listWidget->isScrollVisible() && curIndex < orderVectors[STATUS_NUMBER].length())
//    {
//        insert(orderVectors[STATUS_NUMBER][curIndex++]);
//    }

}





void  OrderViewWidget::onScrollBarMoved( int  v)
{

}

void  OrderViewWidget::onReachedBottom()
{
    for  ( int i = 0; i < 5 && curIndex < orderVectors[curStatus].size(); i++, curIndex++)
    {
        insert(orderVectors[curStatus][curIndex]);
    }


}
