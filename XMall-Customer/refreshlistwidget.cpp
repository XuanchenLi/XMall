#include "refreshlistwidget.h"
#include "ui_refreshlistwidget.h"
#include <QScrollBar>
#include <QListWidget>
#include <QVBoxLayout>
RefreshListWidget::RefreshListWidget(QWidget *parent) :
    QListWidget(parent)
{

    scrollBar = verticalScrollBar();
    connect(scrollBar, SIGNAL(valueChanged(int)),  this , SLOT(onSliderChanged(int)));

    //vLayout->addWidget(this);
}

RefreshListWidget::~RefreshListWidget()
{

}
void  RefreshListWidget::onSliderChanged(int  p)
{

     if  (p == scrollBar->maximum())
     {
         emit reachedBottom();  // 1
     }
     emit msliderChanged(p);   // 2
}
