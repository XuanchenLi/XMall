#include "orderlistitem.h"
#include "ui_orderlistitem.h"
#include "Service/HttpProxy.h"
extern QString GET_HOST();
extern QString GET_PRODUCT_SMALL_PATH();
OrderListItem::OrderListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderListItem)
{
    ui->setupUi(this);
}

OrderListItem::~OrderListItem()
{
    delete ui;
}

const OrderItemEntity &OrderListItem::getItem() const
{
    return item;
}

void OrderListItem::setItem(const OrderItemEntity &newItem)
{
    item = newItem;
    //
    ui->nameLabel->setText(item.getName());
    ui->countLabel->setText(QString::number(item.getCount()));
    ui->priceLabel->setText("￥ " + QString::number(item.getCurrentPrice(),'f',2));
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/product/id/" + QString::number(item.getProductId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        setProduct(ProductEntity::parseJson(jsonObject["productEntity"].toObject()));
    }
    if(product.getSmallPicAddress() != "")
    {
        QString filepath = product.getSmallPicAddress();
        int first = filepath.lastIndexOf ("\\");
        QString filename = filepath.right (filepath.length ()-first-1);
        QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
        httpProxy->get(GET_HOST()+GET_PRODUCT_SMALL_PATH()+filename);
        if(httpProxy->getReplyCode() == 200)
        {
            QByteArray avatarData = httpProxy->getReplyData();
            QImage img;
            img.loadFromData(avatarData);
            QPixmap pixmap(QPixmap::fromImage(img));
            ui->smallLabel->setScaledContents(true);
            ui->smallLabel->setAlignment(Qt::AlignCenter);
            ui->smallLabel->setPixmap(pixmap);
        }
    }

}

const ProductEntity &OrderListItem::getProduct() const
{
    return product;
}

void OrderListItem::setProduct(const ProductEntity &newProduct)
{
    product = newProduct;
}
