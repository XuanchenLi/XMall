#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QRegularExpressionValidator>
#include <QScopedPointer>
#include "alertwindow.h"
#include "Service/HttpProxy.h"
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

protected:
    void mouseMoveEvent(QMouseEvent * mouseEvent);//鼠标移动事件
    void mousePressEvent(QMouseEvent* mouseEvent);//鼠标按下事件

private:
    Ui::Register *ui;
    QPoint p;
    QRegularExpressionValidator passwordValidator;
    QRegularExpressionValidator emailValidator;
    QRegularExpressionValidator phoneValidator;
    AlertWindow *alertWin;
    QScopedPointer<HttpProxy> httpProxy;

private slots:

    void on_minimizeToolButton_clicked();

    void on_quitToolButton_clicked();

    void on_registerPushButton_clicked();



signals:
    void retLogin(QPoint);
};

#endif // REGISTER_H
