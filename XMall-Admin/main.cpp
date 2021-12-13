#include "login.h"

#include <QApplication>

//test
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();

    //text
    MainWindow mw;
    mw.show();

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
