#ifndef PRODUCTLISTWIDGET_H
#define PRODUCTLISTWIDGET_H
#include "Service/ProductEntity.h"
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

private:
    Ui::ProductListWidget *ui;
    ProductEntity productEntity;
private slots:



signals:
    //void deleteRecord(bool);
};

#endif // PRODUCTLISTWIDGET_H
