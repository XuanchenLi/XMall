#include "commentlistitem.h"
#include "ui_commentlistitem.h"
#include "Service/HttpProxy.h"
#include "Service/UserInfoEntity.h"
extern QString GET_HOST();
extern QString GET_AVATAR_PATH();
CommentListItem::CommentListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommentListItem)
{
    ui->setupUi(this);
}

CommentListItem::~CommentListItem()
{
    delete ui;
}

const CommentEntity &CommentListItem::getCommentEntity() const
{
    return commentEntity;
}

void CommentListItem::setCommentEntity(const CommentEntity &newCommentEntity)
{
    commentEntity = newCommentEntity;
    ui->time->setText(commentEntity.getCreatTime().toString("yyyy-MM-dd hh:mm:ss"));
    ui->content->setPlainText(commentEntity.getContent());
    ui->nickname->setText(commentEntity.getUserNickname());
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/user/entity/phone/"+commentEntity.getUserPhone());
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        QJsonObject userEntity = jsonObject["userInfoEntity"].toObject();
        if(userEntity["icon"].toString() == "")
        {
            QImage img;
            img.load (":/pics/avatars/defaultAvatar.jpg");
            QPixmap pixmap(QPixmap::fromImage(img));
            ui->avatar->setPixmap(pixmap);
        }
        else
        {
            QString filepath = userEntity["icon"].toString();
            int first = filepath.lastIndexOf ("\\");
            QString filename = filepath.right (filepath.length ()-first-1);
            QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
            httpProxy->get(GET_HOST()+GET_AVATAR_PATH()+filename);
            //QJsonObject jsonObject = httpProxy->getJsonObject();
            //qDebug()<<jsonObject["statusCode"];
            if(httpProxy->getReplyCode() == 200)
            {
                QByteArray avatarData = httpProxy->getReplyData();
                qDebug()<<"avatarData";
                QImage img;
                img.loadFromData(avatarData);
                QPixmap pixmap(QPixmap::fromImage(img));
                ui->avatar->setScaledContents(true);
                ui->avatar->setAlignment(Qt::AlignCenter);
                ui->avatar->setPixmap(pixmap);
            }
        }
    }
}
