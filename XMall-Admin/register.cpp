#include<QMouseEvent>
#include<QLineEdit>
#include<QRegularExpression>
#include<QRegularExpressionValidator>
#include <synchapi.h>
#include <QJsonObject>
#include<QJsonDocument>
#include <QTime>
#include "register.h"
#include "ui_register.h"
#include "alertwindow.h"
#include "Service/AdminEntity.h"

extern QString GET_HOST();

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register),
    httpProxy(new HttpProxy)
{
    ui->setupUi(this);
    //去边框
    setWindowFlags(Qt::FramelessWindowHint| windowFlags());
    //背景透明
    setAttribute(Qt::WA_TranslucentBackground);

    setMinimumSize(1280, 400); setMaximumSize(1280, 420);

    ui->phonePicLineEdit->findChild<QLineEdit*>("lineEdit")->setPlaceholderText("手机号");
    ui->pswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setPlaceholderText("密码");
    ui->repswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setPlaceholderText("重新输入密码");

    ui->pswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setEchoMode(QLineEdit::Password);
    ui->repswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setEchoMode(QLineEdit::Password);


    ui->phonePicLineEdit->setPic(":/pics/icons/phone.png");
    ui->pswPicLineEdit->setPic(":/pics/icons/psw.png");
    ui->repswPicLineEdit->setPic(":/pics/icons/repsw.png");
    //正则匹配
    QRegularExpression regExpPassword("^(?![a-zA-Z]+$)(?![0-9]+$)[a-zA-Z0-9]{8,}$");
    passwordValidator.setRegularExpression(regExpPassword);
    QRegularExpression regExpPhone("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    phoneValidator.setRegularExpression(regExpPhone);


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
    ui->registerPushButton->setEnabled(true);
    ui->phonePicLineEdit->findChild<QLineEdit*>("lineEdit")->setText("");
    ui->pswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setText("");
    ui->repswPicLineEdit->findChild<QLineEdit*>("lineEdit")->setText("");
    emit retLogin(this->frameGeometry().topLeft());
}

void Register::on_registerPushButton_clicked()
{
    ui->registerPushButton->setEnabled(false);
    QString copyStr = ui->phonePicLineEdit->findChild<QLineEdit*>("lineEdit")->text();
    int pos = 0;
    QString phoneNum = copyStr;
    if (phoneValidator.validate(copyStr,pos) != QValidator::Acceptable)
    {
        qDebug()<<phoneValidator.validate(copyStr,pos);
        alertWin->setMessage("手机号格式错误");
        alertWin->show();
        ui->registerPushButton->setEnabled(true);
        return;
    }
    copyStr =  ui->pswPicLineEdit->findChild<QLineEdit*>("lineEdit")->text();
    if (passwordValidator.validate(copyStr,pos) != QValidator::Acceptable)
    {
        alertWin->setMessage("密码不得少于8位且包含字母和数字");
        alertWin->show();
        ui->registerPushButton->setEnabled(true);
        return;
    }
    QString repsw = ui->repswPicLineEdit->findChild<QLineEdit*>("lineEdit")->text();
    if (repsw != copyStr)
    {
        alertWin->setMessage("两次密码不一致");
        alertWin->show();
        ui->registerPushButton->setEnabled(true);
        return;
    }
    httpProxy->get(GET_HOST() + "/admin/phone/" + phoneNum);
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        alertWin->setMessage("手机号已被占用");
        alertWin->show();
        ui->registerPushButton->setEnabled(true);
        return;
    }
    AdminEntity admin = AdminEntity("", ui->phonePicLineEdit->findChild<QLineEdit*>("lineEdit")->text()
                                          , ui->pswPicLineEdit->findChild<QLineEdit*>("lineEdit")->text());
    QByteArray postMsg = QJsonDocument(admin.getJsonForm()).toJson();
    httpProxy->post(GET_HOST() + "/admin/register", postMsg);
    jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        alertWin->setMessage("注册成功！");
        alertWin->show();
        ui->registerPushButton->setEnabled(true);
        emit retLogin(this->frameGeometry().topLeft());
        close();
        return ;
    }
    else
    {
        alertWin->setMessage("注册失败");
        alertWin->show();
        ui->registerPushButton->setEnabled(true);
        return ;
    }
}

