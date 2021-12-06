#ifndef REFRESHLISTWIDGET_H
#define REFRESHLISTWIDGET_H

#include <QScrollArea>
#include <QListWidget>
namespace Ui {
class RefreshListWidget;
}

class RefreshListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit RefreshListWidget(QWidget *parent = nullptr);
    ~RefreshListWidget();


private  slots:
     void  onSliderChanged( int  p);

private:

    QScrollBar* scrollBar;
signals:
     void  msliderChanged( int  p);
     void  reachedBottom();
};

#endif // REFRESHLISTWIDGET_H
