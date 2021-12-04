#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include "Service/HttpProxy.h"

HttpProxy::HttpProxy()
{
    httpRequest.setRawHeader("Content-Type", "application/json");
    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
}

HttpProxy::~HttpProxy()
{
    networkAccessManager.disconnect();
}

void HttpProxy::get(const QString url)
{
    httpRequest.setUrl(url);
    QEventLoop loop;
    networkAccessManager.get(httpRequest);
    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
}

void HttpProxy::post(const QString url, const QByteArray &data)
{
    httpRequest.setUrl(url);
    networkAccessManager.post(httpRequest, data);
    QEventLoop loop;
    QObject::connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
}

void HttpProxy::serviceRequestFinished(QNetworkReply *reply)
{
    replyCode = 0;
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "HttpProxy...serviceRequestFinished...statusCode:" << statusCode;
    replyCode = statusCode;
    if(reply->error() == QNetworkReply::NoError) {
        replyData = reply->readAll();
        requestFinished(reply, replyData, statusCode);
    } else {
        replyData = "";
        requestFinished(reply, "", statusCode);
    }
    reply->deleteLater();
}

void HttpProxy::requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode)
{
    qDebug()<<"statusCode="<<statusCode;
    QByteArray resBytes = reply->readAll();

    qDebug()<<"resBytes="<<QString(resBytes);
    QJsonDocument doc = QJsonDocument::fromJson(resBytes);
    QJsonObject json = doc.object();


    QString resultcode = json["resultcode"].toString();
    qDebug()<<"resultcode="<<resultcode;

    int error_code = json["error_code"].toInt();
    qDebug()<<"error_code="<<error_code;
}

QJsonObject HttpProxy::getJsonObject()
{

    return  QJsonDocument::fromJson(replyData).object();
}

/*
void HttpProxy::buildConnection(QObject *obj_p, void (*replyFunction)(QObject *, QNetworkReply *))
{
    connect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), obj_p, SLOT(replyFunction));
}
void HttpProxy::removeConnection(QObject *obj_p, void (*replyFunction)(QObject *, QNetworkReply *))
{
    disconnect(&networkAccessManager, SIGNAL(finished(QNetworkReply*)), obj_p, SLOT(replyFunction));
}
*/
