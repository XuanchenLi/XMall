#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "Service/HttpProxy.h"
#include "Service/UserInfoDto.h"
#include "Service/UserInfoEntity.h"
#include "Service/AddressEntity.h"
#include "addresslistitem.h"
#include "refreshlistwidget.h"
#include <QPushButton>
#include<QRegularExpression>
#include<QRegularExpressionValidator>
#include <QLabel>
#include <QTabBar>
#include <QScopedPointer>
#include <QFileDialog>
#include <QListWidgetItem>
extern QString GET_HOST();
extern QString GET_AVATAR_PATH();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->profileTabWidget->setTabPosition(QTabWidget::West);
    QImage img;
    img.load (":/pics/icons/mylogo.png");
    QPixmap pixmap(QPixmap::fromImage(img));
    QLabel* logoLabel = new QLabel(this);
    pixmap = pixmap.scaled(24,24);
    logoLabel->setScaledContents(true);
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setPixmap(pixmap);
    QLabel* textLabel = new QLabel(this);
    textLabel->setText("©2021 XMall。保留所有权利。");
    ui->statusbar->addPermanentWidget(logoLabel);
    ui->statusbar->addPermanentWidget(textLabel);
    connect(ui->exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->switchAccountAction,
            SIGNAL(triggered()),
            this,
            SLOT(on_switchAccountAction_trigger()));
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
     animation->setDuration(1000);
     animation->setStartValue(0);
     animation->setEndValue(1);
     animation->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_switchAccountAction_trigger()
{
    Login* loginWin = new Login;
    this->close();
    loginWin->show();
}

void MainWindow::initUserBaseInfo()
{
    ui->ackPushButton->setEnabled(true);
    ui->phoneLabel->setText(currentUser.getPhone());
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/user/entity/phone/"+currentUser.getPhone());
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        QJsonObject userEntity = jsonObject["userInfoEntity"].toObject();
        ui->nicknameLineEdit->setText(userEntity["nickname"].toString());
        ui->emailLineEdit->setText(userEntity["email"].toString());
        ui->birthdayDateEdit->setDate(QDate::fromString(userEntity["birthday"].toString(),"yyyy-MM-dd"));
        //qDebug()<<QDate::fromString(userEntity["birthday"].toString(),"yyyy-MM-dd");
        bool gender = userEntity["gender"].toBool();
        //qDebug()<<"gender:"<<gender;
        if(gender)
        {
            ui->maleRadioButton->setChecked(true);
            ui->femaleRadioButton->setChecked(false);
        }
        else
        {
            ui->maleRadioButton->setChecked(false);
            ui->femaleRadioButton->setChecked(true);
        }
        ui->remarkTextEdit->setText(userEntity["personalRemark"].toString());
        if(userEntity["icon"].toString() == "")
        {
            QImage img;
            img.load (":/pics/avatars/defaultAvatar.jpg");
            QPixmap pixmap(QPixmap::fromImage(img));
            ui->avatarLabel->setPixmap(pixmap);
        }
        else
        {
            QString filepath = userEntity["icon"].toString();
            int first = filepath.lastIndexOf ("\\");
            QString filename = filepath.right (filepath.length ()-first-1);
            QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
            httpProxy->get(GET_HOST()+GET_AVATAR_PATH()+filename);
            //QJsonObject jsonObject = httpProxy->getJsonObject();
            //qDebug()<<jsonObject["statusCode"];
            if(httpProxy->getReplyCode() == 200)
            {
                QByteArray avatarData = httpProxy->getReplyData();
                qDebug()<<"avatarData";
                QImage img;
                img.loadFromData(avatarData);
                QPixmap pixmap(QPixmap::fromImage(img));
                ui->avatarLabel->setScaledContents(true);
                ui->avatarLabel->setAlignment(Qt::AlignCenter);
                ui->avatarLabel->setPixmap(pixmap);
            }
        }
    }


}
void MainWindow::initFunction()
{
    initUserBaseInfo();
    initAddress();
}

void MainWindow::on_ackPushButton_clicked()
{
    ui->ackPushButton->setEnabled(false);
    int pos = 0;
    UserInfoEntity userInfo ;
    QRegularExpression regExp("^[a-z0-9A-Z]+[- | a-z0-9A-Z . _]+@([a-z0-9A-Z]+(-[a-z0-9A-Z]+)?\\.)+[a-z]{2,}$");
    QRegularExpressionValidator validator;
    validator.setRegularExpression(regExp);
    QString curStr =  ui->emailLineEdit->text();
    userInfo.setEmail(curStr);
    if (validator.validate(curStr,pos) != QValidator::Acceptable)
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("邮箱格式错误");
        alertWin->show();
        ui->ackPushButton->setEnabled(true);
        return;
    }
    regExp.setPattern("^[a-zA-Z0-9_-]{4,16}$");
    validator.setRegularExpression(regExp);
    curStr =  ui->nicknameLineEdit->text();
    userInfo.setNickname(curStr);
    if (validator.validate(curStr,pos) != QValidator::Acceptable)
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("昵称违规");
        alertWin->show();
        ui->ackPushButton->setEnabled(true);
        return;
    }
    curStr = ui->remarkTextEdit->toPlainText();
    userInfo.setPersonalRemark(curStr);
    if(curStr.length() > 100)
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("个性签名过长");
        alertWin->show();
        ui->ackPushButton->setEnabled(true);
        return;
    }
    userInfo.setPhone(currentUser.getPhone());
    if(ui->maleRadioButton->isChecked())
    {
        userInfo.setGender(true);
    }
    else
    {
        userInfo.setGender(false);
    }
    userInfo.setBirthday(ui->birthdayDateEdit->date());
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    QByteArray postMsg = QJsonDocument(userInfo.getEditRequestJsonForm()).toJson();
    httpProxy->post(GET_HOST() + "/user/update",postMsg);
    if(httpProxy->getReplyCode() == 200)
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("保存成功");
        alertWin->show();
        ui->ackPushButton->setEnabled(true);
        initUserBaseInfo();
        update();
    }
    else
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("保存失败");
        alertWin->show();
        ui->ackPushButton->setEnabled(true);
    }
    return;
}


void MainWindow::on_avatarPushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择一张图片"), "C:", tr("Image Files (*.png *.jpg *.bmp *jpeg)"));
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->uploadPicture(GET_HOST() + "/user/phone/" + currentUser.getPhone() + "/uploadAvatar", fileName);
    if(httpProxy->getReplyCode() == 200)
    {
        initUserBaseInfo();
    }
}


void MainWindow::on_saveAddressPushButton_clicked()
{
    ui->saveAddressPushButton->setEnabled(false);
    AddressEntity addressEntity;
    addressEntity.setUserPhone(currentUser.getPhone());
    addressEntity.setProvince(ui->cityWidget->getProvince());
    addressEntity.setCity(ui->cityWidget->getCity());
    addressEntity.setRegion(ui->cityWidget->getRegion());
    QString detail = ui->detailAddressTextEdit->toPlainText();
    if(detail.length() > 50)
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("详细地址过长");
        alertWin->show();
        ui->saveAddressPushButton->setEnabled(true);
        return ;
    }
    addressEntity.setDetail(detail);
    QRegularExpression regExp("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    QRegularExpressionValidator validator;
    validator.setRegularExpression(regExp);
    QString phone = ui->recvPhonelineEdit->text();
    int pos = 0;
    if(validator.validate(phone,pos) != QValidator::Acceptable)
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("手机号格式错误");
        alertWin->show();
        ui->saveAddressPushButton->setEnabled(true);
        return ;
    }
    addressEntity.setPhone(phone);
    addressEntity.setName(ui->recvNameLineEdit->text());
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->post(GET_HOST() + "/user/address", addressEntity.getQByteArrayForm());
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        initAddress();
        //
    }
    else
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
        ui->saveAddressPushButton->setEnabled(true);
        return ;
    }
    ui->saveAddressPushButton->setEnabled(true);
}

void MainWindow::initAddress()
{
    ui->addressListWidget->play(currentUser.getPhone());
}
