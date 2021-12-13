#ifndef MENULISTITEM_H
#define MENULISTITEM_H

#include <QWidget>
#include "Service/CategoryEntity.h"
namespace Ui {
class MenuListItem;
}

class MenuListItem : public QWidget
{
    Q_OBJECT

public:
    explicit MenuListItem(QWidget *parent = nullptr);
    ~MenuListItem();

    const CategoryEntity &getCategoryEntity() const;
    void setCategoryEntity(const CategoryEntity &newCategoryEntity);
    void setText(QString text) const;
private slots:
    void on_pushButton_clicked();

private:
    Ui::MenuListItem *ui;
    CategoryEntity categoryEntity;
};

#endif // MENULISTITEM_H
