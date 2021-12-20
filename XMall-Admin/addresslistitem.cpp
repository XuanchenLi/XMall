#include "addresslistitem.h"
#include "ui_addresslistitem.h"
#include "Service/HttpProxy.h"
#include <QJsonObject>
extern QString GET_HOST();
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

void AddressListItem::on_pushButton_clicked()
{
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/user/address/delete/" + addressEntity.getUserPhone() + "/" + addressEntity.getUuid());
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

