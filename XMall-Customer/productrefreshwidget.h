#ifndef PRODUCTREFRESHWIDGET_H
#define PRODUCTREFRESHWIDGET_H
#include "productlistwidget.h"
#include "Service/CategoryEntity.h"
#include "mainwindow.h"
#include <QWidget>

namespace Ui {
class ProductRefreshWidget;
}

class ProductRefreshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProductRefreshWidget(QWidget *parent = nullptr);
    ~ProductRefreshWidget();
    void setVector(int status);
    void setVector();
    void insert(ProductListWidget* item);
    void clear(int status);
    void clear();
    void play(int status);
    void play();
    void play(CategoryEntity, int);
    enum {COMING_SOON = 0, ON_SALE = 1, NOT_ON_SALE = 2, SHORTAGE = 3, STATUS_NUMBER = 4};//Enum HACK!!!
    const QString &getPhone() const;
    void setPhone(const QString &newPhone);

    void setFather(MainWindow *newFather);

private:
    Ui::ProductRefreshWidget *ui;
    QVector<ProductListWidget*> productVectors[STATUS_NUMBER + 1];
    CategoryEntity curCategory;
    int curIndex = 0;
    int curStatus;
    QString phone;
    MainWindow *father;
private  slots:
     void  onScrollBarMoved( int );
     virtual void  onReachedBottom();
     //void on_deleteRecord(bool);
     void on_addCart();
     void on_order(OrderItemEntity);
signals:
     void order(OrderItemEntity);
};

#endif // PRODUCTREFRESHWIDGET_H
