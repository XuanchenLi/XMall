#ifndef PRODUCTLISTWIDGET_H
#define PRODUCTLISTWIDGET_H
#include "Service/ProductEntity.h"
#include "Service/OrderItemEntity.h"
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class ProductListWidget;
}

class ProductListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductListWidget(QWidget *parent = nullptr);
    ~ProductListWidget();

    const ProductEntity &getProductEntity() const;
    void setProductEntity(const ProductEntity &newProductEntity);

    const QString &getPhone() const;
    void setPhone(const QString &newPhone);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);


private:
    Ui::ProductListWidget *ui;
    ProductEntity productEntity;
    QPoint mousePos;
    QString phone;

private slots:
    void mouseClicked();
    void on_modified(ProductEntity);
    void on_addCart();
    void on_order(OrderItemEntity);
signals:
    //void clicked();
    void addCart();
    void order(OrderItemEntity);
};

#endif // PRODUCTLISTWIDGET_H
