#ifndef USERINFOENTITY_H
#define USERINFOENTITY_H
#include <QString>
#include <QDate>
class UserInfoEntity
{
public:
    const QString &getUuid() const;
    void setUuid(const QString &newUuid);
    const QString &getNickname() const;
    void setNickname(const QString &newNickname);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);
    const QString &getEmail() const;
    void setEmail(const QString &newEmail);
    bool getGender() const;
    void setGender(bool newGender);
    const QString &getIcon() const;
    void setIcon(const QString &newIcon);
    const QDate &getBirthday() const;
    void setBirthday(const QDate &newBirthday);
    const QString &getPersonalRemark() const;
    void setPersonalRemark(const QString &newPersonalRemark);
    QJsonObject getJsonForm();
    QJsonObject getEditRequestJsonForm();
private:
        QString uuid;
        QString nickname;
        QString phone;
        QString password;
        QString email;
        bool gender;
        QString icon;
        QDate birthday;
        QString personalRemark;
};

#endif // USERINFOENTITY_H
