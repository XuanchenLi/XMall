#ifndef ORDERENTITY_H
#define ORDERENTITY_H
#include <QString>
#include <QJsonObject>
#include <QByteArray>
class OrderEntity{
public:
    OrderEntity() {}

    long getId() const;
    void setId(long newId);
    const QString &getUserPhone() const;
    void setUserPhone(const QString &newUserPhone);
    const QString &getOrderSn() const;
    void setOrderSn(const QString &newOrderSn);
    double getTotPrice() const;
    void setTotPrice(double newTotPrice);
    double getPayPrice() const;
    void setPayPrice(double newPayPrice);
    double getFreightPrice() const;
    void setFreightPrice(double newFreightPrice);
    double getPromotionPrice() const;
    void setPromotionPrice(double newPromotionPrice);
    double getCouponPrice() const;
    void setCouponPrice(double newCouponPrice);
    int getPayType() const;
    void setPayType(int newPayType);
    int getStatus() const;
    void setStatus(int newStatus);
    const QString &getUserAddressInfo() const;
    void setUserAddressInfo(const QString &newUseAddressInfo);
    const QDateTime &getCreatTime() const;
    void setCreatTime(const QDateTime &newCreatTime);
    const QDateTime &getPayTime() const;
    void setPayTime(const QDateTime &newPayTime);
    const QDateTime &getDeliveryTime() const;
    void setDeliveryTime(const QDateTime &newDeliveryTime);
    const QDateTime &getRecvTime() const;
    void setRecvTime(const QDateTime &newRecvTime);
    const QDateTime &getCommentTime() const;
    void setCommentTime(const QDateTime &newCommentTime);
    const QDateTime &getRefundTime() const;
    void setRefundTime(const QDateTime &newRefundTime);
    const QDateTime &getDieTime() const;
    void setDieTime(const QDateTime &newDieTime);
    enum{WAIT_PAY = 0, WAIT_DELIVERY = 1, WAIT_RECV = 2, WAIT_COMMENT = 3, COMPLETED = 4, WAIT_REFUND = 5, DIE = 6};
    QJsonObject getJsonForm();
    QByteArray getQByteArrayForm();
    static OrderEntity parseJson(QJsonObject obj);
private:
         long id;
         QString userPhone;
         QString orderSn;
         double totPrice;
         double payPrice;
         double freightPrice;
         double promotionPrice;
         double couponPrice;
         int payType;
         int status;
         QString userAddressInfo;
         QDateTime creatTime;
         QDateTime payTime;
         QDateTime deliveryTime;
         QDateTime recvTime;
         QDateTime commentTime;
         QDateTime refundTime;
         QDateTime dieTime;
};

#endif // ORDERENTITY_H
