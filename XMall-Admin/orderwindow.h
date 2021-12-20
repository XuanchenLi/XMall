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
    void initOld();
    const QVector<OrderItemEntity> &getItemVector() const;
    void setItemVector(const QVector<OrderItemEntity> &newItemVector);
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);

    const OrderEntity &getOrderEntity() const;
    void setOrderEntity(const OrderEntity &newOrderEntity);
    double calculate();

    void newByStatus();
private slots:
    void on_declinePushButton_clicked();
    void on_ackPushButton_clicked();
    void on_deliveryPushButton_clicked();
private:
    void clearLayout();
    Ui::OrderWindow *ui;
    QVector<OrderItemEntity> itemVector;
    QString phone;
    OrderEntity orderEntity;
    double freightPrice;
    double totPrice;
    double payPrice;
};

#endif // ORDERWINDOW_H
