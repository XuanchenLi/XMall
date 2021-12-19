#include "Service/ProductEntity.h"
#include <QJsonObject>
#include <QJsonDocument>
long ProductEntity::getId() const
{
    return id;
}

void ProductEntity::setId(long newId)
{
    id = newId;
}

const QString &ProductEntity::getName() const
{
    return name;
}

void ProductEntity::setName(const QString &newName)
{
    name = newName;
}

const QString &ProductEntity::getIntroduction() const
{
    return introduction;
}

void ProductEntity::setIntroduction(const QString &newIntroduction)
{
    introduction = newIntroduction;
}

double ProductEntity::getPrice() const
{
    return price;
}

void ProductEntity::setPrice(double newPrice)
{
    price = newPrice;
}

double ProductEntity::getCurrentPrice() const
{
    return currentPrice;
}

void ProductEntity::setCurrentPrice(double newCurrentPrice)
{
    currentPrice = newCurrentPrice;
}

const QString &ProductEntity::getSmallPicAddress() const
{
    return smallPicAddress;
}

void ProductEntity::setSmallPicAddress(const QString &newSmallPicAddress)
{
    smallPicAddress = newSmallPicAddress;
}

const QString &ProductEntity::getBigPicAddress() const
{
    return bigPicAddress;
}

void ProductEntity::setBigPicAddress(const QString &newBigPicAddress)
{
    bigPicAddress = newBigPicAddress;
}

int ProductEntity::getLimitation() const
{
    return limitation;
}

void ProductEntity::setLimitation(int newLimitation)
{
    limitation = newLimitation;
}

long ProductEntity::getCategoryId() const
{
    return categoryId;
}

void ProductEntity::setCategoryId(long newCategoryId)
{
    categoryId = newCategoryId;
}

bool ProductEntity::getIsHaveAttribute() const
{
    return isHaveAttribute;
}

void ProductEntity::setIsHaveAttribute(bool newIsHaveAttribute)
{
    isHaveAttribute = newIsHaveAttribute;
}

double ProductEntity::getFreightPrice() const
{
    return freightPrice;
}

void ProductEntity::setFreightPrice(double newFreightPrice)
{
    freightPrice = newFreightPrice;
}

int ProductEntity::getStatus() const
{
    return status;
}

void ProductEntity::setStatus(int newStatus)
{
    status = newStatus;
}

long ProductEntity::getSale() const
{
    return sale;
}

void ProductEntity::setSale(long newSale)
{
    sale = newSale;
}

const QString &ProductEntity::getUnit() const
{
    return unit;
}

void ProductEntity::setUnit(const QString &newUnit)
{
    unit = newUnit;
}

long ProductEntity::getStorage() const
{
    return storage;
}

void ProductEntity::setStorage(long newStorage)
{
    storage = newStorage;
}

const QDateTime &ProductEntity::getCreatTime() const
{
    return creatTime;
}

void ProductEntity::setCreatTime(const QDateTime &newCreatTime)
{
    creatTime = newCreatTime;
}

QJsonObject ProductEntity::getJsonForm() const
{
    return QJsonObject{
        {"id",  QString::number(id)},
        {"name", name},
        {"introduction",  introduction},
        {"price", QString::number(price, 'f', 2)},
        {"currentPrice",  QString::number(currentPrice, 'f', 2)},
        {"smallPicAddress", smallPicAddress},
        {"bigPicAddress",  bigPicAddress},
        {"limitation", QString::number(limitation)},
        {"categoryId",  QString::number(categoryId)},
        {"isHaveAttribute", isHaveAttribute},
        {"freightPrice",  QString::number(freightPrice,'f',2)},
        {"status", QString::number(status)},
        {"sale",  QString::number(sale)},
        {"unit",  unit},
        {"storage", QString::number(storage)},
        {"creatTime", creatTime.toString("yyyy-MM-dd hh:mm:ss")}
    };
}

ProductEntity ProductEntity::parseJson(QJsonObject obj)
{
    ProductEntity productEntity;
    productEntity.setId(obj["id"].toInteger());
    productEntity.setName(obj["name"].toString());
    productEntity.setIntroduction(obj["introduction"].toString());
    productEntity.setPrice(obj["price"].toDouble());
    productEntity.setCurrentPrice(obj["currentPrice"].toDouble());
    productEntity.setSmallPicAddress(obj["smallPicAddress"].toString());
    productEntity.setBigPicAddress(obj["bigPicAddress"].toString());
    productEntity.setLimitation(obj["limitation"].toInt());
    productEntity.setCategoryId(obj["categoryId"].toInteger());
    productEntity.setIsHaveAttribute(obj["isHaveAttribute"].toBool());
    productEntity.setFreightPrice(obj["freightPrice"].toDouble());
    productEntity.setStatus(obj["status"].toInt());
    productEntity.setSale(obj["sale"].toInteger());
    productEntity.setUnit(obj["unit"].toString());
    productEntity.setStorage(obj["storage"].toInteger());
    productEntity.setCreatTime(QDateTime::fromString(obj["creatTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    return productEntity;
}
QByteArray ProductEntity::getQByteArrayForm() const
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
