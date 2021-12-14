#include "Service/FreightEntity.h"
#include <QJsonDocument>
long FreightEntity::getId() const
{
    return id;
}

void FreightEntity::setId(long newId)
{
    id = newId;
}

double FreightEntity::getPrice() const
{
    return price;
}

void FreightEntity::setPrice(double newPrice)
{
    price = newPrice;
}

FreightEntity::FreightEntity(long id, double price) : id(id),
    price(price)
{}
QJsonObject FreightEntity::getJsonForm()
{
    return QJsonObject{
        {"id",  QString::number(id)},
        {"price", QString::number(price, 'f', 2)}
    };
}

FreightEntity FreightEntity::parseJson(QJsonObject obj)
{
    FreightEntity freightEntity;
    freightEntity.setId(obj["id"].toInteger());
    freightEntity.setPrice(obj["price"].toDouble());

    return freightEntity;
}
QByteArray FreightEntity::getQByteArrayForm()
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
