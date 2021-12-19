#include "freightrefreshwidget.h"
#include "ui_freightrefreshwidget.h"
#include "Service/HttpProxy.h"
#include "alertwindow.h"
#include <QJsonArray>

extern QString GET_HOST();
FreightRefreshWidget::FreightRefreshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FreightRefreshWidget)
{
    ui->setupUi(this);
}

FreightRefreshWidget::~FreightRefreshWidget()
{
    clear();
    delete ui;
}
void FreightRefreshWidget::setVector()
{
    clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/freight/");
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray freights = jsonObject["freightEntityList"].toArray();
        for (int i =0; i<freights.count(); ++i)
        {
            FreightListItem* item = new FreightListItem;
            connect(item, &FreightListItem::deleteRecord, this, &FreightRefreshWidget::on_deleteRecord);
            item->setFreightEntity(FreightEntity::parseJson(freights[i].toObject()));
            freightVector.push_back(item);
        }
    }

}
void FreightRefreshWidget::insert(FreightListItem* item)
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

void FreightRefreshWidget::clear()
{
    curIndex = 0;
    for (auto item : freightVector)
    {
        delete item;
    }
    freightVector.clear();
}
void FreightRefreshWidget::play()
{

    ui->listWidget->clear();
    setVector();
    for(curIndex = 0; curIndex < qMin(freightVector.length(), 5); ++curIndex)
    {
        insert(freightVector[curIndex]);
    }
    while(!ui->listWidget->isScrollVisible() && curIndex < freightVector.length())
    {
        insert(freightVector[curIndex++]);
    }
}
void FreightRefreshWidget::on_deleteRecord(bool signal)
{
    if(signal)
    {
        this->play();

    }
    else
    {
        AlertWindow* alertWin = new AlertWindow;
        alertWin->setMessage("删除失败");
        alertWin->show();
    }
}
void  FreightRefreshWidget::onScrollBarMoved( int  v)
{

}

void  FreightRefreshWidget::onReachedBottom()
{
    for  ( int i = 0; i < 2 && curIndex < freightVector.length(); i++, curIndex++)
    {
        insert(freightVector[curIndex]);
    }

}
