#include "xmallmainwindow.h"
#include "ui_xmallmainwindow.h"
#include<QMouseEvent>
XMallMainWindow::XMallMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XMallMainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);    //隐藏标题栏（无边框）
    setAttribute(Qt::WA_StyledBackground);      //启用样式背景绘制
    setAttribute(Qt::WA_TranslucentBackground); //背景透明
    setAttribute(Qt::WA_Hover);//开启鼠标追踪
    QScreen *mScreen = QGuiApplication::screens().first();
    setMinimumSize(860, 500); setMaximumSize(mScreen->geometry().width(),
                                             mScreen->geometry().height());
}

XMallMainWindow::~XMallMainWindow()
{
    delete ui;
}

//重写QObject::event，悬浮事件转换为鼠标移动事件
bool XMallMainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *hoverEvent = static_cast<QHoverEvent *>(event);
        QMouseEvent mouseEvent(QEvent::MouseMove, hoverEvent->position(),
                               Qt::NoButton, Qt::NoButton, Qt::NoModifier);
        mouseMoveEvent(&mouseEvent);
    }

    return QWidget::event(event);
}
//鼠标点击事件
void XMallMainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isMousePressed = true;
        mousePressPos = event->globalPosition().toPoint();
    }
    return QWidget::mousePressEvent(event);
}

void XMallMainWindow::maximizeWidget()
{
    showMaximized();
}

void XMallMainWindow::restoreWidget()
{
    showNormal();
}

void XMallMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isMousePressed = false;
        isResizing = false;
        isDoublePressed = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void XMallMainWindow::leaveEvent(QEvent *event)
{
    isMousePressed = false;
    isDoublePressed = false;
    isResizing = false;

    QWidget::leaveEvent(event);
}
//鼠标移动事件
void XMallMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousePressed)
    {
        if(isResizing)//按下且改变大小
        {
            mouseMovePos = event->globalPosition().toPoint() - mousePressPos;
            mousePressPos += mouseMovePos;
        }
        else//只按下，则移动
        {
            if(!isDoublePressed && windowState() == Qt::WindowMaximized)
            {
                restoreWidget();
                QScreen *mScreen = QGuiApplication::screens().first();
                QPointF point(width() * ((double)(event->globalPosition().x())/mScreen->geometry().width()),
                              height() * ((double)(event->globalPosition().y())/mScreen->geometry().height()));
                move(event->globalPosition().toPoint() - point.toPoint());
                mousePressPos = event->globalPosition().toPoint();
            }

            QPoint point = event->globalPosition().toPoint() - mousePressPos;
            move(pos() + point);
            mousePressPos = event->globalPosition().toPoint();
        }
    }

    if(windowState() != Qt::WindowMaximized)
    {
        updateRegion(event);
    }

    QWidget::mouseMoveEvent(event);
}
//根据鼠标位置重绘光标
void XMallMainWindow::updateRegion(QMouseEvent *event)
{
    QRect mainRect = geometry();
    int marginTop = event->globalPosition().y() - mainRect.y();
    int marginBottom = mainRect.y() + mainRect.height() - event->globalPosition().y();
    int marginLeft = event->globalPosition().x() - mainRect.x();
    int marginRight = mainRect.x() + mainRect.width() - event->globalPosition().x();

    if(!isResizing)
    {
        if ((marginRight >= MARGIN_MIN_SIZE && marginRight <= MARGIN_MAX_SIZE)
            && (marginBottom >= MARGIN_MIN_SIZE && marginBottom <= MARGIN_MAX_SIZE))
        {
            mouseDirection = RIGHTBOTTOM;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if((marginTop >= MARGIN_MIN_SIZE && marginTop <= MARGIN_MAX_SIZE)
                && (marginRight >= MARGIN_MIN_SIZE && marginRight <= MARGIN_MAX_SIZE))
        {
            mouseDirection = RIGHTTOP;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if ( (marginLeft >= MARGIN_MIN_SIZE && marginLeft <= MARGIN_MAX_SIZE)
                  && (marginTop >= MARGIN_MIN_SIZE && marginTop <= MARGIN_MAX_SIZE) )
        {
            mouseDirection = LEFTTOP;
            setCursor(Qt::SizeFDiagCursor);
        }
        else if ( (marginLeft >= MARGIN_MIN_SIZE && marginLeft <= MARGIN_MAX_SIZE)
                  && (marginBottom >= MARGIN_MIN_SIZE && marginBottom <= MARGIN_MAX_SIZE))
        {
            mouseDirection = LEFTBOTTOM;
            setCursor(Qt::SizeBDiagCursor);
        }
        else if (marginBottom <= MARGIN_MAX_SIZE && marginBottom >= MARGIN_MIN_SIZE) {
            mouseDirection = DOWN;
            setCursor(Qt::SizeVerCursor);
        }
        else if (marginLeft <= MARGIN_MAX_SIZE - 1 && marginLeft >= MARGIN_MIN_SIZE - 1) {
            mouseDirection = LEFT;
            setCursor(Qt::SizeHorCursor);
        }
        else if ((marginRight <= MARGIN_MAX_SIZE && marginRight >= MARGIN_MIN_SIZE))
        {
            mouseDirection = RIGHT;
            setCursor(Qt::SizeHorCursor);
        }
        else if (marginTop <= MARGIN_MAX_SIZE && marginTop >= MARGIN_MIN_SIZE)
        {
            mouseDirection = UP;
            setCursor(Qt::SizeVerCursor);
        }
        else
        {
            if(!isMousePressed)
            {
                setCursor(Qt::ArrowCursor);
            }
        }
    }
    if (mouseDirection != NONE) {
        isResizing = true;
        resizeRegion(marginTop, marginBottom, marginLeft, marginRight);
    }

}
//改变窗口大小
void XMallMainWindow::resizeRegion(int marginTop, int marginBottom,
                                   int marginLeft, int marginRight)
{
    if (isMousePressed)
    {
        switch(mouseDirection){
        case RIGHTBOTTOM:
        {
            QRect rect = geometry();
            rect.setBottomRight(rect.bottomRight() + mouseMovePos);
            setGeometry(rect);
        }
            break;
        case RIGHTTOP:
        {
            if (marginLeft > minimumWidth() && marginBottom > minimumHeight())
            {
                  QRect rect = geometry();
                  rect.setTopRight(rect.topRight() + mouseMovePos);
                  setGeometry(rect);
            }
        }
            break;
        case LEFTTOP:
        {
            if (marginRight > minimumWidth() && marginBottom > minimumHeight())
            {
                  QRect rect = geometry();
                  rect.setTopLeft(rect.topLeft() + mouseMovePos);
                  setGeometry(rect);
            }
        }
            break;
        case LEFTBOTTOM:
        {
             if (marginRight > minimumWidth() && marginTop> minimumHeight())
             {
                   QRect rect = geometry();
                   rect.setBottomLeft(rect.bottomLeft() + mouseMovePos);
                   setGeometry(rect);
             }
        }
             break;
        case RIGHT:
         {
              QRect rect = geometry();
              rect.setWidth(rect.width() + mouseMovePos.x());
              setGeometry(rect);
         }
             break;
        case DOWN:
         {
              QRect rect = geometry();
              rect.setHeight(rect.height() + mouseMovePos.y());
              setGeometry(rect);
         }
              break;
         case LEFT:
         {
               if (marginRight > minimumWidth())
               {
                    QRect rect = geometry();
                    rect.setLeft(rect.x() + mouseMovePos.x());
                    setGeometry(rect);
               }
         }
               break;
         case UP:
         {
                if (marginBottom > minimumHeight())
               {
                    QRect rect = geometry();
                    rect.setTop(rect.y() + mouseMovePos.y());
                    setGeometry(rect);
               }
         }
                break;
         default:
         {
         }
                break;
        }
    }
    else {
                isResizing = false;
                mouseDirection = NONE;
          }
}
