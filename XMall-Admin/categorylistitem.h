#ifndef CATEGORYLISTITEM_H
#define CATEGORYLISTITEM_H

#include <QWidget>
#include "Service/CategoryEntity.h"
namespace Ui {
class CategoryListItem;
}

class CategoryListItem : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryListItem(QWidget *parent = nullptr);
    ~CategoryListItem();

    const CategoryEntity &getCategoryEntity() const;
    void setCategoryEntity(const CategoryEntity &newCategoryEntity);

private:
    Ui::CategoryListItem *ui;
    CategoryEntity categoryEntity;

private slots:
    void on_pushButton_clicked();

signals:
    void deleteRecord(bool);
};

#endif // CATEGORYLISTITEM_H
