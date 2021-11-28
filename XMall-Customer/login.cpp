#include "login.h"
#include "ui_login.h"
#include <QPainter>
#include<QMouseEvent>
#include<QObject>
Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    //去边框
    setWindowFlags(Qt::FramelessWindowHint| windowFlags());
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    setMinimumSize(1280, 580); setMaximumSize(1280, 580);
    registerWin = new Register;
    connect(registerWin, &Register::retLogin, this, &Login::on_retLogin);
    QImage img;
    img.load (":/pics/icons/mylogo.png");
    QPixmap pixmap(QPixmap::fromImage(img));
    QLabel* logoLabel = ui->logoLabel;
    pixmap = pixmap.scaled(120,120);
    logoLabel->setScaledContents(true);
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setPixmap(pixmap);
}

Login::~Login()
{
    delete ui;
}

void Login::mousePressEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons()==Qt::LeftButton)
    {
        p = mouseEvent->globalPosition().toPoint()-this->frameGeometry().topLeft();
    }
}

void Login::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons() & Qt::LeftButton)
    {
        move(mouseEvent->globalPosition().toPoint() - p);
    }
}


void Login::on_minimizeToolButton_clicked()
{
    showMinimized();
}


void Login::on_quitToolButton_clicked()
{
    close();
}



void Login::on_quitPushButton_clicked()
{
    close();
}


void Login::on_registerPushButton_clicked()
{
    this->hide();

    registerWin->move(this->frameGeometry().topLeft());

    registerWin->show();
}

void Login::on_retLogin(QPoint pos)
{
    this->move(pos);
    this->show();
}

