#include "categoryrefreshwidget.h"
#include "ui_categoryrefreshwidget.h"
#include "Service/HttpProxy.h"
#include "Service/CategoryEntity.h"
#include "alertwindow.h"
#include <QJsonArray>

extern QString GET_HOST();
CategoryRefreshWidget::CategoryRefreshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryRefreshWidget)
{
    ui->setupUi(this);
    for(int i =1; i<=5;++i){
    QListWidgetItem* pItem = new QListWidgetItem();
    ui->listWidget->addItem(pItem);
    }
    connect(ui->listWidget, SIGNAL(msliderChanged(int)),  this , SLOT(onScrollBarMoved(int)));
    connect(ui->listWidget, SIGNAL(reachedBottom()),  this , SLOT(onReachedBottom()));
}

CategoryRefreshWidget::~CategoryRefreshWidget()
{
    delete ui;
}

void  CategoryRefreshWidget::onScrollBarMoved( int  v)
{

}

void  CategoryRefreshWidget::onReachedBottom()
{
    for  ( int i = 0; i < 2 && curIndex < categoryVector.length(); i++, curIndex++)
    {
        insertCategory(categoryVector[curIndex]);
    }

}
void CategoryRefreshWidget::setCategoryVector(int level)
{
    clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/category/level/" + QString::number(level));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray categories = jsonObject["categoryEntityList"].toArray();
        for (int i =0; i<categories.count(); ++i)
        {
            CategoryListItem* item = new CategoryListItem;
            connect(item, &CategoryListItem::deleteRecord, this, &CategoryRefreshWidget::on_deleteRecord);
            item->setCategoryEntity(CategoryEntity::parseJson(categories[i].toObject()));
            categoryVector.push_back(item);
        }
    }

}
void CategoryRefreshWidget::insertCategory(CategoryListItem* categoryItem)
{
    if (categoryItem == nullptr)
    {
        qDebug()<<"空指针";
        return;
    }
    //qDebug()<<categoryItem->getCategoryEntity().getId();
    QListWidgetItem* pItem = new QListWidgetItem();
    ui->listWidget->addItem(pItem);
    pItem->setSizeHint(categoryItem->size());
    ui->listWidget->setItemWidget(pItem,categoryItem);

}

void CategoryRefreshWidget::clear()
{
    curIndex = 0;
    categoryVector.clear();
}
void CategoryRefreshWidget::play(int level)
{

    ui->listWidget->clear();
    setCategoryVector(level);
    for(curIndex = 0; curIndex < qMin(categoryVector.length(), 5); ++curIndex)
    {
        insertCategory(categoryVector[curIndex]);
    }
    while(!ui->listWidget->isScrollVisible() && curIndex < categoryVector.length())
    {
        insertCategory(categoryVector[curIndex++]);
    }
}

int CategoryRefreshWidget::getLevel() const
{
    return level;
}

void CategoryRefreshWidget::setLevel(int newLevel)
{
    level = newLevel;
}

const QVector<CategoryListItem *> &CategoryRefreshWidget::getCategoryVector() const
{
    return categoryVector;
}
void CategoryRefreshWidget::on_deleteRecord(bool signal)
{
    if(signal)
    {
        this->play(level);
        emit refreshBox();
    }
    else
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("删除失败");
        alertWin->show();
    }
}
