#ifndef COMMENTLISTITEM_H
#define COMMENTLISTITEM_H

#include <QWidget>
#include "Service/CommentEntity.h"
namespace Ui {
class CommentListItem;
}

class CommentListItem : public QWidget
{
    Q_OBJECT

public:
    explicit CommentListItem(QWidget *parent = nullptr);
    ~CommentListItem();

    const CommentEntity &getCommentEntity() const;
    void setCommentEntity(const CommentEntity &newCommentEntity);

private:
    Ui::CommentListItem *ui;
    CommentEntity commentEntity;
};

#endif // COMMENTLISTITEM_H
