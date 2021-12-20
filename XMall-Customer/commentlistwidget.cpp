#include "commentlistwidget.h"
#include "ui_commentlistwidget.h"
#include "commentlistitem.h"
#include "Service/HttpProxy.h"
#include "alertwindow.h"
#include "Service/CommentEntity.h"
#include <QListWidget>
#include <QJsonArray>
#include <QLabel>
extern QString GET_HOST();
CommentListWidget::CommentListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentListWidget)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(msliderChanged(int)),  this , SLOT(onScrollBarMoved(int)));
    connect(ui->listWidget, SIGNAL(reachedBottom()),  this , SLOT(onReachedBottom()));
}

CommentListWidget::~CommentListWidget()
{
    clear();
    delete ui;
}
void  CommentListWidget::onScrollBarMoved( int  v)
{

}

void  CommentListWidget::onReachedBottom()
{

     for  ( int i = 0; i < 2 && curIndex < commentVector.length(); i++, curIndex++)
     {
         insert(commentVector[curIndex]);
     }

}

void CommentListWidget::setVector(long productId)
{
    clear();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/product/comment/" + QString::number(productId));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"].toString() == "SUCCESS")
    {
        QJsonArray commentes = jsonObject["commentEntityList"].toArray();
        for (int i =0; i<commentes.count(); ++i)
        {
            CommentEntity comment = CommentEntity::parseJson(commentes[i].toObject());
            if(comment.getStatus() == comment.DELETED) continue;
            CommentListItem* item = new CommentListItem;
            item->setCommentEntity(comment);
            commentVector.push_back(item);
        }
    }

}
void CommentListWidget::insert(CommentListItem* commentItem)
{
    if (commentItem == nullptr)
    {
        qDebug()<<"空指针";
        return;
    }
    QListWidgetItem* pItem = new QListWidgetItem();
    ui->listWidget->addItem(pItem);
    pItem->setSizeHint(commentItem->size());
    ui->listWidget->setItemWidget(pItem,commentItem);

}

void CommentListWidget::clear()
{
    curIndex = 0;
    ui->listWidget->clear();
    commentVector.clear();
    commentVector.squeeze();
}
void CommentListWidget::play(long id)
{
    this->productId = id;
    ui->listWidget->clear();
    setVector(id);
    for(curIndex = 0; curIndex < commentVector.length(); ++curIndex)
    {
        insert(commentVector[curIndex]);
    }

}

