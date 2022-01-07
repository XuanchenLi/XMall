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

UserInfoDto::UserInfoDto(QString _nickname, QString _phone, QString _password, QString _email):
    nickname(_nickname),
    phone(_phone),
    password(_password),
    email(_email)
{
qDebug()<<"初始化"<<phone;
}

QJsonObject UserInfoDto::getJsonForm()
{
    return QJsonObject{
        {"nickname", nickname},
        {"phone", phone},
        {"password", password},
        {"email", email}
    };
}
