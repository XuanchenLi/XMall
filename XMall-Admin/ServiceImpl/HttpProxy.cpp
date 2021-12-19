#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QTimer>
#include <QHttpPart>
#include <QFile>
#include "Service/HttpProxy.h"

HttpProxy::HttpProxy():httpRequest(new QNetworkRequest),networkAccessManager(new QNetworkAccessManager)
{
    //httpRequest.setRawHeader("Content-Type", "application/json");
    connect(networkAccessManager.get(), SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
}

HttpProxy::~HttpProxy()
{
    networkAccessManager->disconnect();
}

void HttpProxy::get(const QString url)
{
    httpRequest->setRawHeader("Content-Type", "application/json");
    QTimer timer;
    timer.setInterval(60000);//一分钟
    httpRequest->setUrl(url);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    QNetworkReply* reply = networkAccessManager->get(*httpRequest);
    connect(networkAccessManager.get(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    if(!timer.isActive())//处理超时
    {
        qDebug()<<"超时";
        disconnect(networkAccessManager.get(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
        reply->abort();
        reply->deleteLater();
    }
    else
    {
        timer.stop();
    }
}

void HttpProxy::post(const QString url, const QByteArray &data)
{
    QTimer timer;
    httpRequest->setRawHeader("Content-Type", "application/json");
    timer.setInterval(60000);//一分钟
    httpRequest->setUrl(url);
    QNetworkReply* reply = networkAccessManager->post(*httpRequest, data);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(networkAccessManager.get(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    timer.start();
    loop.exec();
    if(!timer.isActive())//处理超时
    {
        qDebug()<<"超时";
        disconnect(networkAccessManager.get(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
        reply->abort();
        reply->deleteLater();
    }
    else
    {
        timer.stop();
    }

}

void HttpProxy::uploadPicture(const QString url, const QString filePath)
{
    QTimer timer;
    //httpRequest.setRawHeader("Content-Type", "multipart/form-data");
    timer.setInterval(60000);//一分钟
    httpRequest->setUrl(url);
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    int first = filePath.lastIndexOf ("\\");
    QString picname = filePath.right (filePath.length ()-first-1);
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\";filename=\""+ picname + "\""));
    QFile *file = new QFile(filePath);//pathbuf1 为文件路径
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);
    multiPart->append(imagePart);
    QNetworkReply* reply = networkAccessManager->post(*httpRequest, multiPart);
    QEventLoop loop;
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    connect(networkAccessManager.get(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    timer.start();
    loop.exec();
    if(!timer.isActive())//处理超时
    {
        qDebug()<<"超时";
        disconnect(networkAccessManager.get(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
        reply->abort();
        reply->deleteLater();
    }
    else
    {
        timer.stop();
    }

}

void HttpProxy::serviceRequestFinished(QNetworkReply *reply)
{
    //timer.stop();
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
    //qDebug()<<"statusCode="<<statusCode;
    QByteArray resBytes = reply->readAll();

    //qDebug()<<"resBytes="<<QString(resBytes);
    QJsonDocument doc = QJsonDocument::fromJson(resBytes);
    QJsonObject json = doc.object();


    QString resultcode = json["resultcode"].toString();
    //qDebug()<<"resultcode="<<resultcode;

    int error_code = json["error_code"].toInt();
    //qDebug()<<"error_code="<<error_code;
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
