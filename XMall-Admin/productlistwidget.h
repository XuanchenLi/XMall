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

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);


private:
    Ui::ProductListWidget *ui;
    ProductEntity productEntity;
    QPoint mousePos;
private slots:
    void mouseClicked();
    void on_modified(ProductEntity);

signals:
    //void clicked();
};

#endif // PRODUCTLISTWIDGET_H
