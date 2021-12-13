#include "categorylistitem.h"
#include "ui_categorylistitem.h"
#include "Service/HttpProxy.h"
extern QString GET_HOST();
CategoryListItem::CategoryListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryListItem)
{
    ui->setupUi(this);
}

CategoryListItem::~CategoryListItem()
{
    delete ui;
}

const CategoryEntity &CategoryListItem::getCategoryEntity() const
{
    return categoryEntity;
}

void CategoryListItem::setCategoryEntity(const CategoryEntity &newCategoryEntity)
{
    categoryEntity = newCategoryEntity;
    ui->label->setText("父类目id：" + QString::number(categoryEntity.getParentId()) + "\n"
                       + "id：" + QString::number(categoryEntity.getId()) + "\n"
                       + categoryEntity.getName());
}
void CategoryListItem::on_pushButton_clicked()
{
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/category/delete/id/" + QString::number(categoryEntity.getId()));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        emit deleteRecord(true);
        //
    }
    else
    {
        emit deleteRecord(false);
    }

}
