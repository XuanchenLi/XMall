#ifndef FREIGHTENTITY_H
#define FREIGHTENTITY_H
#include <QString>
#include <QJsonObject>
#include <QByteArray>
class FreightEntity
{
public:
    FreightEntity() {}
    FreightEntity(long id, double price);

    long getId() const;
    void setId(long newId);
    double getPrice() const;
    void setPrice(double newPrice);
    QJsonObject getJsonForm();
    QByteArray getQByteArrayForm();
    static FreightEntity parseJson(QJsonObject obj);

private:
    long id;
    double price;
};

#endif // FREIGHTENTITY_H
