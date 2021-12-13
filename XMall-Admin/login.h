#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include <register.h>
#include "alertwindow.h"
#include "mainwindow.h"
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


    void on_minimizeToolButton_clicked();

    void on_quitToolButton_clicked();

    void on_quitPushButton_clicked();

    void on_registerPushButton_clicked();

    void on_retLogin(QPoint pos);

    void on_loginPushButton_clicked();

private:
    Ui::Login *ui;
    QPoint p;
    Register* registerWin;
    QScopedPointer<HttpProxy> httpProxy;
    AlertWindow *alertWin;
    MainWindow *mainWin;
};
#endif // LOGIN_H
