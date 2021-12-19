#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H
#include "Service/OrderItemEntity.h"
#include "Service/OrderEntity.h"
#include <QMainWindow>
#include <QVector>
namespace Ui {
class OrderWindow;
}

class OrderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrderWindow(QWidget *parent = nullptr);
    ~OrderWindow();
    void initNew(QVector<OrderItemEntity>);
    const QVector<OrderItemEntity> &getItemVector() const;
    void setItemVector(const QVector<OrderItemEntity> &newItemVector);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);

    const OrderEntity &getOrderEntity() const;
    void setOrderEntity(const OrderEntity &newOrderEntity);
    double calculate();
private slots:
    void on_orderPushButton_clicked();

private:
    Ui::OrderWindow *ui;
    QVector<OrderItemEntity> itemVector;
    QString phone;
    OrderEntity orderEntity;
    double freightPrice;
    double totPrice;
    double payPrice;
};

#endif // ORDERWINDOW_H
