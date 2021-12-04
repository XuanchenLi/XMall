#ifndef USERINFODTO_H
#define USERINFODTO_H

#include<QString>
#include<QJsonObject>
using namespace  std;

class UserInfoDto{
public:
    const QString &getNickname() const;
    void setNickname(const QString &newNickname);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);
    const QString &getEmail() const;
    void setEmail(const QString &newPassword);
    QJsonObject getJsonForm();
    UserInfoDto(){}
    UserInfoDto(QString nickname, QString phone, QString password, QString email);

private:
    QString nickname;
    QString phone;
    QString password;
    QString email;

};
#endif // USERINFODTO_H
