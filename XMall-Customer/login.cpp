#include "login.h"
#include "ui_login.h"
#include <QPainter>
#include<QMouseEvent>
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
}

Login::~Login()
{
    delete ui;
}

void Login::mousePressEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons()==Qt::LeftButton)
    {
        p = mouseEvent->globalPos()-this->frameGeometry().topLeft();
    }
}

void Login::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons() & Qt::LeftButton)
    {
        move(mouseEvent->globalPos() - p);
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

