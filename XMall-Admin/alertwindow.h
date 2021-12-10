#ifndef ALERTWINDOW_H
#define ALERTWINDOW_H

#include <QWidget>

namespace Ui {
class AlertWindow;
}

class AlertWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AlertWindow(QWidget *parent = nullptr);
    ~AlertWindow();
    void setMessage(QString msg);

private slots:
    void on_ackPushButton_clicked();

private:
    Ui::AlertWindow *ui;
};

#endif // ALERTWINDOW_H
