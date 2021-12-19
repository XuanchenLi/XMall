#include "Service/CommentEntity.h"
long CommentEntity::getId() const
{
    return id;
}

void CommentEntity::setId(long newId)
{
    id = newId;
}

long CommentEntity::getProductId() const
{
    return productId;
}

void CommentEntity::setProductId(long newProductId)
{
    productId = newProductId;
}

const QString &CommentEntity::getUserNickname() const
{
    return userNickname;
}

void CommentEntity::setUserNickname(const QString &newUserNickname)
{
    userNickname = newUserNickname;
}

const QString &CommentEntity::getUserPhone() const
{
    return userPhone;
}

void CommentEntity::setUserPhone(const QString &newUserPhone)
{
    userPhone = newUserPhone;
}

int CommentEntity::getStatus() const
{
    return status;
}

void CommentEntity::setStatus(int newStatus)
{
    status = newStatus;
}

const QDateTime &CommentEntity::getCreatTime() const
{
    return creatTime;
}

void CommentEntity::setCreatTime(const QDateTime &newCreatTime)
{
    creatTime = newCreatTime;
}

const QString &CommentEntity::getContent() const
{
    return content;
}

void CommentEntity::setContent(const QString &newContent)
{
    content = newContent;
}
QJsonObject CommentEntity::getJsonForm()
{
    return QJsonObject{
        {"id",  QString::number(id)},
        {"productId", QString::number(productId)},
        {"userNickname", userNickname},
        {"userPhone", userPhone},
        {"status", status},
        {"creatTime", creatTime.toString("yyyy-MM-dd hh:mm:ss")},
        {"content", content}
    };
}

CommentEntity CommentEntity::parseJson(QJsonObject obj)
{
    CommentEntity CommentEntity;
    CommentEntity.setId(obj["id"].toInteger());
    CommentEntity.setProductId(obj["productId"].toInteger());
    CommentEntity.setUserNickname(obj["UserNickname"].toString());
    CommentEntity.setUserPhone(obj["userPhone"].toString());
    CommentEntity.setStatus(obj["status"].toInt());
    CommentEntity.setCreatTime(QDateTime::fromString(obj["creatTime"].toString().mid(0,19),"yyyy-MM-dd'T'hh:mm:ss"));
    CommentEntity.setContent(obj["content"].toString());

    return CommentEntity;
}
QByteArray CommentEntity::getQByteArrayForm()
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
