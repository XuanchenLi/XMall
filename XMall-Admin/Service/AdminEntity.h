#ifndef ADMINENTITY_H
#define ADMINENTITY_H
#include <QString>
#include <QJsonObject>
class AdminEntity
{
public:
    AdminEntity() {}
    AdminEntity(const QString &uuid, const QString &phone, const QString &password);

    const QString &getUuid() const;
    void setUuid(const QString &newUuid);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);
    QJsonObject getJsonForm();

private:
    QString uuid;
    QString phone;
    QString password;
};

#endif // ADMINENTITY_H
