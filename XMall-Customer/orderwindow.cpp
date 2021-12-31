#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "Service/FreightEntity.h"
#include "Service/CartEntity.h"
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

void OrderWindow::initNew(QVector<OrderItemEntity> items)
{
    itemVector = items;
    ui->addressList->play(phone);
    //创建订单
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/newOrder/" + phone);
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] != "SUCCESS")
    {
        return ;
    }
    orderEntity = OrderEntity::parseJson(jsonObject["orderEntity"].toObject());
    //添加订单商品
    QJsonArray request;
    for (int i = 0; i < items.length(); ++i)
    {
        items[i].setOrderSn(orderEntity.getOrderSn());
        QJsonObject obj = items[i].getJsonForm();
        request.append(obj);
    }
    if(!request.empty())
    {
        httpProxy->post(GET_HOST() + "/order/saveItems", QJsonDocument(request).toJson());
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() != "SUCCESS")
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("发生异常");
            alertWin->show();
            return ;
        }
    }else{
        return ;
    }
    //删除购物车
    emit delCart(items);
    for (int i = 0; i < items.length(); ++i)
    {
        items[i].setOrderSn(orderEntity.getOrderSn());
        QJsonObject obj = items[i].getJsonForm();
        request.append(obj);
    }
    //LABEL初始化
    ui->itemList->play(orderEntity.getOrderSn());
    ui->orderSnLabel->setText(orderEntity.getOrderSn());
    ui->dateLabel->setText(orderEntity.getCreatTime().toString("yyyy-MM-dd hh:mm:ss"));
    //qDebug()<<orderEntity.getCreatTime().toString("yyyy-MM-dd hh:mm:ss");
    switch(orderEntity.getStatus())
    {
        case OrderEntity::WAIT_PAY:ui->statusLabel->setText("未付款"); break;
        case OrderEntity::WAIT_DELIVERY:ui->statusLabel->setText("待发货"); break;
        case OrderEntity::WAIT_RECV:ui->statusLabel->setText("待收货"); break;
        case OrderEntity::WAIT_REFUND:ui->statusLabel->setText("退款申请中"); break;
        case OrderEntity::DIE:ui->statusLabel->setText("已关闭"); break;
        case OrderEntity::COMPLETED:ui->statusLabel->setText("已完成"); break;
    }
    //运费
    freightPrice = 0;
    for(auto item : items)
    {
        httpProxy->get(GET_HOST() + "/product/id/" + QString::number(item.getProductId()));
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() == "SUCCESS")
        {
            ProductEntity product = ProductEntity::parseJson(jsonObject["productEntity"].toObject());
            if (product.getFreightPrice() > freightPrice)
                freightPrice = product.getFreightPrice();
        }else
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("发生异常");
            alertWin->show();
            return ;
        }
    }
    orderEntity.setFreightPrice(freightPrice);
    ui->freightLabel->setText("￥ " + QString::number(freightPrice,'f',2));
    //
    totPrice = calculate() + freightPrice;
    orderEntity.setPayPrice(totPrice);
    orderEntity.setTotPrice(totPrice);
    ui->totLabel->setText("￥ " + QString::number(totPrice,'f',2));
    //此处可加入促销运算
    //ui->payLabel->setText("￥ " + QString::number(calculateWithPromotion(),'f',2))
    payPrice = totPrice;
    ui->payLabel->setText(ui->totLabel->text());
    httpProxy->post(GET_HOST() + "/order/update", orderEntity.getQByteArrayForm());
    jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("发生异常");
        alertWin->show();
        return ;
    }
    //
    newByStatus();

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

void OrderWindow::on_orderPushButton_clicked()
{
//    QString name = sender()->objectName();
//    QPushButton* btn = ui->BtnHorizontalLayout->findChild<QPushButton*>(name);
//    btn->setEnabled(false);
    if(!ui->alipayRadioButton->isChecked() && ! ui->wechatRadioButton->isChecked())
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("未选择支付方式");
        orderEntity.setPayType(orderEntity.NONE);
        alertWin->show();
//        btn->setEnabled(true);
        return ;
    }
    else{
        if(ui->alipayRadioButton->isChecked())
        {
            orderEntity.setPayType(orderEntity.ALIPAY);
        }
        else if (ui->wechatRadioButton->isChecked())
        {
            orderEntity.setPayType(orderEntity.WECHAT);
        }
    }
    QString address = ui->addressList->selectedAddress();
    if(address == "")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("未选择地址");
        alertWin->show();
//        btn->setEnabled(true);
        return ;
    }
    else
    {
        orderEntity.setUserAddressInfo(ui->addressList->selectedAddress());
    }
    //
    orderEntity.setCouponPrice(0);
    orderEntity.setPromotionPrice(0);
    //
    orderEntity.setFreightPrice(freightPrice);
    orderEntity.setPayPrice(payPrice);
    orderEntity.setTotPrice(totPrice);
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->post(GET_HOST() + "/order/pay", orderEntity.getQByteArrayForm());
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("支付失败");
        alertWin->show();
//        btn->setEnabled(true);
        return ;
    }
    AlertWindow* alertWin = new AlertWindow;
    alertWin->setMessage("支付成功");
    alertWin->show();
    orderEntity.setStatus(OrderEntity::WAIT_DELIVERY);
    initOld();
}

void OrderWindow::newByStatus()
{
    clearLayout();
    switch(orderEntity.getStatus())
    {
    case OrderEntity::WAIT_PAY:
    {

        QPushButton* payBtn = new QPushButton(tr("立即付款"));
        ui->BtnHorizontalLayout->addWidget(payBtn);
        connect(payBtn, &QPushButton::clicked, this, &OrderWindow::on_orderPushButton_clicked);
        QPushButton* dieBtn = new QPushButton(tr("取消订单"));
        ui->BtnHorizontalLayout->addWidget(dieBtn);
        connect(dieBtn, &QPushButton::clicked, this, &OrderWindow::on_diePushButton_clicked);
        break;
    }

    case OrderEntity::WAIT_DELIVERY:
    {
        QPushButton* refundBtn = new QPushButton(tr("申请退款"));
        ui->BtnHorizontalLayout->addWidget(refundBtn);
        connect(refundBtn, &QPushButton::clicked, this, &OrderWindow::on_refundPushButton_clicked);
        break;
    }
    case OrderEntity::WAIT_RECV:
    {
        QPushButton* refundBtn = new QPushButton(tr("申请退款"));
        ui->BtnHorizontalLayout->addWidget(refundBtn);
        connect(refundBtn, &QPushButton::clicked, this, &OrderWindow::on_refundPushButton_clicked);
        QPushButton* recvBtn = new QPushButton(tr("确认收货"));
        ui->BtnHorizontalLayout->addWidget(recvBtn);
        connect(recvBtn, &QPushButton::clicked, this, &OrderWindow::on_recvPushButton_clicked);
        break;
    }
    case OrderEntity::COMPLETED:
    {
        QPushButton* refundBtn = new QPushButton(tr("申请退款"));
        ui->BtnHorizontalLayout->addWidget(refundBtn);
        connect(refundBtn, &QPushButton::clicked, this, &OrderWindow::on_refundPushButton_clicked);
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

void OrderWindow::on_recvPushButton_clicked()
{
//    QString name = sender()->objectName();
//    QPushButton* btn = ui->BtnHorizontalLayout->findChild<QPushButton*>(name);
//    btn->setEnabled(false);
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/recv/id/" + QString::number(orderEntity.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
//        btn->setEnabled(true);
        return ;
    }
//    btn->setEnabled(true);
    orderEntity.setStatus(OrderEntity::COMPLETED);
    initOld();
}

void OrderWindow::on_refundPushButton_clicked()
{
//    QString name = sender()->objectName();
//    QPushButton* btn = ui->BtnHorizontalLayout->findChild<QPushButton*>(name);
//    btn->setEnabled(false);
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/refund/id/" + QString::number(orderEntity.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
//        btn->setEnabled(true);
        return ;
    }
//    btn->setEnabled(true);
    orderEntity.setStatus(OrderEntity::WAIT_REFUND);
    initOld();
}
void OrderWindow::on_diePushButton_clicked()
{

    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/order/die/id/" + QString::number(orderEntity.getId()));
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
