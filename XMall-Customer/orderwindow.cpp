#include "orderwindow.h"
#include "ui_orderwindow.h"
#include "Service/FreightEntity.h"
#include "Service/CartEntity.h"
#include "Service/HttpProxy.h"
#include "alertwindow.h"
#include <QJsonArray>
#include <QLabel>
OrderWindow::OrderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderWindow)
{
    ui->setupUi(this);
    QImage img;
    img.load (":/pics/icons/mylogo.png");
    QPixmap pixmap(QPixmap::fromImage(img));
    QLabel* logoLabel = new QLabel(this);
    pixmap = pixmap.scaled(24,24);
    logoLabel->setScaledContents(true);
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLabel->setPixmap(pixmap);
    QLabel* textLabel = new QLabel(this);
    textLabel->setText("©2021 XMall。保留所有权利。");
    ui->statusbar->addPermanentWidget(logoLabel);
    ui->statusbar->addPermanentWidget(textLabel);
}

OrderWindow::~OrderWindow()
{
    delete ui;
}
