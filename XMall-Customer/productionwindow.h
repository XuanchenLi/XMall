#ifndef PRODUCTIONWINDOW_H
#define PRODUCTIONWINDOW_H

#include <QMainWindow>
#include "Service/ProductEntity.h"
#include "Service/UserInfoEntity.h"
namespace Ui {
class ProductionWindow;
}

class ProductionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProductionWindow(QWidget *parent = nullptr);
    ~ProductionWindow();

    const ProductEntity &getProduct() const;
    void setProduct(const ProductEntity &newProduct);

    const QString &getPhone() const;
    void setPhone(const QString &newPhone);
    void initComment();

private slots:
    void on_cartPushButton_clicked();

    void on_orderPushButton_clicked();

private:
    Ui::ProductionWindow *ui;
    ProductEntity product;
    QString phone;
signals:
    void addCart();
};

#endif // PRODUCTIONWINDOW_H
