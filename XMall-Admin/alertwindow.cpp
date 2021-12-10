#include "alertwindow.h"
#include "ui_alertwindow.h"

AlertWindow::AlertWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlertWindow)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    setMinimumSize(280, 145); setMaximumSize(280, 145);

}

AlertWindow::~AlertWindow()
{
    delete ui;
}

void AlertWindow::on_ackPushButton_clicked()
{
    close();
}
void AlertWindow::setMessage(QString msg)
{
    ui->messageLabel->setText(msg);
    adjustSize();
}
