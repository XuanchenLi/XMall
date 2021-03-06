#ifndef CARTREFRESHWIDGET_H
#define CARTREFRESHWIDGET_H
#include "cartlistitem.h"
#include "Service/CartEntity.h"
#include "Service/OrderItemEntity.h"
#include <QWidget>
#include <QVector>

namespace Ui {
class CartRefreshWidget;
}

class CartRefreshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CartRefreshWidget(QWidget *parent = nullptr);
    ~CartRefreshWidget();
    void setCartVector(QString phone);
    void insertCart(CartListItem* item);
    void clear();
    void play(QString phone);
    double calculate();
    void checkAll();
    QVector<CartEntity> getSelectedItemsCartEntity();
    QVector<ProductEntity> getSelectedItemsProductEntity();
    void delCart(QVector<OrderItemEntity>);
private:
    Ui::CartRefreshWidget *ui;
    QVector<CartListItem*> cartVector;
    int curIndex = 0;
    QString phone;
private  slots:
     void  onScrollBarMoved( int );
     void  onReachedBottom();
     void  on_deleteRecord(bool);
     void on_itemChanged();
signals:
     void finishCalculate(double);
};

#endif // CARTREFRESHWIDGET_H
