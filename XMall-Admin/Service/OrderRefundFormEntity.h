#ifndef ORDERREFUNDFORMENTITY_H
#define ORDERREFUNDFORMENTITY_H
#include <QString>
#include <QJsonObject>
#include <QByteArray>
class OrderRefundFormEntity{
public:
    long getId() const;
    void setId(long newId);
    const QString &getOrderSn() const;
    void setOrderSn(const QString &newOrderSn);
    const QDateTime &getCreatTime() const;
    void setCreatTime(const QDateTime &newCreatTime);
    double getRefundPrice() const;
    void setRefundPrice(double newRefundPrice);
    const QString &getUserPhone() const;
    void setUserPhone(const QString &newUserPhone);
    const QDateTime &getHandleTime() const;
    void setHandleTime(const QDateTime &newHandleTime);
    int getStatus() const;
    void setStatus(int newStatus);
    QJsonObject getJsonForm();
    QByteArray getQByteArrayForm();
    static OrderRefundFormEntity parseJson(QJsonObject obj);
    int getPreStatus() const;
    void setPreStatus(int newPreStatus);

private:

         long id;
         QString orderSn;
         QDateTime creatTime;
         double refundPrice;
         QString userPhone;
         QDateTime handleTime;
         int status;
         int preStatus;
};

#endif // ORDERREFUNDFORMENTITY_H
