#ifndef CATEGORYENTITY_H
#define CATEGORYENTITY_H
#include <QString>
#include <QJsonObject>
class CategoryEntity{


public:
    CategoryEntity() {}
    CategoryEntity(long id, long parentId, const QString &name, int level, bool isLeaf);
    static CategoryEntity parseJson(QJsonObject obj);
    long getId() const;
    void setId(long newId);
    long getParentId() const;
    void setParentId(long newParentId);
    const QString &getName() const;
    void setName(const QString &newName);
    int getLevel() const;
    void setLevel(int newLevel);
    bool getIsLeaf() const;
    void setIsLeaf(bool newIsLeaf);
    QJsonObject getJsonForm();
    QByteArray getQByteArrayForm();
private:
    long id;
    long parentId;
    QString name;
    int level;
    bool isLeaf;
};

#endif // CATEGORYENTITY_H
