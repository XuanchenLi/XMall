#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
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
private slots:

    void on_minimizeToolButton_clicked();

    void on_quitToolButton_clicked();

signals:
    void retLogin(QPoint);
};

#endif // REGISTER_H
