#ifndef ORDERLISTWIDGET_H
#define ORDERLISTWIDGET_H

#include <QWidget>
#include <QVector>
#include "orderlistitem.h"
namespace Ui {
class OrderListWidget;
}

class OrderListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderListWidget(QWidget *parent = nullptr);
    ~OrderListWidget();
    void setVector(QString orderSn);
    void insert(OrderListItem* item);
    void clear();
    void play(QString orderSn);
private:
    Ui::OrderListWidget *ui;
    QVector<OrderListItem*> itemVector;
    int curIndex = 0;
    QString orderSn;
private  slots:
     void  onScrollBarMoved( int );
     void  onReachedBottom();
};

#endif // ORDERLISTWIDGET_H
