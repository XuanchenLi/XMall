#include "orderviewitem.h"
#include "ui_orderviewitem.h"
#include "orderwindow.h"
#include <QMouseEvent>
OrderViewItem::OrderViewItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderViewItem)
{
    ui->setupUi(this);
}

OrderViewItem::~OrderViewItem()
{
    qDebug()<<"delete";
    delete ui;
}

const OrderEntity &OrderViewItem::getOrder() const
{
    return order;
}

void OrderViewItem::setOrder(const OrderEntity &newOrder)
{
    order = newOrder;
    //
    ui->orderSn->setText(order.getOrderSn());
    ui->creatTime->setText(order.getCreatTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->payPrice->setText("￥ " + QString::number(order.getPayPrice(),'f',2));
    switch(order.getStatus())
    {
        case OrderEntity::WAIT_PAY:ui->status->setText("未付款"); break;
        case OrderEntity::WAIT_DELIVERY:ui->status->setText("待发货"); break;
        case OrderEntity::WAIT_RECV:ui->status->setText("待收货"); break;
        case OrderEntity::WAIT_REFUND:ui->status->setText("退款申请中"); break;
        case OrderEntity::DIE:ui->status->setText("已关闭"); break;
        case OrderEntity::COMPLETED:ui->status->setText("已完成"); break;
    }
}
void OrderViewItem::mouseClicked()
{
    //处理代码
    //qDebug()<<"open detail page";
    OrderWindow* win = new OrderWindow;
    win->setOrderEntity(order);
    win->initOld();
    win->show();

}

void OrderViewItem::mousePressEvent(QMouseEvent *ev)
{

    mousePos = QPoint(ev->position().x(), ev->position().y());
}

void OrderViewItem::mouseReleaseEvent(QMouseEvent *ev)
{
    if(mousePos == QPoint(ev->position().x(), ev->position().y()))
        mouseClicked();
}

