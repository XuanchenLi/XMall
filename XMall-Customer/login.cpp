#include "login.h"
#include "ui_login.h"
#include "alertwindow.h"
#include "mainwindow.h"
#include "Service/UserInfoDto.h"
#include <QPainter>
#include<QMouseEvent>
#include<QObject>
extern QString GET_HOST();
Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
    , httpProxy(new HttpProxy)
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
    alertWin = new AlertWindow;
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


void Login::on_loginPushButton_clicked()
{
    ui->loginPushButton->setEnabled(false);
    QString phone = ui->accountLineEdit->text();
    QString psw = ui->passwordLineEdit->text();
    httpProxy->get(GET_HOST() + "/user/phone/" + phone);
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        if (jsonObject["userInfoDto"].toObject()["password"] == psw)
        {
            qDebug()<<"登陆成功";
            UserInfoDto currentUser = UserInfoDto("",phone
                                                  ,psw
                                                  ,"");
            mainWin = new MainWindow;
            mainWin->setCurrentUser(currentUser);
            this->close();
            mainWin->show();
            mainWin->initFunction();
        }
        else
        {
            alertWin->setMessage("账号或密码错误");
            alertWin->show();
            ui->loginPushButton->setEnabled(true);
            return;
        }
    }
    else
    {
        alertWin->setMessage("账号或密码错误");
        alertWin->show();
        ui->loginPushButton->setEnabled(true);
        return;
    }

}

