#ifndef ADDRESSLISTITEM_H
#define ADDRESSLISTITEM_H

#include <QWidget>

namespace Ui {
class AddressListItem;
}

class AddressListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AddressListItem(QWidget *parent = nullptr);
    ~AddressListItem();

private:
    Ui::AddressListItem *ui;
};

#endif // ADDRESSLISTITEM_H
