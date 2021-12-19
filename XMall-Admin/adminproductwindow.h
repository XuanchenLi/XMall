#ifndef ADMINPRODUCTWINDOW_H
#define ADMINPRODUCTWINDOW_H
#include "Service/ProductEntity.h"
#include "Service/CategoryEntity.h"
#include "Service/FreightEntity.h"
#include <QMainWindow>
#include <QVector>

namespace Ui {
class AdminProductWindow;
}

class AdminProductWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminProductWindow(QWidget *parent = nullptr);
    ~AdminProductWindow();
    const ProductEntity &getProduct() const;
    void setProduct(const ProductEntity &newProduct);
    void initCategory();
    void initFreight();

    int getStatus() const;
    void setStatus(int newStatus);
    enum {NEW_PRODUCT = 0, UPDATE_PRODUCT = 1};

private slots:
    void on_bigPicPushButton_clicked();

    void on_smallPicPushButton_clicked();

    void on_savePushButton_clicked();

    void on_category_1ComboBox_currentIndexChanged(int index);

private:
    Ui::AdminProductWindow *ui;
    ProductEntity product;
    CategoryEntity level2;
    QVector<CategoryEntity> categoryLevel1;
    QVector<CategoryEntity> categoryLevel2;
    QVector<FreightEntity> freightVector;
    int status;

signals:
    void modified(ProductEntity);
};

#endif // ADMINPRODUCTWINDOW_H
