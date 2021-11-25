#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

protected:
    void mouseMoveEvent(QMouseEvent * mouseEvent);//鼠标移动事件
    void mousePressEvent(QMouseEvent* mouseEvent);//鼠标按下事件

private slots:

    void on_minimizePushButton_clicked();

    void on_minimizeToolButton_clicked();

    void on_quitToolButton_clicked();

    void on_quitPushButton_clicked();

private:
    Ui::Login *ui;

    QPoint p;
};
#endif // LOGIN_H
