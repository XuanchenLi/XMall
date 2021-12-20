#include "Service/OrderRefundFormEntity.h"
#include <QJsonDocument>
long OrderRefundFormEntity::getId() const
{
    return id;
}

void OrderRefundFormEntity::setId(long newId)
{
    id = newId;
}

const QString &OrderRefundFormEntity::getOrderSn() const
{
    return orderSn;
}

void OrderRefundFormEntity::setOrderSn(const QString &newOrderSn)
{
    orderSn = newOrderSn;
}

const QDateTime &OrderRefundFormEntity::getCreatTime() const
{
    return creatTime;
}

void OrderRefundFormEntity::setCreatTime(const QDateTime &newCreatTime)
{
    creatTime = newCreatTime;
}

double OrderRefundFormEntity::getRefundPrice() const
{
    return refundPrice;
}

void OrderRefundFormEntity::setRefundPrice(double newRefundPrice)
{
    refundPrice = newRefundPrice;
}

const QString &OrderRefundFormEntity::getUserPhone() const
{
    return userPhone;
}

void OrderRefundFormEntity::setUserPhone(const QString &newUserPhone)
{
    userPhone = newUserPhone;
}

const QDateTime &OrderRefundFormEntity::getHandleTime() const
{
    return handleTime;
}

void OrderRefundFormEntity::setHandleTime(const QDateTime &newHandleTime)
{
    handleTime = newHandleTime;
}

int OrderRefundFormEntity::getStatus() const
{
    return status;
}

void OrderRefundFormEntity::setStatus(int newStatus)
{
    status = newStatus;
}
QJsonObject OrderRefundFormEntity::getJsonForm()
{
    return QJsonObject{
        {"id",  QString::number(id)},
        {"orderSn", orderSn},
        {"refundPrice",  QString::number(refundPrice, 'f', 2)},
        {"status",QString::number(status) },
        {"preStatus",QString::number(preStatus) },
        {"userPhone", userPhone},
        {"handleTime", handleTime.toString("yyyy-MM-dd hh:mm:ss")},
        {"creatTime", creatTime.toString("yyyy-MM-dd hh:mm:ss")}
    };
}

OrderRefundFormEntity OrderRefundFormEntity::parseJson(QJsonObject obj)
{
    OrderRefundFormEntity OrderRefundFormEntity;
    OrderRefundFormEntity.setId(obj["id"].toInteger());
    OrderRefundFormEntity.setRefundPrice(obj["refundPrice"].toDouble());
    OrderRefundFormEntity.setOrderSn(obj["orderSn"].toString());
    OrderRefundFormEntity.setCreatTime(QDateTime::fromString(obj["creatTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    OrderRefundFormEntity.setHandleTime(QDateTime::fromString(obj["hadnleTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    OrderRefundFormEntity.setUserPhone(obj["userPhone"].toString());
    OrderRefundFormEntity.setStatus(obj["status"].toInt());
    OrderRefundFormEntity.setPreStatus(obj["preStatus"].toInt());
    return OrderRefundFormEntity;
}

int OrderRefundFormEntity::getPreStatus() const
{
    return preStatus;
}

void OrderRefundFormEntity::setPreStatus(int newPreStatus)
{
    preStatus = newPreStatus;
}
QByteArray OrderRefundFormEntity::getQByteArrayForm()
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
