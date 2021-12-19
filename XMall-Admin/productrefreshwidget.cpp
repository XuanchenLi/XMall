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
            //connect(item, &ProductListWidget::deleteRecord, this, &ProductRefreshWidget::on_deleteRecord);
            item->setProductEntity(ProductEntity::parseJson(products[i].toObject()));
            productVectors[status].push_back(item);
        }
    }

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
                //connect(item, &ProductListWidget::deleteRecord, this, &ProductRefreshWidget::on_deleteRecord);
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
    for (auto item : productVectors[status])
    {
        delete item;
    }
    productVectors[status].clear();
}
void ProductRefreshWidget::clear()
{
    curIndex = 0;
    for (auto vector : productVectors)
    {
        for (auto item : vector)
        {
            delete item;
        }
    }
    productVectors[STATUS_NUMBER].clear();
}
void ProductRefreshWidget::play(int status)
{
    if(status == STATUS_NUMBER) return;
    curStatus = status;
    ui->listWidget->clear();
    setVector(status);
    for(curIndex = 0; curIndex < qMin(productVectors[status].length(), 5); ++curIndex)
    {
        insert(productVectors[status][curIndex]);
    }
        while(!ui->listWidget->isScrollVisible() && curIndex < productVectors[status].length())
    {
        insert(productVectors[status][curIndex++]);
    }

}
void ProductRefreshWidget::play()
{
    curStatus = STATUS_NUMBER;
    ui->listWidget->clear();
    setVector();
    for(curIndex = 0; curIndex < qMin(productVectors[STATUS_NUMBER].length(), 10); ++curIndex)
    {
        insert(productVectors[STATUS_NUMBER][curIndex]);
    }
        while(!ui->listWidget->isScrollVisible() && curIndex < productVectors[STATUS_NUMBER].length())
    {
        insert(productVectors[STATUS_NUMBER][curIndex++]);
    }

}
void  ProductRefreshWidget::onScrollBarMoved( int  v)
{

}

void  ProductRefreshWidget::onReachedBottom()
{

    for  ( int i = 0; i < 10 && curIndex < productVectors[curStatus].length(); i++, curIndex++)
    {
        insert(productVectors[curStatus][curIndex]);
    }
    if (curIndex >= productVectors[curStatus].length() && curStatus != STATUS_NUMBER)
    {
        QVector<ProductListWidget*> next;
        QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
        httpProxy->get(GET_HOST() + "/product/random/" + QString::number(10));
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() == "SUCCESS")
        {
             QJsonArray products = jsonObject["productEntityList"].toArray();
             for (int i =0; i<products.count(); ++i)
             {
                 ProductListWidget* item = new ProductListWidget;
                 //connect(item, &ProductListWidget::deleteRecord, this, &ProductRefreshWidget::on_deleteRecord);
                 item->setProductEntity(ProductEntity::parseJson(products[i].toObject()));
                 next.push_back(item);
             }
        }
        for  ( int i = 0; i < next.length(); i++, curIndex++)
        {
            insert(next[i]);
        }
    }

}
