#include "Service/OrderItemEntity.h"
#include <QJsonDocument>
long OrderItemEntity::getId() const
{
    return id;
}

void OrderItemEntity::setId(long newId)
{
    id = newId;
}

const QString &OrderItemEntity::getOrderSn() const
{
    return orderSn;
}

void OrderItemEntity::setOrderSn(const QString &newOrderSn)
{
    orderSn = newOrderSn;
}

long OrderItemEntity::getProductId() const
{
    return productId;
}

void OrderItemEntity::setProductId(long newProductId)
{
    productId = newProductId;
}

const QString &OrderItemEntity::getName() const
{
    return name;
}

void OrderItemEntity::setName(const QString &newName)
{
    name = newName;
}

double OrderItemEntity::getCurrentPrice() const
{
    return currentPrice;
}

void OrderItemEntity::setCurrentPrice(double newCurrentPrice)
{
    currentPrice = newCurrentPrice;
}

double OrderItemEntity::getPrice() const
{
    return price;
}

void OrderItemEntity::setPrice(double newPrice)
{
    price = newPrice;
}

int OrderItemEntity::getCount() const
{
    return count;
}

void OrderItemEntity::setCount(int newCount)
{
    count = newCount;
}
QJsonObject OrderItemEntity::getJsonForm()
{
    return QJsonObject{
        {"id",  QString::number(id)},
        {"orderSn", orderSn},
        {"productId",  QString::number(productId)},
        {"name", name},
        {"price", QString::number(price, 'f', 2)},
        {"currentPrice",  QString::number(currentPrice, 'f', 2)},
        {"count",QString::number(count) }
    };
}

OrderItemEntity OrderItemEntity::parseJson(QJsonObject obj)
{
    OrderItemEntity OrderItemEntity;
    OrderItemEntity.setId(obj["id"].toInteger());
    OrderItemEntity.setName(obj["name"].toString());
    OrderItemEntity.setPrice(obj["price"].toDouble());
    OrderItemEntity.setCurrentPrice(obj["currentPrice"].toDouble());
    OrderItemEntity.setOrderSn(obj["orderSn"].toString());
    OrderItemEntity.setProductId(obj["productId"].toInteger());
    OrderItemEntity.setCount(obj["count"].toInt());

    return OrderItemEntity;
}
QByteArray OrderItemEntity::getQByteArrayForm()
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
