#ifndef XMALLMAINWINDOW_H
#define XMALLMAINWINDOW_H

#include <QWidget>

namespace Ui {
class XMallMainWindow;
}

class XMallMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit XMallMainWindow(QWidget *parent = nullptr);
    ~XMallMainWindow();

protected:
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
private:
    void restoreWidget();
    void maximizeWidget();
    void updateRegion(QMouseEvent *event);
    void resizeRegion(int marginTop, int marginBottom, int marginLeft, int marginRight);
private:
    Ui::XMallMainWindow *ui;
    QPoint mousePressPos;
    QPoint mouseMovePos;
    bool isMousePressed;
    bool isResizing;
    bool isDoublePressed;
    enum Direction {NONE = 0, UP = 1, DOWN , LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTTOP, RIGHTBOTTOM};
    Direction mouseDirection;
    const int MARGIN_MAX_SIZE = 10;
    const int MARGIN_MIN_SIZE = 2;
};

#endif // XMALLMAINWINDOW_H
