#include "Service/CartEntity.h"
long CartEntity::getId() const
{
    return id;
}

void CartEntity::setId(long newId)
{
    id = newId;
}

const QString &CartEntity::getUserPhone() const
{
    return userPhone;
}

void CartEntity::setUserPhone(const QString &newUserPhone)
{
    userPhone = newUserPhone;
}

long CartEntity::getProduct_id() const
{
    return product_id;
}

void CartEntity::setProduct_id(long newProduct_id)
{
    product_id = newProduct_id;
}

int CartEntity::getCount() const
{
    return count;
}

void CartEntity::setCount(int newCount)
{
    count = newCount;
}

bool CartEntity::getDel() const
{
    return del;
}

void CartEntity::setDel(bool newIsDel)
{
    del = newIsDel;
}

bool CartEntity::getChecked() const
{
    return checked;
}

void CartEntity::setChecked(bool newIsChecked)
{
    checked = newIsChecked;
}

QJsonObject CartEntity::getJsonForm() const
{
    return QJsonObject{
        {"id",  QString::number(id)},
        {"userPhone", userPhone},
        {"productId", QString::number(product_id)},
        {"count", QString::number(count)},
        {"del", del},
        {"checked", checked}
    };
}

CartEntity CartEntity::parseJson(QJsonObject obj)
{
    CartEntity cartEntity;
    cartEntity.setId(obj["id"].toInteger());
    cartEntity.setUserPhone(obj["userPhone"].toString());
    cartEntity.setProduct_id(obj["productId"].toInteger());
    cartEntity.setCount(obj["count"].toInt());
    cartEntity.setDel(obj["del"].toBool());
    cartEntity.setChecked(obj["checked"].toBool());

    return cartEntity;
}
QByteArray CartEntity::getQByteArrayForm() const
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
