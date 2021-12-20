#include "productrefreshwidget.h"
#include "ui_productrefreshwidget.h"
#include "Service/HttpProxy.h"
#include "Service/ProductEntity.h"
#include "productlistwidget.h"
#include <QJsonArray>
#include <QListView>
extern QString GET_HOST();
ProductRefreshWidget::ProductRefreshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductRefreshWidget)
{
    ui->setupUi(this);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setResizeMode(QListView::Adjust);
    ui->listWidget->setMovement(QListView::Static);
    connect(ui->listWidget, SIGNAL(msliderChanged(int)),  this , SLOT(onScrollBarMoved(int)));
    connect(ui->listWidget, SIGNAL(reachedBottom()),  this , SLOT(onReachedBottom()));
}

ProductRefreshWidget::~ProductRefreshWidget()
{
    clear();
    delete ui;
}
void ProductRefreshWidget::setVector(int status)
{
    clear(status);
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/product/status/" + QString::number(status));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray products = jsonObject["productEntityList"].toArray();
        for (int i =0; i<products.count(); ++i)
        {
            ProductListWidget* item = new ProductListWidget;
            item->setPhone(phone);
            connect(item, &ProductListWidget::addCart, this, &ProductRefreshWidget::on_addCart);
            connect(item, &ProductListWidget::order, this, &ProductRefreshWidget::on_order);
            item->setProductEntity(ProductEntity::parseJson(products[i].toObject()));
            productVectors[status].push_back(item);
        }
    }

}
void ProductRefreshWidget::on_addCart()
{
    if(father != nullptr)
        father->initCart(phone);
}
void ProductRefreshWidget::setVector()
{
    clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    for (int j = 0; j < STATUS_NUMBER; ++j){
        httpProxy->get(GET_HOST() + "/product/status/" + QString::number(j));
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() == "SUCCESS")
        {
         QJsonArray products = jsonObject["productEntityList"].toArray();
            for (int i =0; i<products.count(); ++i)
            {
                ProductListWidget* item = new ProductListWidget;
                item->setPhone(phone);
                connect(item, &ProductListWidget::addCart, this, &ProductRefreshWidget::on_addCart);
                connect(item, &ProductListWidget::order, this, &ProductRefreshWidget::on_order);
                item->setProductEntity(ProductEntity::parseJson(products[i].toObject()));
                productVectors[STATUS_NUMBER].push_back(item);
            }
        }
    }

}



void ProductRefreshWidget::insert(ProductListWidget* item)
{
    if (item == nullptr)
    {
        qDebug()<<"空指针";
        return;
    }
    QListWidgetItem* pItem = new QListWidgetItem();
    ui->listWidget->addItem(pItem);
    pItem->setSizeHint(item->size());
    ui->listWidget->setItemWidget(pItem,item);

}

void ProductRefreshWidget::clear(int status)
{
    curIndex = 0;
    ui->listWidget->clear();
    productVectors[status].clear();
    productVectors[status].squeeze();
}
void ProductRefreshWidget::clear()
{
    curIndex = 0;
    ui->listWidget->clear();
    productVectors[STATUS_NUMBER].clear();
    productVectors[STATUS_NUMBER].squeeze();
}
void ProductRefreshWidget::play(int status)
{
    curCategory.setId(0);
    if(status == STATUS_NUMBER) return;
    curStatus = status;
    ui->listWidget->clear();
    setVector(status);
    for(curIndex = 0; curIndex < productVectors[status].length(); ++curIndex)
    {
        insert(productVectors[status][curIndex]);
    }

}
void ProductRefreshWidget::play()
{
    curCategory.setId(0);
    curStatus = STATUS_NUMBER;
    ui->listWidget->clear();
    setVector();
    for(curIndex = 0; curIndex < productVectors[STATUS_NUMBER].length(); ++curIndex)
    {
        insert(productVectors[STATUS_NUMBER][curIndex]);
    }
//        while(!ui->listWidget->isScrollVisible() && curIndex < productVectors[STATUS_NUMBER].length())
//    {
//        insert(productVectors[STATUS_NUMBER][curIndex++]);
//    }

}

void ProductRefreshWidget::play(CategoryEntity category, int status = 1)
{
    curIndex = 0;
    curCategory = category;
    curStatus = status;
    ui->listWidget->clear();
    setVector(status);
    for(curIndex = 0; curIndex < productVectors[status].length(); ++curIndex)
    {
        if(productVectors[status][curIndex]->getProductEntity().getCategoryId() == category.getId())
            insert(productVectors[status][curIndex]);

    }
//        while(!ui->listWidget->isScrollVisible())
//    {
//        if(curIndex >= productVectors[status].length())
//            curIndex = 0;
//        if(productVectors[status][curIndex]->getProductEntity().getCategoryId() == category.getId())
//            insert(productVectors[status][curIndex++]);

//    }

}

const QString &ProductRefreshWidget::getPhone() const
{
    return phone;
}

void ProductRefreshWidget::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

void ProductRefreshWidget::setFather(MainWindow *newFather)
{
    father = newFather;
}

void  ProductRefreshWidget::onScrollBarMoved( int  v)
{

}

void  ProductRefreshWidget::onReachedBottom()
{
    if(curCategory.getId() == 0)
    {
        for  ( int i = 0; i < 10 && curIndex < productVectors[curStatus].length(); i++, curIndex++)
        {
            insert(productVectors[curStatus][curIndex]);
        }
//        if (curIndex >= productVectors[curStatus].length() && curStatus != STATUS_NUMBER)
//        {
//            QVector<ProductListWidget*> next;
//            QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
//            httpProxy->get(GET_HOST() + "/product/random/ten");
//            QJsonObject jsonObject = httpProxy->getJsonObject();
//            if(jsonObject["statusCode"].toString() == "SUCCESS")
//            {
//                QJsonArray products = jsonObject["productEntityList"].toArray();
//                for (int i =0; i<products.count(); ++i)
//                {
//                    ProductListWidget* item = new ProductListWidget;
//                    //connect(item, &ProductListWidget::deleteRecord, this, &ProductRefreshWidget::on_deleteRecord);
//                    item->setProductEntity(ProductEntity::parseJson(products[i].toObject()));
//                    next.push_back(item);
//                }
//            }
//            for  ( int i = 0; i < next.length(); i++)
//            {
//                insert(next[i]);
//            }
//        }
    }
    else
    {
        if(curIndex >= productVectors[curStatus].length())
            curIndex = 0;
        for  ( int count = 0; count < 10 && curIndex < productVectors[curStatus].length();  curIndex++)
        {
            if(productVectors[curStatus][curIndex]->getProductEntity().getCategoryId() == curCategory.getId())
            {
                insert(productVectors[curStatus][curIndex]);
                count++;
            }
        }
    }

}

void ProductRefreshWidget::on_order(OrderItemEntity item)
{

    emit order(item);
}
