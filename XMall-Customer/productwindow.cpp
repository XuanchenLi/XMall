#include "productwindow.h"
#include "ui_productwindow.h"

ProductWindow::ProductWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductWindow)
{
    ui->setupUi(this);
}

ProductWindow::~ProductWindow()
{
    delete ui;
}
