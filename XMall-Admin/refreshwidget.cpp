#include "refreshwidget.h"
#include "ui_refreshwidget.h"
#include <QListWidget>
#include <QLabel>
RefreshWidget::RefreshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RefreshWidget)
{
    ui->setupUi(this);
    int  startRow = ui->listWidget->count();
    for ( int  i = startRow; i < startRow+5; i++)
    {
        QListWidgetItem* pItem = new QListWidgetItem();
         ui->listWidget->addItem(pItem);
    }

    connect(ui->listWidget, SIGNAL(msliderChanged(int)),  this , SLOT(onScrollBarMoved(int)));
    connect(ui->listWidget, SIGNAL(reachedBottom()),  this , SLOT(onReachedBottom()));
}

RefreshWidget::~RefreshWidget()
{
    delete ui;
}
void  RefreshWidget::onScrollBarMoved( int  v)
{

}

void  RefreshWidget::onReachedBottom()
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
