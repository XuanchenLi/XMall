#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "Service/FreightEntity.h"
#include "Service/OrderRefundFormEntity.h"
#include "Service/HttpProxy.h"
#include "alertwindow.h"
#include "QPushButton"
#include <QJsonArray>
#include <QLabel>
extern QString GET_HOST();
OrderWindow::OrderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderWindow)
{
    ui->setupUi(this);
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
}

OrderWindow::~OrderWindow()
{
    delete ui;
}


void OrderWindow::initOld()
{
    itemVector.clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);

    //添加订单商品
    //LABEL初始化
    ui->itemList->play(orderEntity.getOrderSn());
    ui->orderSnLabel->setText(orderEntity.getOrderSn());
    ui->dateLabel->setText(orderEntity.getCreatTime().toString("yyyy-MM-dd hh:mm:ss"));
//    qDebug()<<orderEntity.getCreatTime().toString("yyyy-MM-dd hh:mm:ss");
//    qDebug()<<orderEntity.getCreatTime();
    switch(orderEntity.getStatus())
    {
        case OrderEntity::WAIT_PAY:ui->statusLabel->setText("未付款"); break;
        case OrderEntity::WAIT_DELIVERY:ui->statusLabel->setText("待发货"); break;
        case OrderEntity::WAIT_RECV:ui->statusLabel->setText("待收货"); break;
        case OrderEntity::WAIT_REFUND:ui->statusLabel->setText("退款申请中"); break;
        case OrderEntity::DIE:ui->statusLabel->setText("已关闭"); break;
        case OrderEntity::COMPLETED:ui->statusLabel->setText("已完成"); break;
    }
    if(orderEntity.getStatus() != OrderEntity::WAIT_PAY)
    {
        ui->wechatRadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, 1);
        ui->wechatRadioButton->setFocusPolicy(Qt::NoFocus);
        ui->alipayRadioButton->setAttribute(Qt::WA_TransparentForMouseEvents, 1);
        ui->alipayRadioButton->setFocusPolicy(Qt::NoFocus);
        switch(orderEntity.getPayType())
        {
        case OrderEntity::ALIPAY:
        {
            qDebug()<<orderEntity.getPayType();
            ui->alipayRadioButton->setChecked(true);
            break;
        }
        case OrderEntity::WECHAT:
        {
            ui->wechatRadioButton->setChecked(true);
            break;
        }
        }
        //运费
        QLabel* address = new QLabel;
        address->setText(orderEntity.getUserAddressInfo());
        ui->addressList->clear();
        ui->addressList->insertAddressView(address);
        ui->freightLabel->setText("￥ " + QString::number(orderEntity.getFreightPrice(),'f',2));
        //
        ui->totLabel->setText("￥ " + QString::number(orderEntity.getTotPrice(),'f',2));

        ui->payLabel->setText("￥ " + QString::number(orderEntity.getPayPrice(),'f',2));
        //
    }
    else
    {
        ui->addressList->play(orderEntity.getUserPhone());
        ui->freightLabel->setText("￥ " + QString::number(orderEntity.getFreightPrice(),'f',2));
        //
        ui->totLabel->setText("￥ " + QString::number(orderEntity.getTotPrice(),'f',2));
        //此处可加入促销运算
        //ui->payLabel->setText("￥ " + QString::number(calculateWithPromotion(),'f',2))
        payPrice = totPrice;
        ui->payLabel->setText(QString::number(orderEntity.getPayPrice(),'f',2));
        //
    }
    newByStatus();

}
const QVector<OrderItemEntity> &OrderWindow::getItemVector() const
{
    return itemVector;
}

void OrderWindow::setItemVector(const QVector<OrderItemEntity> &newItemVector)
{
    itemVector = newItemVector;
}

const QString &OrderWindow::getPhone() const
{
    return phone;
}

void OrderWindow::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

const OrderEntity &OrderWindow::getOrderEntity() const
{
    return orderEntity;
}

void OrderWindow::setOrderEntity(const OrderEntity &newOrderEntity)
{
    orderEntity = newOrderEntity;
}
double OrderWindow::calculate()
{
    QJsonArray request;
    for (int i = 0; i < itemVector.length(); ++i)
    {
        QJsonObject obj = itemVector[i].getJsonForm();
        //qDebug()<<"bug"<<cartVector[i]->getCartEntity().getCount();
        request.append(obj);
    }
    if(!request.empty())
    {
        QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
        httpProxy->post(GET_HOST() + "/order/calculate", QJsonDocument(request).toJson());
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() != "SUCCESS")
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("发生异常");
            alertWin->show();
            return 999999999;
        }
        else
        {
            return jsonObject["res"].toDouble();
        }
    }else{
        return 0;
    }
}



void OrderWindow::newByStatus()
{
    clearLayout();
    switch(orderEntity.getStatus())
    {
    case OrderEntity::WAIT_REFUND:
    {
        QPushButton* ackBtn = new QPushButton(tr("同意"));
        ui->BtnHorizontalLayout->addWidget(ackBtn);
        connect(ackBtn, &QPushButton::clicked, this, &OrderWindow::on_ackPushButton_clicked);
        QPushButton* declineBtn = new QPushButton(tr("拒绝"));
        ui->BtnHorizontalLayout->addWidget(declineBtn);
        connect(declineBtn, &QPushButton::clicked, this, &OrderWindow::on_declinePushButton_clicked);
        break;
    }
    case OrderEntity::WAIT_DELIVERY:
    {
        QPushButton* deliveryBtn = new QPushButton(tr("发货"));
        ui->BtnHorizontalLayout->addWidget(deliveryBtn);
        connect(deliveryBtn, &QPushButton::clicked, this, &OrderWindow::on_deliveryPushButton_clicked);
        break;
    }

    }
}

void OrderWindow::clearLayout()
{
    QLayoutItem *child;
     while ((child = ui->BtnHorizontalLayout->takeAt(0)) != 0)
     {
            //setParent为NULL，防止删除之后界面不消失
            if(child->widget())
            {
                child->widget()->setParent(NULL);
            }

            delete child;
     }

}

void OrderWindow::on_ackPushButton_clicked()
{

    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/ackRefund/id/" + QString::number(orderEntity.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
        return ;
    }
    orderEntity.setStatus(OrderEntity::DIE);
    initOld();
}

void OrderWindow::on_declinePushButton_clicked()
{

    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/declineRefund/id/" + QString::number(orderEntity.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();

        return ;
    }
    httpProxy->get(GET_HOST() + "/order/RefundForm/orderSn/" + orderEntity.getOrderSn());
    jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();

        return ;
    }
    OrderRefundFormEntity form = OrderRefundFormEntity::parseJson(jsonObject["orderRefundFormEntity"].toObject());
    orderEntity.setStatus(form.getPreStatus());
    initOld();
}
void OrderWindow::on_deliveryPushButton_clicked()
{
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/delivery/id/" + QString::number(orderEntity.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
        return ;
    }

    orderEntity.setStatus(OrderEntity::WAIT_RECV);
    initOld();
}
