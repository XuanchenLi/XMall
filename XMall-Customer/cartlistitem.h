#ifndef CARTLISTITEM_H
#define CARTLISTITEM_H
#include "Service/CartEntity.h"
#include "Service/ProductEntity.h"
#include <QWidget>

namespace Ui {
class CartListItem;
}

class CartListItem : public QWidget
{
    Q_OBJECT

public:
    explicit CartListItem(QWidget *parent = nullptr);
    ~CartListItem();

    const CartEntity &getCartEntity() const;
    void setCartEntity(const CartEntity &newCartEntity);
    const ProductEntity &getProduct() const;
    void setProduct(const ProductEntity &newProduct);
    void setTotPrice(double price);
    void setInvalid();
    bool updateCount();
    int getSpinBoxCount();
    bool isChecked() const;
    void check();

private:
    Ui::CartListItem *ui;
    CartEntity cartEntity;
    ProductEntity product;

signals:
    void deleteRecord(bool);
    void itemChanged();
private slots:
    void on_pushButton_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_checkBox_stateChanged(int arg1);
};

#endif // CARTLISTITEM_H
