#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QPushButton>
#include <QLabel>
#include <QTabBar>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->profileTabWidget->setTabPosition(QTabWidget::West);
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
    connect(ui->exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->switchAccountAction, SIGNAL(triggered()), this, SLOT(on_switchAccountAction_trigger()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_switchAccountAction_trigger()
{
    Login* loginWin = new Login;
    this->close();
    loginWin->show();
}
