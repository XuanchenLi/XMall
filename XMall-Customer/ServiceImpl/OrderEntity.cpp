#include "Service/OrderEntity.h"
#include <QJsonDocument>
long OrderEntity::getId() const
{
    return id;
}

void OrderEntity::setId(long newId)
{
    id = newId;
}

const QString &OrderEntity::getUserPhone() const
{
    return userPhone;
}

void OrderEntity::setUserPhone(const QString &newUserPhone)
{
    userPhone = newUserPhone;
}

const QString &OrderEntity::getOrderSn() const
{
    return orderSn;
}

void OrderEntity::setOrderSn(const QString &newOrderSn)
{
    orderSn = newOrderSn;
}

double OrderEntity::getTotPrice() const
{
    return totPrice;
}

void OrderEntity::setTotPrice(double newTotPrice)
{
    totPrice = newTotPrice;
}

double OrderEntity::getPayPrice() const
{
    return payPrice;
}

void OrderEntity::setPayPrice(double newPayPrice)
{
    payPrice = newPayPrice;
}

double OrderEntity::getFreightPrice() const
{
    return freightPrice;
}

void OrderEntity::setFreightPrice(double newFreightPrice)
{
    freightPrice = newFreightPrice;
}

double OrderEntity::getPromotionPrice() const
{
    return promotionPrice;
}

void OrderEntity::setPromotionPrice(double newPromotionPrice)
{
    promotionPrice = newPromotionPrice;
}

double OrderEntity::getCouponPrice() const
{
    return couponPrice;
}

void OrderEntity::setCouponPrice(double newCouponPrice)
{
    couponPrice = newCouponPrice;
}

int OrderEntity::getPayType() const
{
    return payType;
}

void OrderEntity::setPayType(int newPayType)
{
    payType = newPayType;
}

int OrderEntity::getStatus() const
{
    return status;
}

void OrderEntity::setStatus(int newStatus)
{
    status = newStatus;
}

const QString &OrderEntity::getUserAddressInfo() const
{
    return userAddressInfo;
}

void OrderEntity::setUserAddressInfo(const QString &newUserAddressInfo)
{
    userAddressInfo = newUserAddressInfo;
}

const QDateTime &OrderEntity::getCreatTime() const
{
    return creatTime;
}

void OrderEntity::setCreatTime(const QDateTime &newCreatTime)
{
    creatTime = newCreatTime;
}

const QDateTime &OrderEntity::getPayTime() const
{
    return payTime;
}

void OrderEntity::setPayTime(const QDateTime &newPayTime)
{
    payTime = newPayTime;
}

const QDateTime &OrderEntity::getDeliveryTime() const
{
    return deliveryTime;
}

void OrderEntity::setDeliveryTime(const QDateTime &newDeliveryTime)
{
    deliveryTime = newDeliveryTime;
}

const QDateTime &OrderEntity::getRecvTime() const
{
    return recvTime;
}

void OrderEntity::setRecvTime(const QDateTime &newRecvTime)
{
    recvTime = newRecvTime;
}

const QDateTime &OrderEntity::getCommentTime() const
{
    return commentTime;
}

void OrderEntity::setCommentTime(const QDateTime &newCommentTime)
{
    commentTime = newCommentTime;
}

const QDateTime &OrderEntity::getRefundTime() const
{
    return refundTime;
}

void OrderEntity::setRefundTime(const QDateTime &newRefundTime)
{
    refundTime = newRefundTime;
}

const QDateTime &OrderEntity::getDieTime() const
{
    return dieTime;
}

void OrderEntity::setDieTime(const QDateTime &newDieTime)
{
    dieTime = newDieTime;
}

QJsonObject OrderEntity::getJsonForm()
{
    return QJsonObject{
        {"id",  QString::number(id)},
        {"userPhone", userPhone},
        {"orderSn", orderSn},
        {"totPrice",  QString::number(totPrice,'f',2)},
        {"payPrice",  QString::number(payPrice,'f',2)},
        {"freightPrice",  QString::number(freightPrice,'f',2)},
        {"promotionPrice",  QString::number(promotionPrice,'f',2)},
        {"couponPrice",  QString::number(couponPrice,'f',2)},
        {"payType",  QString::number(payType)},
        {"status",  QString::number(status)},
        {"userAddressInfo", userAddressInfo},
        {"creatTime", creatTime.toString("yyyy-MM-dd hh:mm:ss")},
        {"payTime", payTime.toString("yyyy-MM-dd hh:mm:ss")},
        {"deliveryTime", deliveryTime.toString("yyyy-MM-dd hh:mm:ss")},
        {"recvTime", recvTime.toString("yyyy-MM-dd hh:mm:ss")},
        {"commentTime", commentTime.toString("yyyy-MM-dd hh:mm:ss")},
        {"refundTime", refundTime.toString("yyyy-MM-dd hh:mm:ss")},
        {"dieTime", dieTime.toString("yyyy-MM-dd hh:mm:ss")}
    };
}

OrderEntity OrderEntity::parseJson(QJsonObject obj)
{
    OrderEntity OrderEntity;
    OrderEntity.setId(obj["id"].toInteger());
    OrderEntity.setUserPhone(obj["userPhone"].toString());
    OrderEntity.setOrderSn(obj["orderSn"].toString());
    OrderEntity.setTotPrice(obj["totPrice"].toDouble());
    OrderEntity.setPayPrice(obj["payPrice"].toDouble());
    OrderEntity.setPromotionPrice(obj["promotionPrice"].toDouble());
    OrderEntity.setFreightPrice(obj["freightPrice"].toDouble());
    OrderEntity.setCouponPrice(obj["couponPrice"].toDouble());
    OrderEntity.setPayType(obj["payType"].toInt());
    OrderEntity.setStatus(obj["status"].toInt());
    OrderEntity.setUserAddressInfo(obj["userAddressInfo"].toString());
    OrderEntity.setCreatTime(QDateTime::fromString(obj["creatTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    OrderEntity.setPayTime(QDateTime::fromString(obj["payTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    OrderEntity.setDeliveryTime(QDateTime::fromString(obj["deliveryTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    OrderEntity.setRecvTime(QDateTime::fromString(obj["recvTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    OrderEntity.setCommentTime(QDateTime::fromString(obj["commentTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    OrderEntity.setRefundTime(QDateTime::fromString(obj["refundTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    OrderEntity.setDieTime(QDateTime::fromString(obj["dieTime"].toString(),"yyyy-MM-dd hh:mm:ss"));
    return OrderEntity;
}
QByteArray OrderEntity::getQByteArrayForm()
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
