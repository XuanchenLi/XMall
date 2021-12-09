#ifndef ADDRESSREFRESHWIDGET_H
#define ADDRESSREFRESHWIDGET_H

#include <QWidget>
#include "addresslistitem.h"
namespace Ui {
class AddressRefreshWidget;
}

class AddressRefreshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddressRefreshWidget(QWidget *parent = nullptr);
    ~AddressRefreshWidget();
    void setAddressVector();
    void insertAddress(AddressListItem addressItem);
    void clear();


private:
    Ui::AddressRefreshWidget *ui;
    QVector<AddressListItem> addressVector;
    int curIndex = 0;

private  slots:
     void  onScrollBarMoved( int );
     void  onReachedBottom();
};

#endif // ADDRESSREFRESHWIDGET_H
