#ifndef COMMENTENTITY_H
#define COMMENTENTITY_H
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
class CommentEntity{
public:
    long getId() const;
    void setId(long newId);
    long getProductId() const;
    void setProductId(long newProductId);
    const QString &getUserNickname() const;
    void setUserNickname(const QString &newUserNickname);
    const QString &getUserPhone() const;
    void setUserPhone(const QString &newUserPhone);
    int getStatus() const;
    void setStatus(int newStatus);
    const QDateTime &getCreatTime() const;
    void setCreatTime(const QDateTime &newCreatTime);
    const QString &getContent() const;
    void setContent(const QString &newContent);
    enum{DELETED = 1, VALID = 1};
    QJsonObject getJsonForm();
    QByteArray getQByteArrayForm();
    static CommentEntity parseJson(QJsonObject obj);
private:
         long id;
         long productId;
         QString userNickname;
         QString userPhone;
         int status;
         QDateTime creatTime;
         QString content;
};

#endif // COMMENTENTITY_H
