#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>

namespace Ui {
class TopBar;
}

class TopBar : public QWidget
{
    Q_OBJECT

public:
    explicit TopBar(QWidget *parent = nullptr);
    ~TopBar();
    void setFatherWindow(QWidget*);
private slots:
    void on_screenPushButton_clicked();

private:
    Ui::TopBar *ui;
    Qt::WindowState screenState;//全屏为1；
    QWidget *faWin;
    QSize previousSize;
};

#endif // TOPBAR_H
