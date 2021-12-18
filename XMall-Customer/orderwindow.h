#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H
#include "Service/OrderItemEntity.h"
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

private:
    Ui::OrderWindow *ui;
    QVector<OrderItemEntity> itemVector;
    QString phone;
};

#endif // ORDERWINDOW_H
