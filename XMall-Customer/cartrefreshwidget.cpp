#include "cartrefreshwidget.h"
#include "ui_cartrefreshwidget.h"
#include "Service/HttpProxy.h"
#include "alertwindow.h"
#include <QJsonArray>
extern QString GET_HOST();
CartRefreshWidget::CartRefreshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartRefreshWidget)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(msliderChanged(int)),  this , SLOT(onScrollBarMoved(int)));
    connect(ui->listWidget, SIGNAL(reachedBottom()),  this , SLOT(onReachedBottom()));
}

CartRefreshWidget::~CartRefreshWidget()
{
    clear();
    delete ui;
}
void  CartRefreshWidget::onScrollBarMoved( int  v)
{

}

void  CartRefreshWidget::onReachedBottom()
{

}

void CartRefreshWidget::setCartVector(QString phone)
{
    clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/cart/phone/" + phone);
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray carts = jsonObject["cartEntityList"].toArray();
        for (int i =0; i<carts.count(); ++i)
        {
            CartListItem* item = new CartListItem;
            connect(item, &CartListItem::deleteRecord, this, &CartRefreshWidget::on_deleteRecord);
            connect(item, &CartListItem::itemChanged, this, &CartRefreshWidget::on_itemChanged);
            item->setCartEntity(CartEntity::parseJson(carts[i].toObject()));
            cartVector.push_back(item);
        }
    }
}
void CartRefreshWidget::insertCart(CartListItem* Item)
{
    if (Item == nullptr)
    {
        qDebug()<<"空指针";
        return;
    }
    QListWidgetItem* pItem = new QListWidgetItem();
    ui->listWidget->addItem(pItem);
    pItem->setSizeHint(Item->size());
    ui->listWidget->setItemWidget(pItem,Item);

}

void CartRefreshWidget::clear()
{
    curIndex = 0;
    for (auto item : cartVector)
    {
        delete item;
    }
    cartVector.clear();
}
void CartRefreshWidget::play(QString phone)
{
    this->phone = phone;
    ui->listWidget->clear();
    setCartVector(phone);
    for(curIndex = 0; curIndex < cartVector.length(); ++curIndex)
    {
        insertCart(cartVector[curIndex]);
    }
    calculate();

}
void CartRefreshWidget::on_deleteRecord(bool signal)
{
    if(signal)
    {
        this->play(phone);
    }
    else
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("删除失败");
        alertWin->show();
    }
}

double CartRefreshWidget::calculate()
{
    double res = 0.0;
    QJsonArray request;
    for (int i = 0; i < cartVector.length(); ++i)
    {
        if(cartVector[i]->isChecked())
        {
            QJsonObject obj = cartVector[i]->getCartEntity().getJsonForm();
            //qDebug()<<"bug"<<cartVector[i]->getCartEntity().getCount();
            request.append(obj);
            res += cartVector[i]->getProduct().getCurrentPrice() * cartVector[i]->getSpinBoxCount();
        }
    }
    if(!request.empty())
    {
        QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
        httpProxy->post(GET_HOST() + "/cart/calculate",QJsonDocument(request).toJson());
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() == "SUCCESS")
        {
            double remoteRes = jsonObject["res"].toDouble();
//            qDebug()<<"local:"<<res;
//            qDebug()<<"remote:"<<remoteRes;
            if(res != remoteRes)
            {
                //Refresh
                play(phone);
                return 99999999;
            }
            else
            {
                emit finishCalculate(remoteRes);
                return remoteRes;
            }
        }
        else
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("与服务器失去连接");
            alertWin->show();
            return 99999999;
        }
    }
    else
    {
        emit finishCalculate(res);
        return res;
    }
    emit finishCalculate(res);
    return res;
}

void CartRefreshWidget::checkAll()
{
    for (int i = 0; i < cartVector.length(); ++i)
    {
        if(!cartVector[i]->isChecked())
        {
            cartVector[i]->check();
        }
    }
    calculate();
}
void CartRefreshWidget::on_itemChanged()
{
    calculate();
}

QVector<CartEntity> CartRefreshWidget::getSelectedItemsCartEntity()
{
    QVector<CartEntity> products;
    for (int i = 0; i < cartVector.length(); ++i)
    {
        if(cartVector[i]->isChecked())
        {
            products.append(cartVector[i]->getCartEntity());
        }
    }
    return products;
}
QVector<ProductEntity> CartRefreshWidget::getSelectedItemsProductEntity()
{
    QVector<ProductEntity> products;
    for (int i = 0; i < cartVector.length(); ++i)
    {
        if(cartVector[i]->isChecked())
        {
            products.append(cartVector[i]->getProduct());
        }
    }
    return products;
}

void CartRefreshWidget::delCart(QVector<OrderItemEntity> items)
{
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);

    for(auto item : items)
    {
        for(auto cart : cartVector)
        {
            if ( cart->getProduct().getId() == item.getProductId())
            {
                httpProxy->get(GET_HOST() + "/cart/delete/phone/" + phone + "/id/" + QString::number(cart->getCartEntity().getId()));
                QJsonObject jsonObject = httpProxy->getJsonObject();
                if(jsonObject["statusCode"].toString() != "SUCCESS")
                {
                    AlertWindow* alertWin = new AlertWindow;
                    alertWin->setMessage("发生错误");
                    alertWin->show();
                    return ;
                }
                break;
            }
        }
    }
}
