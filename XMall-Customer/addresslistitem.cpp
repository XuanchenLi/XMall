#include "addresslistitem.h"
#include "ui_addresslistitem.h"

AddressListItem::AddressListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddressListItem)
{
    ui->setupUi(this);

}

AddressListItem::~AddressListItem()
{
    delete ui;
}
