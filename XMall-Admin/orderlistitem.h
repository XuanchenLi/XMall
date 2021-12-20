#ifndef ORDERLISTITEM_H
#define ORDERLISTITEM_H

#include <QWidget>
#include "Service/OrderItemEntity.h"
#include "Service/ProductEntity.h"
namespace Ui {
class OrderListItem;
}

class OrderListItem : public QWidget
{
    Q_OBJECT

public:
    explicit OrderListItem(QWidget *parent = nullptr);
    ~OrderListItem();

    const OrderItemEntity &getItem() const;
    void setItem(const OrderItemEntity &newItem);

    const ProductEntity &getProduct() const;
    void setProduct(const ProductEntity &newProduct);

private:
    Ui::OrderListItem *ui;
    OrderItemEntity item;
    ProductEntity product;
};

#endif // ORDERLISTITEM_H
