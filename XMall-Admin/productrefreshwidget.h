 #ifndef PRODUCTREFRESHWIDGET_H
#define PRODUCTREFRESHWIDGET_H
#include "productlistwidget.h"
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
    enum {COMING_SOON = 0, ON_SALE = 1, NOT_ON_SALE = 2, SHORTAGE = 3, STATUS_NUMBER = 4};//Enum HACK!!!
private:
    Ui::ProductRefreshWidget *ui;
    QVector<ProductListWidget*> productVectors[STATUS_NUMBER + 1];
    int curIndex = 0;
    int curStatus;
private  slots:
     void  onScrollBarMoved( int );
     virtual void  onReachedBottom();
     //void on_deleteRecord(bool);
};

#endif // PRODUCTREFRESHWIDGET_H
