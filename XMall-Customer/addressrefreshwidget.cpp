#include "addressrefreshwidget.h"
#include "ui_addressrefreshwidget.h"
#include "addresslistitem.h"
#include "Service/HttpProxy.h"
#include "alertwindow.h"
#include <QListWidget>
#include <QJsonArray>
#include <QLabel>
extern QString GET_HOST();
AddressRefreshWidget::AddressRefreshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddressRefreshWidget)
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(msliderChanged(int)),  this , SLOT(onScrollBarMoved(int)));
    connect(ui->listWidget, SIGNAL(reachedBottom()),  this , SLOT(onReachedBottom()));

}

AddressRefreshWidget::~AddressRefreshWidget()
{
    delete ui;
}
void  AddressRefreshWidget::onScrollBarMoved( int  v)
{

}

void  AddressRefreshWidget::onReachedBottom()
{

     for  ( int i = 0; i < 2 && curIndex < addressVector.length(); i++, curIndex++)
     {
         insertAddress(addressVector[curIndex]);
     }

}

void AddressRefreshWidget::setAddressVector(QString phone)
{
    clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/user/address/" + phone);
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray addresses = jsonObject["addressList"].toArray();
        for (int i =0; i<addresses.count(); ++i)
        {
            AddressListItem* item = new AddressListItem;
            connect(item, &AddressListItem::deleteRecord, this, &AddressRefreshWidget::on_deleteRecord);
            item->setAddressEntity(AddressEntity::parseJson(addresses[i].toObject()));
            addressVector.push_back(item);
        }
    }

}
void AddressRefreshWidget::insertAddress(AddressListItem* addressItem)
{
    if (addressItem == nullptr)
    {
        qDebug()<<"空指针";
        return;
    }
    QListWidgetItem* pItem = new QListWidgetItem();
    ui->listWidget->addItem(pItem);
    pItem->setSizeHint(addressItem->size());
    ui->listWidget->setItemWidget(pItem,addressItem);

}

void AddressRefreshWidget::clear()
{
    curIndex = 0;
    addressVector.clear();
}
void AddressRefreshWidget::play(QString phone)
{
    this->phone = phone;
    ui->listWidget->clear();
    setAddressVector(phone);
    for(curIndex = 0; curIndex < qMin(addressVector.length(), 5); ++curIndex)
    {
        insertAddress(addressVector[curIndex]);
    }
    while(!ui->listWidget->isScrollVisible() && curIndex < addressVector.length())
    {
        insertAddress(addressVector[curIndex++]);
    }
}
void AddressRefreshWidget::on_deleteRecord(bool signal)
{
    if(signal)
    {
        this->play(phone);
    }
    else
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("删除失败");
        alertWin->show();
    }
}
