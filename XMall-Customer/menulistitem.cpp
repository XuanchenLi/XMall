#include "menulistitem.h"
#include "ui_menulistitem.h"
#include "alertwindow.h"
MenuListItem::MenuListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuListItem)
{
    ui->setupUi(this);
}

MenuListItem::~MenuListItem()
{
    delete ui;
}

const CategoryEntity &MenuListItem::getCategoryEntity() const
{
    return categoryEntity;
}

void MenuListItem::setCategoryEntity(const CategoryEntity &newCategoryEntity)
{
    categoryEntity = newCategoryEntity;
}
void MenuListItem::setText(QString text) const
{
    ui->pushButton->setText(text);
    ui->pushButton->setEnabled(true);
}

void MenuListItem::on_pushButton_clicked()
{
   //按类别检索
    AlertWindow *alertWin = new AlertWindow;
    alertWin->setMessage(categoryEntity.getName());
    alertWin->show();
}

