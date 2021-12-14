#ifndef FREIGHTREFRESHWIDGET_H
#define FREIGHTREFRESHWIDGET_H

#include <QWidget>
#include "freightlistitem.h"
namespace Ui {
class FreightRefreshWidget;
}

class FreightRefreshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FreightRefreshWidget(QWidget *parent = nullptr);
    ~FreightRefreshWidget();
    void setVector();
    void insert(FreightListItem* item);
    void clear();
    void play();
private:
    Ui::FreightRefreshWidget *ui;
    QVector<FreightListItem*> freightVector;
    int curIndex = 0;

private  slots:
     void  onScrollBarMoved( int );
     virtual void  onReachedBottom();
     void on_deleteRecord(bool);

};

#endif // FREIGHTREFRESHWIDGET_H
