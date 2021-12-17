#ifndef CARTENTITY_H
#define CARTENTITY_H
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
class CartEntity{
public:
    CartEntity() {}
    QJsonObject getJsonForm() const;
    QByteArray getQByteArrayForm() const;
    static CartEntity parseJson(QJsonObject obj);

    long getId() const;
    void setId(long newId);
    const QString &getUserPhone() const;
    void setUserPhone(const QString &newUserPhone);
    long getProduct_id() const;
    void setProduct_id(long newProduct_id);
    int getCount() const;
    void setCount(int newCount);
    bool getDel() const;
    void setDel(bool newIsDel);

    bool getChecked() const;
    void setChecked(bool newIsChecked);

private:
    long id;
    QString userPhone;
    long product_id;
    int count;
    bool del;
    bool checked;
};

#endif // CARTENTITY_H
