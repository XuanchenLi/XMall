#ifndef HTTPPROXY_H
#define HTTPPROXY_H
#include <QSettings>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
class HttpProxy : public QObject{

    Q_OBJECT
public:
    HttpProxy();
    ~HttpProxy();
    void get(const QString url);
    void post(const QString url, const QByteArray &data);
    void uploadPicture(const QString url, const QString filePath);
    QJsonObject getJsonObject();
    inline int getReplyCode() const{return replyCode;}
    inline QByteArray getReplyData() const{return replyData;}
    /*
    void buildConnection(QObject* obj_p, void(*replyFunction)(QObject*, QNetworkReply *));
    void removeConnection(QObject* obj_p, void(*replyFunction)(QObject*, QNetworkReply *));
    */
protected:
    virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode);//子类定义获得回复后的具体操作

public slots:
    void serviceRequestFinished(QNetworkReply *reply);
private:
    //QTimer timer;
    QScopedPointer<QNetworkRequest> httpRequest;
    QScopedPointer<QNetworkAccessManager> networkAccessManager;
    int replyCode;
    QByteArray replyData;

};
#endif // HTTPPROXY_H
