#include "login.h"
#include <QApplication>
#include <QString>
//Test

#include<topbar.h>
#include<mainwindow.h>
#include <QtNetwork/QNetworkAccessManager>
#include<QtNetwork/QNetworkReply>
#include<QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();

    //TEST

    //
    return a.exec();
}


QString GET_HOST()
{
    static QString MY_HOST = "http://127.0.0.1:8080";
    return MY_HOST;
}
