#include "productionwindow.h"
#include "ui_productionwindow.h"
#include "Service/FreightEntity.h"
#include "Service/CartEntity.h"
#include "Service/HttpProxy.h"
#include "Service/OrderEntity.h"
#include "Service/OrderItemEntity.h"
#include "orderwindow.h"
#include "alertwindow.h"
#include <QJsonArray>
#include <QLabel>

extern QString GET_HOST();
extern QString GET_PRODUCT_BIG_PATH();
ProductionWindow::ProductionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductionWindow)
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

ProductionWindow::~ProductionWindow()
{
    delete ui;
}

const ProductEntity &ProductionWindow::getProduct() const
{
    return product;
}

void ProductionWindow::setProduct(const ProductEntity &newProduct)
{
    product = newProduct;
    //
    if(product.getLimitation() != -1)
    {
        ui->spinBox->setMaximum(qMin(product.getLimitation(), product.getStorage()));
    }
    else {
        ui->spinBox->setMaximum(product.getStorage());
    }
    ui->nameLabel->setText(product.getName());
    ui->priceLabel->setText("￥ " + QString::number(product.getCurrentPrice(), 'F', 2));
    ui->introductionBrowser->setText(product.getIntroduction());
    ui->unitLabel->setText(product.getUnit());
    ui->storageLabel->setText("剩余：" + QString::number(product.getStorage()) + " " + product.getUnit());
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
//    FreightEntity freight;
//    httpProxy->get(GET_HOST() + "/freight/id/" + QString::number(product.getFreightTemplateId()));
//    QJsonObject jsonObject = httpProxy->getJsonObject();
//    if(jsonObject["statusCode"] == "SUCCESS")
//    {
//        freight = FreightEntity::parseJson(jsonObject["freightEntity"].toObject());
//        ui->freightLabel->setText("运费：￥ " + QString::number(freight.getPrice(), 'f', 2));
//    }
    ui->freightLabel->setText("运费：￥ " + QString::number(product.getFreightPrice(), 'f', 2));
    QString filepath = product.getBigPicAddress();
    int first = filepath.lastIndexOf ("\\");
    QString filename = filepath.right (filepath.length ()-first-1);
    httpProxy->get(GET_HOST()+GET_PRODUCT_BIG_PATH()+filename);
    if(httpProxy->getReplyCode() == 200)
    {
        QByteArray avatarData = httpProxy->getReplyData();
        //qDebug()<<"avatarData";
        QImage img;
        img.loadFromData(avatarData);
        QPixmap pixmap(QPixmap::fromImage(img));
        ui->bigPicLabel->setScaledContents(true);
        ui->bigPicLabel->setAlignment(Qt::AlignCenter);
        ui->bigPicLabel->setPixmap(pixmap);
    }
    if (product.getLimitation() != -1)
    {
        ui->limitationLabel->setText("限购 " + QString::number(product.getLimitation()) + " " + product.getUnit());
    }
    if(product.getStorage() <= 0)
    {
        ui->storageLabel->setText("缺货");
    }
    if(product.getStatus() == product.COMING_SOON)
    {
        ui->orderPushButton->setText("尚未开售");
        ui->orderPushButton->setEnabled(false);
        ui->orderPushButton->setStyleSheet("background-color: rgb(88,88,88)");
    }
    else if(product.getStatus() == product.NOT_ON_SALE)
    {
        ui->orderPushButton->setText("已下架");
        ui->orderPushButton->setEnabled(false);
        ui->orderPushButton->setStyleSheet("background-color: rgb(88,88,88)");
    }

    //initComment();
}

const QString &ProductionWindow::getPhone() const
{
    return phone;
}

void ProductionWindow::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

void ProductionWindow::on_cartPushButton_clicked()
{
    CartEntity cart;
    cart.setId(-1);
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    //
    qDebug()<<phone;
    httpProxy->get(GET_HOST() + "/cart/phone/" + phone);
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray carts = jsonObject["cartEntityList"].toArray();
        for (int i =0; i<carts.count(); ++i)
        {
            CartEntity item = CartEntity::parseJson(carts[i].toObject());
            if(item.getProduct_id() == product.getId() && item.getDel() == false)
            {
                cart = item;
                break;
            }
        }
    }else
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("与服务器失去连接");
        alertWin->show();
        return;
    }
    if(cart.getId() == -1)
    {
        cart.setCount(ui->spinBox->value());
        cart.setChecked(true);
        cart.setDel(false);
        cart.setProduct_id(product.getId());
        cart.setUserPhone(phone);
        httpProxy->post(GET_HOST() + "/cart/add",cart.getQByteArrayForm());
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"] == "SUCCESS")
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("添加成功");
            alertWin->show();
            emit addCart();
            return;
        }
        else
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("与服务器失去连接");
            alertWin->show();
            return;
        }
    }
    else
    {
        int exist = cart.getCount();
        //cart.setIsChecked(true);
        int add = ui->spinBox->value();
        if ((exist + add > product.getLimitation() && product.getLimitation() != -1)|| exist + add > product.getStorage())
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("无法加入更多该商品");
            alertWin->show();
            return;
        }
        cart.setCount(exist + add);
        httpProxy->post(GET_HOST() + "/cart/updateCount",cart.getQByteArrayForm());
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"] == "SUCCESS")
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("添加成功");
            alertWin->show();
            emit addCart();
            return;
        }
        else
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("与服务器失去连接");
            alertWin->show();
            return;
        }
        if(!cart.getChecked())
        {
            httpProxy->get(GET_HOST() + "/cart/check/phone" + cart.getUserPhone()
                           + "/id/" + QString::number(cart.getId()));
        }
    }
}


void ProductionWindow::on_orderPushButton_clicked()
{
    if (ui->spinBox->value() <= 0) return ;
    OrderItemEntity item;
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    //FreightEntity freight;
    httpProxy->get(GET_HOST() + "/product/id/" + QString::number(product.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        ProductEntity newProduct = ProductEntity::parseJson(jsonObject["productEntity"].toObject());
        setProduct(newProduct);
        int curCount = ui->spinBox->value();
        if((newProduct.getLimitation() != -1 && curCount > newProduct.getLimitation())
                || curCount > newProduct.getStorage())
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("数量超限");
            alertWin->show();
            return ;
        }
        item = item.fromProductEntity(newProduct);
        item.setCount(curCount);
        //QVector<int> items;
        //items.clear();
        //qDebug()<<item.getCount();
        //items.resize(5);
        //qDebug()<<items.capacity();
        //items.append(1);
        //qDebug()<<"orderWin";
        emit order(item);
    }
}

