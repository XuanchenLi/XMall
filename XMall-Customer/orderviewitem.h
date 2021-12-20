#ifndef ORDERVIEWITEM_H
#define ORDERVIEWITEM_H

#include <QWidget>
#include "Service/OrderEntity.h"
namespace Ui {
class OrderViewItem;
}

class OrderViewItem : public QWidget
{
    Q_OBJECT

public:
    explicit OrderViewItem(QWidget *parent = nullptr);
    ~OrderViewItem();

    const OrderEntity &getOrder() const;
    void setOrder(const OrderEntity &newOrder);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    Ui::OrderViewItem *ui;
    OrderEntity order;
    QPoint mousePos;
private slots:
    void mouseClicked();
};

#endif // ORDERVIEWITEM_H
