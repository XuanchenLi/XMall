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

const AddressEntity &AddressListItem::getAddressEntity() const
{
    return addressEntity;
}

void AddressListItem::setAddressEntity(const AddressEntity &newAddressEntity)
{
    addressEntity = newAddressEntity;
    ui->cityLabel->setText(addressEntity.getProvince() + "\n"
                           + addressEntity.getCity() + "\n"
                           + addressEntity.getRegion());
    ui->nameLabel->setText(addressEntity.getName());
    ui->phoneLabel->setText(addressEntity.getPhone());
    ui->detailLabel->setText(addressEntity.getDetail());
}
