#include "adminproductwindow.h"
#include "ui_adminproductwindow.h"
#include "Service/HttpProxy.h"
#include "alertwindow.h"
#include <QLabel>
#include <QJsonArray>
#include <QFileDialog>
extern QString GET_HOST();
extern long GET_ID(QString);
AdminProductWindow::AdminProductWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminProductWindow)
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
    //
    initCategory();
    initFreight();
}

AdminProductWindow::~AdminProductWindow()
{
    delete ui;
}

const ProductEntity &AdminProductWindow::getProduct() const
{
    return product;
}

void AdminProductWindow::setProduct(const ProductEntity &newProduct)
{
    product = newProduct;
    ui->idLabel->setText(QString::number(product.getId()));
    ui->nameLineEdit->setText(product.getName());
    ui->unitLineEdit->setText(product.getUnit());
    ui->priceDoubleSpinBox->setValue(product.getPrice());
    ui->currentPriceDoubleSpinBox->setValue(product.getCurrentPrice());
    for(int i = 0; i<freightVector.length(); ++i)
    {
        if(freightVector[i].getId() == product.getFreightTemplateId())
        {
            ui->freightComboBox->setCurrentIndex(i);
            break;
        }
    }
    CategoryEntity level2;
    for(int i = 0; i < categoryLevel2.length(); ++i)
    {
        if(categoryLevel2[i].getId() == product.getCategoryId())
        {
            level2 = categoryLevel2[i];
            break;
        }
    }
    for(int i = 0; i < ui->category_1ComboBox->count(); ++i)
    {
        if(GET_ID(ui->category_1ComboBox->itemText(i)) == level2.getParentId())
        {
            ui->category_1ComboBox->setCurrentIndex(i);
            emit ui->category_1ComboBox->currentIndexChanged(i);
            break;
        }
    }

    for(int i = 0; i<categoryLevel2.length(); ++i)
    {
        if(categoryLevel2[i].getId() == level2.getId())
        {
            ui->category_2ComboBox->setCurrentIndex(i);
            break;
        }
    }
    ui->introductionTextEdit->setText(product.getIntroduction());
    ui->limitationSpinBox->setValue(product.getLimitation());
    ui->storageSpinBox->setValue(product.getStorage());
    ui->saleLabel->setText(QString::number(product.getSale()));
    ui->statusSpinBox->setValue(product.getStatus());
}
void AdminProductWindow::initCategory()
{
    categoryLevel1.clear();
    categoryLevel2.clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/category/level/1");
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray categories = jsonObject["categoryEntityList"].toArray();
        for (int i =0; i<categories.count(); ++i)
        {
            categoryLevel1.push_back(CategoryEntity::parseJson(categories[i].toObject()));
        }
    }
    //
    httpProxy->get(GET_HOST() + "/category/level/2");
    QJsonObject jsonObject2 = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray categories = jsonObject2["categoryEntityList"].toArray();
        for (int i =0; i<categories.count(); ++i)
        {
            categoryLevel2.push_back(CategoryEntity::parseJson(categories[i].toObject()));
        }
    }
    ui->category_1ComboBox->clear();
    for (int i = 0;i < categoryLevel1.length(); ++i)
    {
        ui->category_1ComboBox->addItem(QString::number(categoryLevel1[i].getId())
                                      +": "
                                      + categoryLevel1[i].getName());
    }
    ui->category_2ComboBox->clear();

}
void AdminProductWindow::initFreight()
{
    freightVector.clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/freight/");
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray freights = jsonObject["freightEntityList"].toArray();
        for (int i =0; i<freights.count(); ++i)
        {
            freightVector.push_back(FreightEntity::parseJson(freights[i].toObject()));
        }
    }
    ui->freightComboBox->clear();
    for (int i = 0;i < freightVector.length(); ++i)
    {
        ui->freightComboBox->addItem(QString::number(freightVector[i].getId()) + ":￥ "
                                     + QString::number(freightVector[i].getPrice(),
                                                       'f', 2));
    }
}

void AdminProductWindow::on_bigPicPushButton_clicked()
{
    if(status == NEW_PRODUCT)
    {
        on_savePushButton_clicked();
        status = UPDATE_PRODUCT;
    }
    if(product.getId() == 0) return;
    ui->bigPicPushButton->setEnabled(false);
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择一张图片"), "C:", tr("Image Files (*.png *.jpg *.bmp *jpeg)"));
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->uploadPicture(GET_HOST() + "/product/id/" + QString::number(product.getId()) + "/uploadBigPic", fileName);
    if(httpProxy->getJsonObject()["statusCode"].toString() == "SUCCESS")
    {
        //
        ProductEntity newProduct = ProductEntity::parseJson(httpProxy->getJsonObject()["productEntity"].toObject());
        product = newProduct;
        emit modified(product);
    }
    else
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
        ui->bigPicPushButton->setEnabled(true);
        return ;
    }
    ui->bigPicPushButton->setEnabled(true);
}


void AdminProductWindow::on_smallPicPushButton_clicked()
{
    if(status == NEW_PRODUCT)
    {
        on_savePushButton_clicked();
        status = UPDATE_PRODUCT;
    }
    ui->smallPicPushButton->setEnabled(false);
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择一张图片"), "C:", tr("Image Files (*.png *.jpg *.bmp *jpeg)"));
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->uploadPicture(GET_HOST() + "/product/id/" + QString::number(product.getId()) + "/uploadSmallPic", fileName);
    if(httpProxy->getJsonObject()["statusCode"].toString() == "SUCCESS")
    {
        //
        ProductEntity newProduct = ProductEntity::parseJson(httpProxy->getJsonObject()["productEntity"].toObject());
        product = newProduct;
        emit modified(product);
    }
    else
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
        ui->smallPicPushButton->setEnabled(true);
        return ;
    }
    ui->smallPicPushButton->setEnabled(true);
}


void AdminProductWindow::on_savePushButton_clicked()
{
    ui->savePushButton->setEnabled(false);
     ProductEntity newProduct = product;
     newProduct.setName(ui->nameLineEdit->text());
     newProduct.setUnit(ui->unitLineEdit->text());
     newProduct.setCategoryId(GET_ID(ui->category_2ComboBox->currentText()));
     newProduct.setPrice(ui->priceDoubleSpinBox->value());
     newProduct.setCurrentPrice(ui->currentPriceDoubleSpinBox->value());
     newProduct.setFreightTemplateId(GET_ID(ui->freightComboBox->currentText()));
     newProduct.setIntroduction(ui->introductionTextEdit->toPlainText());
     newProduct.setLimitation(ui->limitationSpinBox->value());
     newProduct.setStorage(ui->storageSpinBox->value());
     newProduct.setStatus(ui->statusSpinBox->value());
     QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
     if(status == UPDATE_PRODUCT)
     {
         httpProxy->post(GET_HOST() + "/product/updateInfo" ,newProduct.getQByteArrayForm());

         if(httpProxy->getJsonObject()["statusCode"].toString() == "SUCCESS")
         {
             AlertWindow *alertWin = new AlertWindow;
             alertWin->setMessage("保存成功");
             alertWin->show();
             product = newProduct;
             emit modified(product);
         }
         else
         {
             AlertWindow *alertWin = new AlertWindow;
             alertWin->setMessage("网络异常");
             alertWin->show();
             ui->savePushButton->setEnabled(true);
             return;
         }
     }
     else if(status == NEW_PRODUCT)
     {
         httpProxy->post(GET_HOST() + "/product/add" ,newProduct.getQByteArrayForm());
         if(httpProxy->getJsonObject()["statusCode"].toString() == "SUCCESS")
         {
             AlertWindow *alertWin = new AlertWindow;
             alertWin->setMessage("添加成功");
             alertWin->show();
             product = ProductEntity::parseJson(httpProxy->getJsonObject()["productEntity"].toObject());
         }
         else
         {
             AlertWindow *alertWin = new AlertWindow;
             alertWin->setMessage("网络异常");
             alertWin->show();
             ui->savePushButton->setEnabled(true);
             return;
         }
     }
     ui->savePushButton->setEnabled(true);
}

int AdminProductWindow::getStatus() const
{
    return status;
}

void AdminProductWindow::setStatus(int newStatus)
{
    status = newStatus;
}


void AdminProductWindow::on_category_1ComboBox_currentIndexChanged(int index)
{
    ui->category_2ComboBox->clear();
    int parent = GET_ID(ui->category_1ComboBox->currentText());
    for (int i = 0;i < categoryLevel2.length(); ++i)
    {
        if(categoryLevel2[i].getParentId() == parent)
        {
            ui->category_2ComboBox->addItem(QString::number(categoryLevel2[i].getId())
                                            +": "
                                            + categoryLevel2[i].getName());
        }
    }
}

