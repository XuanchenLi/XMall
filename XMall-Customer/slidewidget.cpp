#include "slidewidget.h"
#include "ui_slidewidget.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include <QJsonArray>
#include "productionwindow.h"
#include "Service/HttpProxy.h"
extern QString GET_HOST();
extern QString GET_PRODUCT_BIG_PATH();
SlideWidget::SlideWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentDrawImageIndx(0)
    , ui(new Ui::SlideWidget)
{
    ui->setupUi(this);
    // 添加ImageOpacity属性，设置透明度;
    this->setProperty("ImageOpacity", 1.0);

    // 动画切换类;为动画绑定施加的对象，此处为this
    m_opacityAnimation = new QPropertyAnimation(this, "ImageOpacity");
    // 这里要设置的动画时间小于图片切换时间;
    m_opacityAnimation->setDuration(ANIMATION_DURATION);

    // 设置ImageOpacity属性值的变化范围;从透明变为透明
    m_opacityAnimation->setStartValue(1.0);
    m_opacityAnimation->setEndValue(0.0);
    // 透明度变化及时更新绘图;
    connect(m_opacityAnimation,
            &QPropertyAnimation::valueChanged,
            this,
            &SlideWidget::onValueChanged);
    // 设置图片切换时钟槽函数;
    connect(&m_imageChangeTimer, SIGNAL(timeout()), this, SLOT(onImageChangeTimeout()));

    //this->setFixedSize(QSize(400, 250));

    //this->setWindowFlags(Qt::FramelessWindowHint);
    //

    startPlay();


}

SlideWidget::~SlideWidget()
{
    delete ui;
}

void SlideWidget::initChangeImageButton()
{
    // 图片过多按钮可能放置不下;
    changeButtonGroup = new QButtonGroup;
    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->addStretch();

    for (int i = 0; i < 5; i++)
    {

        QPushButton* pButton = new QPushButton;
        pButton->setObjectName("pButton_" + QString::number(i));
        pButton->setFixedSize(QSize(16, 16));
        pButton->setCheckable(true);
        changeButtonGroup->addButton(pButton, i);
        m_pButtonChangeImageList.append(pButton);
        hLayout->addWidget(pButton);
        //qDebug()<<"new "<<pButton;
        //pButton->raise();
        //pButton->setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    hLayout->addStretch();
    hLayout->setSpacing(10);

    connect(changeButtonGroup,  &QButtonGroup::buttonClicked,
            this,
            &SlideWidget::onImageSwitchButtonClicked);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(hLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);

}
void SlideWidget::init()
{

        QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
        httpProxy->get(GET_HOST() + "/product/random/5");
        QJsonObject jsonObject = httpProxy->getJsonObject();
        if(jsonObject["statusCode"].toString() == "SUCCESS")
        {
            QJsonArray products = jsonObject["productEntityList"].toArray();
            for (int i =0; i<products.count(); ++i)
            {
                addItem(ProductEntity::parseJson(products[i].toObject()));
            }
        }

}
void SlideWidget::setImageList(QList<QPixmap> imageList)
{
    m_image = imageList;
}

void SlideWidget::addImage(QPixmap image)
{
    m_image.append(image);
}
void SlideWidget::addItem(ProductEntity product)
{
    m_product.append(product);
    //加载图片
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    QString filepath = product.getBigPicAddress();
    int first = filepath.lastIndexOf ("\\");
    QString filename = filepath.right (filepath.length ()-first-1);
    httpProxy->get(GET_HOST()+GET_PRODUCT_BIG_PATH()+filename);
    if(httpProxy->getReplyCode() == 200)
    {
        QByteArray avatarData = httpProxy->getReplyData();
        //qDebug()<<"avatarData";
        QImage img;
        img.loadFromData(avatarData);
        QPixmap pixmap(QPixmap::fromImage(img));
        m_image.append(pixmap);
    }
}
void SlideWidget::startPlay()
{
    // 添加完图片之后，根据图片多少设置图片切换按钮;

    initChangeImageButton();
    if (m_image.count() == 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
    }
    else if (m_image.count() > 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
        m_currentPixmap = m_image.at(m_currentDrawImageIndx);
        m_imageChangeTimer.start(SWITCH_DURATION);
        update();
    }
}

void SlideWidget::onImageChangeTimeout()
{
    // 设置前后的图片;
    m_currentPixmap = m_image.at(m_currentDrawImageIndx);
    m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(false);
    m_currentDrawImageIndx++;
    if (m_currentDrawImageIndx >= m_image.count())
    {
        m_currentDrawImageIndx = 0;
    }
    m_nextPixmap = m_image.at(m_currentDrawImageIndx);

    m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);

    // 动画类重新开始;
    m_opacityAnimation->start();
}

void SlideWidget::paintEvent(QPaintEvent *event)
{
    //qDebug()<<"refresh";
    QPainter painter(this);
    QRect imageRect = this->rect();

    // 如果图片列表为空，显示默认图片;
    if (m_image.isEmpty())
    {
        //QPixmap backPixmap = QPixmap("");
        //painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
    }
    // 如果只有一张图片;
    else if (m_image.count() == 1)
    {
        QPixmap backPixmap = QPixmap(m_image.first());
        painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
    }
    // 多张图片;
    else if (m_image.count() > 1)
    {
        float imageOpacity = this->property("ImageOpacity").toFloat();
        painter.setOpacity(1);
        painter.drawPixmap(imageRect, m_nextPixmap.scaled(imageRect.size()));
        painter.setOpacity(imageOpacity);
        painter.drawPixmap(imageRect, m_currentPixmap.scaled(imageRect.size()));
    }
}

void SlideWidget::onImageSwitchButtonClicked(QAbstractButton* btn)
{

    m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(false);
    m_currentDrawImageIndx = 0;
    QList<QAbstractButton*> listBt = changeButtonGroup->buttons();

    //qDebug()<<btn->objectName();
    if(listBt.isEmpty())
        return;
    for (int i = 0; i < listBt.size() ; ++i)
    {
        //qDebug()<<listBt[i]->objectName();
        if(listBt[i]->objectName() == btn->objectName())
        {
           m_currentDrawImageIndx = i - 1;
           break;
        }
    }

    if (m_currentDrawImageIndx == -1)
    {
        m_currentDrawImageIndx = m_image.count() - 1;
    }

    onImageChangeTimeout();
    m_imageChangeTimer.start(SWITCH_DURATION);
    repaint();//调用paintEvent
}

void SlideWidget::mousePressEvent(QMouseEvent* event)
{
    // 这里可以对当前图片进行点击然后触发每个图片对应的效果;
    if(m_product.empty())return;
    int curIndex = m_currentDrawImageIndx;
    ProductionWindow* productWin = new ProductionWindow;
    productWin->setPhone(phone);
    productWin->setProduct(m_product[curIndex]);
    connect(productWin, &ProductionWindow::addCart, this, &SlideWidget::on_addCart);
    connect(productWin, &ProductionWindow::order, this, &SlideWidget::on_order);
    productWin->show();

}
void SlideWidget::onValueChanged(const QVariant&)
{
    update();
}

void SlideWidget::setPhone(const QString &newPhone)
{
    phone = newPhone;
}
void SlideWidget::on_addCart()
{
    emit addCart();
}

void SlideWidget::on_order(OrderItemEntity item)
{
    emit order(item);
}
