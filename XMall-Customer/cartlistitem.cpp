#include "cartlistitem.h"
#include "ui_cartlistitem.h"
#include "Service/HttpProxy.h"
#include "alertwindow.h"
#include <QJsonObject>
extern QString GET_HOST();
extern QString GET_PRODUCT_SMALL_PATH();
CartListItem::CartListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CartListItem)
{
    ui->setupUi(this);
}

CartListItem::~CartListItem()
{
    delete ui;
}

const CartEntity &CartListItem::getCartEntity() const
{
    return cartEntity;
}

void CartListItem::setCartEntity(const CartEntity &newCartEntity)
{
    cartEntity = newCartEntity;
    //qDebug()<<"bugg2"<<cartEntity.getCount();
    if(!cartEntity.getDel())
    {
        QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
        //qDebug()<<"bugg1"<<cartEntity.getCount();
        httpProxy->get(GET_HOST() + "/product/id/" + QString::number(cartEntity.getProduct_id()));
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() == "SUCCESS")
        {
            ProductEntity item =  ProductEntity::parseJson(jsonObject["productEntity"].toObject());
            product = item;
            if(item.getStatus() != item.ON_SALE)
            {
                setInvalid();
                return ;
            }
           // qDebug()<<"bugg2"<<product.getLimitation();
            if (cartEntity.getCount() <= product.getLimitation() || product.getLimitation() == -1)
            {
                ui->spinBox->setValue(cartEntity.getCount());
                if(cartEntity.getChecked())
                {ui->checkBox->setChecked(true);
                    //qDebug()<<"666666";
                }
                //qDebug()<<"bugg2"<<cartEntity.getCount();
                updateCount();
                setProduct(item);
            }
            else
            {
                cartEntity.setCount(product.getLimitation());
                ui->spinBox->setValue(cartEntity.getCount());
                //更新
                bool signal = updateCount();
                if(signal)
                {
                    setProduct(item);
                }
                else
                {
                    setInvalid();
                    return ;
                }

            }
        }
        else
        {
            setInvalid();
            return ;
        }

    }
    else
    {
        setInvalid();
        return ;
    }

}

const ProductEntity &CartListItem::getProduct() const
{
    return product;
}

void CartListItem::setProduct(const ProductEntity &newProduct)
{
    product = newProduct;
    ui->nameLabel->setText(product.getName());
    ui->priceLabel->setText("￥ " + QString::number(product.getPrice(),'f',2));
    ui->currentPriceLabel->setText("￥ " + QString::number(product.getCurrentPrice(),'f',2));
    setTotPrice(ui->spinBox->value() * product.getCurrentPrice());
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
void CartListItem::setTotPrice(double price)
{
    ui->totLabel->setText("￥ " + QString::number(price,'f',2));
}

void CartListItem::on_pushButton_clicked()
{
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/cart/delete/phone/" + cartEntity.getUserPhone()
                   + "/id/" + QString::number(cartEntity.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        emit deleteRecord(true);
    }
}

void CartListItem::setInvalid()
{
    ui->checkBox->setChecked(false);
    ui->checkBox->setCheckable(false);
    ui->spinBox->setReadOnly(true);
    QWidget* MaskLayer = nullptr;

    MaskLayer = new QWidget(this);
    MaskLayer->setStyleSheet("background-color: rgba(0, 0, 0, 180);");//设置颜色及不透明度
    MaskLayer->setFixedSize(this->size());//设置窗口大小
    MaskLayer->setVisible(false);//初始状态下隐藏，待需要显示时使用m_pMaskLayer->setVisible(true);
    this->stackUnder(MaskLayer);//其中pWrapper为当前窗口的QWidget
    MaskLayer->stackUnder(ui->pushButton);
}
bool CartListItem::updateCount()
{
    QByteArray postMsg = QJsonDocument(cartEntity.getJsonForm()).toJson();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    //qDebug()<<"bugg1"<<cartEntity.getCount();
    httpProxy->post(GET_HOST() + "/cart/updateCount", postMsg);
    //qDebug()<<"bugg2"<<cartEntity.getCount();
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        return true;
    }
    else
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("与服务器失去连接");
        alertWin->show();
        return false;
    }
}
bool CartListItem::isChecked() const
{
    return ui->checkBox->isChecked();
}
int CartListItem::getSpinBoxCount()
{
    return ui->spinBox->value();
}

void CartListItem::on_spinBox_valueChanged(int arg1)
{
    CartEntity newCart = cartEntity;
    //qDebug()<<arg1;
    newCart.setCount(ui->spinBox->value());
    setCartEntity(newCart);
    emit itemChanged();
}

void CartListItem::check()
{
    ui->checkBox->setChecked(true);
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/cart/check/phone/" + cartEntity.getUserPhone() + "/id/" +QString::number(cartEntity.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] != "SUCCESS")
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("与服务器失去连接");
        alertWin->show();
    }
}

void CartListItem::on_checkBox_stateChanged(int arg1)
{
    //qDebug()<<arg1;
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    if (ui->checkBox->isChecked())
    {
        //qDebug()<<"bug"<<cartEntity.getCount();
        httpProxy->get(GET_HOST() + "/cart/check/phone/" + cartEntity.getUserPhone() + "/id/" +QString::number(cartEntity.getId()));
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"] != "SUCCESS")
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("与服务器失去连接");
            alertWin->show();
        }
    }
    else
    {
        httpProxy->get(GET_HOST() + "/cart/disCheck/phone/" + cartEntity.getUserPhone() + "/id/" +QString::number(cartEntity.getId()));
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"] != "SUCCESS")
        {
            AlertWindow* alertWin = new AlertWindow;
            alertWin->setMessage("与服务器失去连接");
            alertWin->show();
        }
    }
    emit itemChanged();
}

