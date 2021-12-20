#ifndef ORDERVIEWWIDGET_H
#define ORDERVIEWWIDGET_H

#include <QWidget>
#include "orderviewitem.h"
namespace Ui {
class OrderViewWidget;
}

class OrderViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OrderViewWidget(QWidget *parent = nullptr);
    ~OrderViewWidget();
    void setVector(int status);
    void setVector();
    void insert(OrderViewItem* item);
    void clear(int status);
    void clear();
    void play(int status);
    void play();
    int getCurStatus() const;
    void setCurStatus(int newCurStatus);
    enum{ STATUS_NUMBER = 6};
private:
    Ui::OrderViewWidget *ui;
    QVector<QVector<OrderViewItem*> > orderVectors;
    int curIndex = 0;
    int curStatus;
private slots:
    void  onScrollBarMoved( int );
    void  onReachedBottom();
};

#endif // ORDERVIEWWIDGET_H
