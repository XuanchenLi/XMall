#include "Service/AdminEntity.h"
const QString &AdminEntity::getUuid() const
{
    return uuid;
}

void AdminEntity::setUuid(const QString &newUuid)
{
    uuid = newUuid;
}

const QString &AdminEntity::getPhone() const
{
    return phone;
}

void AdminEntity::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

const QString &AdminEntity::getPassword() const
{
    return password;
}

void AdminEntity::setPassword(const QString &newPassword)
{
    password = newPassword;
}

AdminEntity::AdminEntity(const QString &uuid, const QString &phone, const QString &password) : uuid(uuid),
    phone(phone),
    password(password)
{}

QJsonObject AdminEntity::getJsonForm()
{
    return QJsonObject{
        {"uuid", uuid},
        {"phone", phone},
        {"password", password}
    };
}
