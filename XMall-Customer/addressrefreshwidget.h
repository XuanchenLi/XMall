#ifndef ADDRESSREFRESHWIDGET_H
#define ADDRESSREFRESHWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
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
    void setAddressVector(QString phone);
    void insertAddress(AddressListItem* addressItem);
    void clear();
    void play(QString phone);
    QString selectedAddress();

private:
    Ui::AddressRefreshWidget *ui;
    QVector<AddressListItem*> addressVector;
    int curIndex = 0;
    QString phone;
private  slots:
     void  onScrollBarMoved( int );
     void  onReachedBottom();
     void on_deleteRecord(bool);
};

#endif // ADDRESSREFRESHWIDGET_H
