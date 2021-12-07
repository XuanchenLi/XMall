#include "slidewidget.h"
#include "ui_slidewidget.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QButtonGroup>
#include <QPropertyAnimation>
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

    this->setWindowFlags(Qt::FramelessWindowHint);
    //
    addImage(":/pics/icons/test.png");
    addImage(":/pics/icons/mylogo.png");
    addImage(":/pics/icons/email.png");
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
    for (int i = 0; i < m_imageFileNameList.count(); i++)
    {
        QPushButton* pButton = new QPushButton;
        pButton->setFixedSize(QSize(16, 16));
        pButton->setCheckable(true);
        changeButtonGroup->addButton(pButton, i);
        m_pButtonChangeImageList.append(pButton);
        hLayout->addWidget(pButton);
    }
    hLayout->addStretch();
    hLayout->setSpacing(10);
    //hLayout->setMargin(0);

    connect(changeButtonGroup, &QButtonGroup::buttonClicked,
            this,
            &SlideWidget::onImageSwitchButtonClicked);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(hLayout);
    mainLayout->setContentsMargins(0, 0, 0, 20);
}

void SlideWidget::setImageList(QStringList imageFileNameList)
{
    m_imageFileNameList = imageFileNameList;
}

void SlideWidget::addImage(QString imageFileName)
{
    m_imageFileNameList.append(imageFileName);
}

void SlideWidget::startPlay()
{
    // 添加完图片之后，根据图片多少设置图片切换按钮;
    initChangeImageButton();
    if (m_imageFileNameList.count() == 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
    }
    else if (m_imageFileNameList.count() > 1)
    {
        m_pButtonChangeImageList[m_currentDrawImageIndx]->setChecked(true);
        m_currentPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
        m_imageChangeTimer.start(SWITCH_DURATION);
        update();
    }
}

void SlideWidget::onImageChangeTimeout()
{
    // 设置前后的图片;
    m_currentPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));
    m_currentDrawImageIndx++;
    if (m_currentDrawImageIndx >= m_imageFileNameList.count())
    {
        m_currentDrawImageIndx = 0;
    }
    m_nextPixmap = QPixmap(m_imageFileNameList.at(m_currentDrawImageIndx));

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
    if (m_imageFileNameList.isEmpty())
    {
        //QPixmap backPixmap = QPixmap("");
        //painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
    }
    // 如果只有一张图片;
    else if (m_imageFileNameList.count() == 1)
    {
        QPixmap backPixmap = QPixmap(m_imageFileNameList.first());
        painter.drawPixmap(imageRect, backPixmap.scaled(imageRect.size()));
    }
    // 多张图片;
    else if (m_imageFileNameList.count() > 1)
    {
        float imageOpacity = this->property("ImageOpacity").toFloat();
        painter.setOpacity(1);
        painter.drawPixmap(imageRect, m_nextPixmap.scaled(imageRect.size()));
        painter.setOpacity(imageOpacity);
        painter.drawPixmap(imageRect, m_currentPixmap.scaled(imageRect.size()));
    }
}

void SlideWidget::onImageSwitchButtonClicked(QAbstractButton* button)
{

    m_currentDrawImageIndx = 0;

    QList<QAbstractButton*> listBt = changeButtonGroup->buttons();
    if(listBt.isEmpty())
        return;
    for (int i = 0; listBt.size() ; ++i)
    {
        if(listBt[i]==button)
        {
           m_currentDrawImageIndx = i;
           break;
        }
    }

    if (m_currentDrawImageIndx == -1)
    {
        m_currentDrawImageIndx = m_imageFileNameList.count() - 1;
    }

    onImageChangeTimeout();
    m_imageChangeTimer.start(SWITCH_DURATION);
    repaint();//调用paintEvent
}

void SlideWidget::mousePressEvent(QMouseEvent* event)
{
    // 这里可以对当前图片进行点击然后触发每个图片对应的效果;
    //qDebug() << m_currentDrawImageIndx;
    //return __super::mouseEvent(event);
}
void SlideWidget::onValueChanged(const QVariant&)
{
    update();
}
