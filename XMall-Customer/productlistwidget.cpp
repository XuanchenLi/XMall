#include "productlistwidget.h"
#include "ui_productlistwidget.h"
#include "Service/HttpProxy.h"
#include "productionwindow.h"
#include <QMouseEvent>
extern QString GET_HOST();
extern QString GET_PRODUCT_SMALL_PATH();
ProductListWidget::ProductListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductListWidget)
{
    ui->setupUi(this);
    raise();
    ui->textBrowser->setTextInteractionFlags ( Qt::NoTextInteraction );
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, "
                        "stop:0 rgb(52, 120, 221), stop:1 rgb(67,129,162));");
}

ProductListWidget::~ProductListWidget()
{
    delete ui;
}

const ProductEntity &ProductListWidget::getProductEntity() const
{
    return productEntity;
}

void ProductListWidget::setProductEntity(const ProductEntity &newProductEntity)
{
    productEntity = newProductEntity;
    ui->currentPriceLabel->setText("￥" + QString::number(productEntity.getCurrentPrice(), 'f', 2));
    if(productEntity.getCurrentPrice() != productEntity.getPrice())
    {
        ui->priceLabel->setText("￥" + QString::number(productEntity.getPrice(), 'f', 2));
    }
    ui->textBrowser->setText(productEntity.getName());
    if(productEntity.getSmallPicAddress() != "")
    {
        QString filepath = productEntity.getSmallPicAddress();
        int first = filepath.lastIndexOf ("\\");
        QString filename = filepath.right (filepath.length ()-first-1);
        QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
        httpProxy->get(GET_HOST()+GET_PRODUCT_SMALL_PATH()+filename);
        if(httpProxy->getReplyCode() == 200)
        {
            QByteArray avatarData = httpProxy->getReplyData();
            //qDebug()<<"avatarData";
            QImage img;
            img.loadFromData(avatarData);
            QPixmap pixmap(QPixmap::fromImage(img));

            ui->smallPic->setScaledContents(true);
            ui->smallPic->setAlignment(Qt::AlignCenter);
            ui->smallPic->setPixmap(pixmap);
        }
        else
        {
            QImage img;
            img.load (":/pics/icons/XMLOGO.png");
            QPixmap pixmap(QPixmap::fromImage(img));
            ui->smallPic->setPixmap(pixmap);
        }
    }
    else
    {
        QImage img;
        img.load (":/pics/icons/test.png");
        QPixmap pixmap(QPixmap::fromImage(img));
        ui->smallPic->setPixmap(pixmap);
    }
}
void ProductListWidget::mouseClicked()
{
    //处理代码
    //qDebug()<<"open detail page";
    ProductionWindow* productWin = new ProductionWindow;
    productWin->setPhone(phone);
    productWin->setProduct(productEntity);
    connect(productWin, &ProductionWindow::addCart, this, &ProductListWidget::on_addCart);
    connect(productWin, &ProductionWindow::order, this, &ProductListWidget::on_order);
    productWin->show();

}

void ProductListWidget::mousePressEvent(QMouseEvent *ev)
{

    mousePos = QPoint(ev->position().x(), ev->position().y());
}

void ProductListWidget::mouseReleaseEvent(QMouseEvent *ev)
{
    if(mousePos == QPoint(ev->position().x(), ev->position().y()))
        mouseClicked();
}

const QString &ProductListWidget::getPhone() const
{
    return phone;
}

void ProductListWidget::setPhone(const QString &newPhone)
{
    phone = newPhone;
}
void ProductListWidget::on_modified(ProductEntity entity)
{
    setProductEntity(entity);

}

void ProductListWidget::on_addCart()
{
    emit addCart();
}

void ProductListWidget::on_order(OrderItemEntity item)
{
    emit order(item);
}
