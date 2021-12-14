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

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Login w;
    w.show();

    //TEST
    MainWindow mw;
    mw.show();
    mw.initCategoryMenu();
    //
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
