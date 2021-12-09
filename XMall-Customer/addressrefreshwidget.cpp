#include "addressrefreshwidget.h"
#include "ui_addressrefreshwidget.h"
#include "addresslistitem.h"
#include <QListWidget>
#include <QLabel>
AddressRefreshWidget::AddressRefreshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddressRefreshWidget)
{
    ui->setupUi(this);
    AddressListItem* temp;
    int  startRow = ui->listWidget->count();
    for ( int  i = startRow; i < startRow+1; i++)
    {
        QListWidgetItem* pItem = new QListWidgetItem();
         temp =  new  AddressListItem();
         ui->listWidget->addItem(pItem);
         temp->findChild<QLabel*>("cityLabel")->setText("TEST");
         temp->findChild<QLabel*>("nameLabel")->setText("TEST");
         temp->findChild<QLabel*>("detailLabel")->setText("TEST");
         temp->findChild<QLabel*>("phoneLabel")->setText("TEST");
         pItem->setSizeHint(temp->size());
         //qDebug()<<temp->sizeHint();
         ui->listWidget->setItemWidget(pItem,temp);
    }
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
     /*AddressListItem* temp;
     int  startRow = ui->listWidget->count();
     */
     /*for  ( int  i = startRow; i < startRow+5; i++)
     {
         QListWidgetItem* pItem = new QListWidgetItem();
          temp =  new  AddressListItem();
          ui->listWidget->addItem(pItem);
          temp->findChild<QLabel*>("cityLabel")->setText("TEST");
          temp->findChild<QLabel*>("nameLabel")->setText("TEST");
          temp->findChild<QLabel*>("detailLabel")->setText("TEST");
          temp->findChild<QLabel*>("phoneLabel")->setText("TEST");
          pItem->setSizeHint(temp->size());
          ui->listWidget->setItemWidget(pItem,temp);
     }*/

}
