#include<QString>
#include<QJsonObject>
#include "Service/UserInfoDto.h"
using namespace  std;
const QString &UserInfoDto::getNickname() const
{
    return nickname;
}

void UserInfoDto::setNickname(const QString &newNickname)
{
    nickname = newNickname;
}
const QString &UserInfoDto::getEmail() const
{
    return email;
}

void UserInfoDto::setEmail(const QString &newEmail)
{
    email = newEmail;
}
const QString &UserInfoDto::getPhone() const
{
    return phone;
}

void UserInfoDto::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

const QString &UserInfoDto::getPassword() const
{
    return password;
}

void UserInfoDto::setPassword(const QString &newPassword)
{
    password = newPassword;
}

UserInfoDto::UserInfoDto(QString nickname, QString phone, QString password, QString email):
    nickname(nickname),
    phone(phone),
    password(password),
    email(email)
{

}

QJsonObject UserInfoDto::getJsonForm()
{
    return QJsonObject{
        {"nickname", nickname},
        {"phone", phone},
        {"password", password},
        {"emial", email}
    };
}
