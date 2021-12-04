#include "topbar.h"
#include "ui_topbar.h"
#include<QScreen>
TopBar::TopBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopBar)
{
    ui->setupUi(this);

    QPushButton* screenBtn = ui->screenPushButton;
    screenBtn->setIcon(QIcon(":/pics/icons/fullScreen.jpg"));
    screenState = Qt::WindowNoState;
    //previousSize = faWin->geometry().size();
}

TopBar::~TopBar()
{
    delete ui;
}

void TopBar::on_screenPushButton_clicked()
{
    QPushButton* screenBtn = ui->screenPushButton;
    if(screenState == Qt::WindowFullScreen)//普通
    {
        screenBtn->setIcon(QIcon(":/pics/icons/fullScreen.jpg"));
        screenState = Qt::WindowNoState;
        //faWin->showNormal();
        faWin->resize(previousSize);

    }
    else//全屏
    {
        screenBtn->setIcon(QIcon(":/pics/icons/normalScreen.jpg"));
        faWin->hide();
        faWin->show();
        previousSize = faWin->geometry().size();
        //QPoint curPoint = faWin->mapToGlobal(QPoint(0,0));
        QScreen *curScreen = QGuiApplication::primaryScreen();
        //qDebug()<<curScreen->geometry();
        //qDebug()<<faWin->maximumSize();
        /* 先更新子控件的屏幕坐标，然后设置子控件全屏显示 */
        //faWin->showFullScreen();
        qDebug()<<curScreen->geometry().size();
        faWin->resize(curScreen->geometry().size());

        qDebug()<<faWin->size();
        //faWin->setWindowState(Qt::WindowMaximized);
        screenState = Qt::WindowFullScreen;


    }
}

void::TopBar::setFatherWindow(QWidget* fa)
{
    faWin = fa;
}
