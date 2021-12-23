#ifndef SLIDEWIDGET_H
#define SLIDEWIDGET_H
#include <QWidget>
#include <QWidget>
#include <QScrollArea>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPushButton>
#include "Service/ProductEntity.h"
#include "Service/OrderItemEntity.h"
namespace Ui {
class SlideWidget;
}
class SlideWidget : public QWidget
{
    Q_OBJECT

public:
    SlideWidget(QWidget *parent = NULL);
    ~SlideWidget();

    // 设置图片列表;
    void setImageList(QList<QPixmap>);
    void addItem(ProductEntity);
    // 添加图片;
    void addImage(QPixmap image);
    // 开始播放;
    void init();
    void startPlay();

    void setPhone(const QString &newPhone);

private:
    // 初始化图片切换按钮;
    void initChangeImageButton();
    // 绘图事件;
    void paintEvent(QPaintEvent *event);

    // 鼠标点击事件;
    void mousePressEvent(QMouseEvent* event);

public slots:
    // 图片切换时钟;
    void onImageChangeTimeout();

    // 图片切换按钮点击;
    void onImageSwitchButtonClicked(QAbstractButton*);

    void onValueChanged(const QVariant&);
    void on_addCart();
    void on_order(OrderItemEntity);

private:
    const int ANIMATION_DURATION = 500;
    const int SWITCH_DURATION = 6000;
    // 用来做图片切换滑动效果，目前以透明度作为切换效果;
    QScrollArea* m_imagePlayWidget;
    // 图片列表;
    QList<QPixmap> m_image;
    QList<ProductEntity> m_product;
    // 图片切换时钟;
    QTimer m_imageChangeTimer;

    // 当前显示图片index;
    int m_currentDrawImageIndx;

    // 切换图片;
    QPixmap m_currentPixmap;
    QPixmap m_nextPixmap;
    // 图片切换动画类;
    QPropertyAnimation* m_opacityAnimation;
    // 按钮列表;
    QList<QPushButton*> m_pButtonChangeImageList;
    QButtonGroup* changeButtonGroup;

    QString phone;
    Ui::SlideWidget *ui;

signals:
    //void clicked();
    void addCart();
    void order(OrderItemEntity);
};


#endif // SLIDEWIDGET_H
