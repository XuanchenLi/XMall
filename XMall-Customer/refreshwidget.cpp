#include "refreshwidget.h"
#include "ui_refreshwidget.h"
#include "addresslistitem.h"
#include <QListWidget>
#include <QLabel>
RefreshWidget::RefreshWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RefreshWidget)
{
    ui->setupUi(this);
    //ui->listWidget->setResizeMode(QListView::Adjust);
    //ui->listWidget->setViewMode(QListView::IconMode);
    //ui->listWidget->setMovement(QListView::Static);
    AddressListItem* temp;
    //QVBoxLayout *m_layout = new QVBoxLayout(this);
    //m_layout->addWidget(ui->listWidget);
    //ui->listWidget->setResizeMode(QListWidget::Adjust);
    int  startRow = ui->listWidget->count();
    for ( int  i = startRow; i < startRow+5; i++)
    {
        QListWidgetItem* pItem = new QListWidgetItem();
         temp =  new  AddressListItem();
         ui->listWidget->addItem(pItem);
         temp->findChild<QLabel*>("cityLabel")->setText("TEST");
         temp->findChild<QLabel*>("nameLabel")->setText("TEST");
         temp->findChild<QLabel*>("detailLabel")->setText("TEST");
         temp->findChild<QLabel*>("phoneLabel")->setText("TEST");
         pItem->setSizeHint(temp->size());
         qDebug()<<temp->sizeHint();
         ui->listWidget->setItemWidget(pItem,temp);
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
     AddressListItem* temp;
     int  startRow = ui->listWidget->count();
     for  ( int  i = startRow; i < startRow+5; i++)
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
     }

}
