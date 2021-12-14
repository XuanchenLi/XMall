#ifndef FREIGHTLISTITEM_H
#define FREIGHTLISTITEM_H

#include <QWidget>
#include "Service/FreightEntity.h"
namespace Ui {
class FreightListItem;
}

class FreightListItem : public QWidget
{
    Q_OBJECT

public:
    explicit FreightListItem(QWidget *parent = nullptr);
    ~FreightListItem();

    const FreightEntity &getFreightEntity() const;
    void setFreightEntity(const FreightEntity &newFreightEntity);

private:
    Ui::FreightListItem *ui;
    FreightEntity freightEntity;
private slots:


    void on_pushButton_clicked();

signals:
    void deleteRecord(bool);
};

#endif // FREIGHTLISTITEM_H
