#include "register.h"
#include "ui_register.h"
#include<QMouseEvent>
#include<QLineEdit>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    //去边框
    setWindowFlags(Qt::FramelessWindowHint| windowFlags());
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);

    setMinimumSize(1280, 1280); setMaximumSize(1280, 1280);

    ui->namePicLineEdit->findChild<QLineEdit*>("lineEdit")->setPlaceholderText("用户名");
    ui->phonePicLineEdit->findChild<QLineEdit*>("lineEdit")->setPlaceholderText("手机号");
    ui->emailPicLineEdit->findChild<QLineEdit*>("lineEdit")->setPlaceholderText("邮箱");
    ui->pswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setPlaceholderText("密码");
    ui->repswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setPlaceholderText("重新输入密码");

    ui->pswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setEchoMode(QLineEdit::Password);
    ui->repswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setEchoMode(QLineEdit::Password);


    ui->namePicLineEdit->setPic(":/pics/icons/user.png");
    ui->phonePicLineEdit->setPic(":/pics/icons/phone.png");
    ui->emailPicLineEdit->setPic(":/pics/icons/email.png");
    ui->pswPicLineEdit->setPic(":/pics/icons/psw.png");
    ui->repswPicLineEdit->setPic(":/pics/icons/repsw.png");

    QImage img;
    img.load (":/pics/icons/mylogo.png");
    QPixmap pixmap(QPixmap::fromImage(img));
    QLabel* logoLabel = ui->logoLabel;
    pixmap = pixmap.scaled(120,120);
    logoLabel->setScaledContents(true);
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setPixmap(pixmap);

}

Register::~Register()
{
    delete ui;
}

void Register::mousePressEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons()==Qt::LeftButton)
    {
        p = mouseEvent->globalPosition().toPoint()-this->frameGeometry().topLeft();
    }
}

void Register::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if(mouseEvent->buttons() & Qt::LeftButton)
    {
        move(mouseEvent->globalPosition().toPoint() - p);
    }
}


void Register::on_minimizeToolButton_clicked()
{
    showMinimized();
}


void Register::on_quitToolButton_clicked()
{
    close();
    emit retLogin(this->frameGeometry().topLeft());
}
