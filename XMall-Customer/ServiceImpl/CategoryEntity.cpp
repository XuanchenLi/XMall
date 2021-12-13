#include "Service/CategoryEntity.h"
#include <QJsonDocument>
long CategoryEntity::getId() const
{
    return id;
}

void CategoryEntity::setId(long newId)
{
    id = newId;
}

long CategoryEntity::getParentId() const
{
    return parentId;
}

void CategoryEntity::setParentId(long newParentId)
{
    parentId = newParentId;
}

const QString &CategoryEntity::getName() const
{
    return name;
}

void CategoryEntity::setName(const QString &newName)
{
    name = newName;
}

int CategoryEntity::getLevel() const
{
    return level;
}

void CategoryEntity::setLevel(int newLevel)
{
    level = newLevel;
}

bool CategoryEntity::getIsLeaf() const
{
    return isLeaf;
}

void CategoryEntity::setIsLeaf(bool newIsLeaf)
{
    isLeaf = newIsLeaf;
}



CategoryEntity::CategoryEntity(long id, long parentId, const QString &name, int level, bool isLeaf) : id(id),
    parentId(parentId),
    name(name),
    level(level),
    isLeaf(isLeaf)
{}

QJsonObject CategoryEntity::getJsonForm()
{
    return QJsonObject{
        {"id",  QString::number(id)},
        {"parentId", QString::number(parentId)},
        {"name", name},
        {"level", level},
        {"isLeaf", isLeaf}
    };
}

CategoryEntity CategoryEntity::parseJson(QJsonObject obj)
{
    CategoryEntity categoryEntity;
    categoryEntity.setId(obj["id"].toInteger());
    categoryEntity.setParentId(obj["parentId"].toInteger());
    categoryEntity.setName(obj["name"].toString());
    categoryEntity.setLevel(obj["level"].toInt());
    categoryEntity.setIsLeaf(obj["isLeaf"].toBool());

    return categoryEntity;
}
QByteArray CategoryEntity::getQByteArrayForm()
{
    return QJsonDocument(this->getJsonForm()).toJson();
}
