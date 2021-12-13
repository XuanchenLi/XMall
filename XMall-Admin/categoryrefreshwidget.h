#ifndef CATEGORYREFRESHWIDGET_H
#define CATEGORYREFRESHWIDGET_H

#include <QWidget>
#include "categorylistitem.h"
namespace Ui {
class CategoryRefreshWidget;
}

class CategoryRefreshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryRefreshWidget(QWidget *parent = nullptr);
    ~CategoryRefreshWidget();
    void setCategoryVector(int level);
    void insertCategory(CategoryListItem* categoryItem);
    void clear();
    void play(int level);
    int getLevel() const;

    void setLevel(int newLevel);

    const QVector<CategoryListItem *> &getCategoryVector() const;

private:
    Ui::CategoryRefreshWidget *ui;
    QVector<CategoryListItem*> categoryVector;
    int curIndex = 0;
    int level;
private  slots:
     void  onScrollBarMoved( int );
     virtual void  onReachedBottom();
     void on_deleteRecord(bool);
signals:
     void refreshBox();
};

#endif // CATEGORYREFRESHWIDGET_H
