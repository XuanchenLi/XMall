#ifndef ADDRESSENTITY_H
#define ADDRESSENTITY_H
#include <QString>
#include <QJsonObject>
#include <QByteArray>
class AddressEntity
{
public:
    const QString &getUserPhone() const;
    void setUserPhone(const QString &newUserPhone);
    const QString &getName() const;
    void setName(const QString &newName);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);
    const QString &getProvince() const;
    void setProvince(const QString &newProvince);
    const QString &getCity() const;
    void setCity(const QString &newCity);
    const QString &getRegion() const;
    void setRegion(const QString &newRegion);
    const QString &getDetail() const;
    void setDetail(const QString &newDetail);
    QJsonObject getJsonForm();
    QByteArray getQByteArrayForm();
private:
    QString userPhone;
    QString name;
    QString phone;
    QString province;
    QString city;
    QString region;
    QString detail;
};

#endif // ADDRESSENTITY_H
