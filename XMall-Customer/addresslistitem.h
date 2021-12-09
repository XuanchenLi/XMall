#ifndef ADDRESSLISTITEM_H
#define ADDRESSLISTITEM_H

#include <QWidget>
#include "Service/AddressEntity.h"

namespace Ui {
class AddressListItem;
}

class AddressListItem : public QWidget
{
    Q_OBJECT

public:
    explicit AddressListItem(QWidget *parent = nullptr);
    ~AddressListItem();



    const AddressEntity &getAddressEntity() const;
    void setAddressEntity(const AddressEntity &newAddressEntity);

private:
    Ui::AddressListItem *ui;
    AddressEntity addressEntity;
};

#endif // ADDRESSLISTITEM_H
