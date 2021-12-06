#ifndef REFRESHWIDGET_H
#define REFRESHWIDGET_H

#include <QWidget>

namespace Ui {
class RefreshWidget;
}

class RefreshWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RefreshWidget(QWidget *parent = nullptr);
    ~RefreshWidget();

private:
    Ui::RefreshWidget *ui;

private  slots:
     void  onScrollBarMoved( int );
     void  onReachedBottom();
};

#endif // REFRESHWIDGET_H
