#include "Service/AddressEntity.h"
#include <QJsonDocument>

const QString &AddressEntity::getUserPhone() const
{
    return userPhone;
}

void AddressEntity::setUserPhone(const QString &newUserPhone)
{
    userPhone = newUserPhone;
}

const QString &AddressEntity::getName() const
{
    return name;
}

void AddressEntity::setName(const QString &newName)
{
    name = newName;
}

const QString &AddressEntity::getPhone() const
{
    return phone;
}

void AddressEntity::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

const QString &AddressEntity::getProvince() const
{
    return province;
}

void AddressEntity::setProvince(const QString &newProvince)
{
    province = newProvince;
}

const QString &AddressEntity::getCity() const
{
    return city;
}

void AddressEntity::setCity(const QString &newCity)
{
    city = newCity;
}

const QString &AddressEntity::getRegion() const
{
    return region;
}

void AddressEntity::setRegion(const QString &newRegion)
{
    region = newRegion;
}

const QString &AddressEntity::getDetail() const
{
    return detail;
}

void AddressEntity::setDetail(const QString &newDetail)
{
    detail = newDetail;
}
QJsonObject AddressEntity::getJsonForm()
{
    return QJsonObject{
        {"userPhone", userPhone},
        {"name", name},
        {"phone", phone},
        {"province", province},
        {"city", city},
        {"region", region},
        {"detail", detail}
    };
}
QByteArray AddressEntity::getQByteArrayForm()
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
