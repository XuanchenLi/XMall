#include "login.h"
#include <QApplication>
#include <QString>

//Test
#include<mainwindow.h>
#include <QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkReply>
#include<QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QDebug>
#include "slidewidget.h"
#include "orderwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Login w;
    w.show();
    //QString date = QString("2021-12-19T13:28:25.000+00:00");
    //qDebug()<<QDateTime::fromString(date.mid(0,19),"yyyy-MM-dd'T'hh:mm:ss").toString("yyyy-MM-dd hh:mm:ss");
    //TEST
//    MainWindow mw;
//    mw.show();
//    mw.initCategoryMenu();
//    OrderWindow *orderWin = new OrderWindow;
//    orderWin->setPhone("15962456486");
//    orderWin->show();
//    //
    return a.exec();
}


QString GET_HOST()
{
    static QString MY_HOST = "http://127.0.0.1:8080";
    return MY_HOST;
}
QString GET_AVATAR_PATH()
{
    static QString AVATAR_PATH = "/static/uploads/avatars/";
    return AVATAR_PATH;
}
QString GET_PRODUCT_SMALL_PATH()
{
    static QString PRODUCT_SMALL_PATH = "/static/uploads/products/small/";
    return PRODUCT_SMALL_PATH;
}
QString GET_PRODUCT_BIG_PATH()
{
    static QString PRODUCT_BIG_PATH = "/static/uploads/products/big/";
    return PRODUCT_BIG_PATH;
}

long GET_ID(QString context)
{
    if (context == "") return 0;
    long res = 0;
    for(int i =0; context[i].isNumber() && i < context.length(); ++i)
    {
        res *= 10;
        res += context[i].toLatin1() - '0';
    }
    return res;
}
