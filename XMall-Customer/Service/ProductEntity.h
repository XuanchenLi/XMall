#ifndef PRODUCTENTITY_H
#define PRODUCTENTITY_H
#include <QString>
#include <QDateTime>
class ProductEntity{
public:
    ProductEntity()
    {
        status = COMING_SOON;
        sale = 0;
    }

    enum {COMING_SOON = 0, ON_SALE = 1, NOT_ON_SALE = 2, SHORTAGE = 3, STATUS_NUMBER = 4};
    long getId() const;
    void setId(long newId);
    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getIntroduction() const;
    void setIntroduction(const QString &newIntroduction);
    double getPrice() const;
    void setPrice(double newPrice);
    double getCurrentPrice() const;
    void setCurrentPrice(double newCurrentPrice);
    const QString &getSmallPicAddress() const;
    void setSmallPicAddress(const QString &newSmallPicAddress);
    const QString &getBigPicAddress() const;
    void setBigPicAddress(const QString &newBigPicAddress);
    int getLimitation() const;
    void setLimitation(int newLimitation);
    long getCategoryId() const;
    void setCategoryId(long newCategoryId);
    bool getIsHaveAttribute() const;
    void setIsHaveAttribute(bool newIsHaveAttribute);
    long getFreightTemplateId() const;
    void setFreightTemplateId(long newFreightTemplateId);
    int getStatus() const;
    void setStatus(int newStatus);
    long getSale() const;
    void setSale(long newSale);
    const QString &getUnit() const;
    void setUnit(const QString &newUnit);
    long getStorage() const;
    void setStorage(long newStorage);
    const QDateTime &getCreatTime() const;
    void setCreatTime(const QDateTime &newCreatTime);
    QJsonObject getJsonForm();
    QByteArray getQByteArrayForm();
    static ProductEntity parseJson(QJsonObject obj);
private:
     long id;
     QString name;
     QString introduction;
     double price;
     double currentPrice;
     QString smallPicAddress;
     QString bigPicAddress;
     int limitation;
     long categoryId;
     bool isHaveAttribute;
     long freightTemplateId;
     int status;
     long sale;
     QString unit;
     long storage;
     QDateTime creatTime;
};

#endif // PRODUCTENTITY_H
