#include "Service/UserInfoEntity.h"
#include <QJsonObject>
const QString &UserInfoEntity::getUuid() const
{
    return uuid;
}

void UserInfoEntity::setUuid(const QString &newUuid)
{
    uuid = newUuid;
}

const QString &UserInfoEntity::getNickname() const
{
    return nickname;
}

void UserInfoEntity::setNickname(const QString &newNickname)
{
    nickname = newNickname;
}

const QString &UserInfoEntity::getPhone() const
{
    return phone;
}

void UserInfoEntity::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

const QString &UserInfoEntity::getPassword() const
{
    return password;
}

void UserInfoEntity::setPassword(const QString &newPassword)
{
    password = newPassword;
}

const QString &UserInfoEntity::getEmail() const
{
    return email;
}

void UserInfoEntity::setEmail(const QString &newEmail)
{
    email = newEmail;
}

bool UserInfoEntity::getGender() const
{
    return gender;
}

void UserInfoEntity::setGender(bool newGender)
{
    gender = newGender;
}

const QString &UserInfoEntity::getIcon() const
{
    return icon;
}

void UserInfoEntity::setIcon(const QString &newIcon)
{
    icon = newIcon;
}

const QDate &UserInfoEntity::getBirthday() const
{
    return birthday;
}

void UserInfoEntity::setBirthday(const QDate &newBirthday)
{
    birthday = newBirthday;
}

const QString &UserInfoEntity::getPersonalRemark() const
{
    return personalRemark;
}

void UserInfoEntity::setPersonalRemark(const QString &newPersonalRemark)
{
    personalRemark = newPersonalRemark;
}
QJsonObject UserInfoEntity::getJsonForm()
{
    return QJsonObject{
        {"uuid", uuid},
        {"nickname", nickname},
        {"phone", phone},
        {"password", password},
        {"emial", email},
        {"gender", gender},
        {"icon", icon},
        {"birthday", birthday.toString("yyyy-MM-dd")},
        {"personalRemark", personalRemark}
    };
}
QJsonObject UserInfoEntity::getEditRequestJsonForm()
{
    return QJsonObject{
        {"phone", phone},
        {"nickname", nickname},
        {"gender", gender},
        {"email", email},
        {"birthday", birthday.toString("yyyy-MM-dd")},
        {"personalRemark", personalRemark}
    };
}
