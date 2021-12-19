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
    clear();
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
    for  (auto item : addressVector)
    {
        delete item;
    }
    addressVector.clear();
}
void AddressRefreshWidget::play(QString phone)
{
    this->phone = phone;
    ui->listWidget->clear();
    setAddressVector(phone);
    for(curIndex = 0; curIndex < addressVector.length(); ++curIndex)
    {
        insertAddress(addressVector[curIndex]);
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
QString AddressRefreshWidget::selectedAddress()
{
    if (ui->listWidget->selectedItems().isEmpty()) return "";
    QWidget* widget = ui->listWidget->itemWidget(ui->listWidget->selectedItems()[0]);
    QString context = "";
    QString name = widget->findChild<QLabel*>("nameLabel")->text();
    QString city = widget->findChild<QLabel*>("cityLabel")->text();
    QString phone = widget->findChild<QLabel*>("phoneLabel")->text();
    QString detail = widget->findChild<QLabel*>("detailLabel")->text();
    context = QString("收货人：" + name + " "
                      + "手机号码：" + phone + " "
                      + "收货地址："  + city + " " + detail);
    return context;
}
