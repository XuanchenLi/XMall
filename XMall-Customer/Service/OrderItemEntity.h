#ifndef ORDERITEMENTITY_H
#define ORDERITEMENTITY_H
#include <QString>
#include <QJsonObject>
#include <QByteArray>
class OrderItemEntity
{

public:
    OrderItemEntity() {}

    long getId() const;
    void setId(long newId);
    const QString &getOrderSn() const;
    void setOrderSn(const QString &newOrderSn);
    long getProductId() const;
    void setProductId(long newProductId);
    const QString &getName() const;
    void setName(const QString &newName);
    double getCurrentPrice() const;
    void setCurrentPrice(double newCurrentPrice);
    double getPrice() const;
    void setPrice(double newPrice);
    int getCount() const;
    void setCount(int newCount);

    QJsonObject getJsonForm();
    QByteArray getQByteArrayForm();
    static OrderItemEntity parseJson(QJsonObject obj);
private:
         long id;
         QString orderSn;
         long productId;
         QString name;
         double currentPrice;
         double price;
         int count;
};

#endif // ORDERITEMENTITY_H
