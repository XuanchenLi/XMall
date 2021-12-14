#include "freightlistitem.h"
#include "ui_freightlistitem.h"
#include "Service/HttpProxy.h"
extern QString GET_HOST();
FreightListItem::FreightListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreightListItem)
{
    ui->setupUi(this);
}

FreightListItem::~FreightListItem()
{
    delete ui;
}

const FreightEntity &FreightListItem::getFreightEntity() const
{
    return freightEntity;
}

void FreightListItem::setFreightEntity(const FreightEntity &newFreightEntity)
{
    freightEntity = newFreightEntity;
    ui->label->setText(QString::number(newFreightEntity.getPrice(), 'f', 2) + "￥");

}

void FreightListItem::on_pushButton_clicked()
{
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/freight/delete/id/" + QString::number(freightEntity.getId()));
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


