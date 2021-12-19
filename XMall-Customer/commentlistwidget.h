#ifndef COMMENTLISTWIDGET_H
#define COMMENTLISTWIDGET_H

#include <QWidget>
#include "commentlistitem.h"
namespace Ui {
class CommentListWidget;
}

class CommentListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommentListWidget(QWidget *parent = nullptr);
    ~CommentListWidget();
    void setVector(long productId);
    void insert(CommentListItem* item);
    void clear();
    void play(long productId);
private:
    Ui::CommentListWidget *ui;
    QVector<CommentListItem*> commentVector;
    int curIndex = 0;
    long productId;

private  slots:
     void  onScrollBarMoved( int );
     void  onReachedBottom();
};

#endif // COMMENTLISTWIDGET_H
