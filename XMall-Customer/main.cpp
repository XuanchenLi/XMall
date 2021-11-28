#include "login.h"
#include <QApplication>

//Test
#include<xmallmainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();

    //TEST
    XMallMainWindow win;
    win.show();

    return a.exec();
}
