#include "login.h"

#include <QApplication>

//test
#include "mainwindow.h"
#include "productlistwidget.h"
#include "productrefreshwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();

    //text
    MainWindow mw;
    mw.show();
    ProductRefreshWidget m;
    m.play();
    m.show();
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
