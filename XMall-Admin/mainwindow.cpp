#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "Service/CategoryEntity.h"
#include "Service/ProductEntity.h"
#include "adminproductwindow.h"
#include <QPropertyAnimation>
extern QString GET_HOST();
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //
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
    connect(ui->categoryWidget_1, SIGNAL(refreshBox()), this, SLOT(on_refreshBox()));
    connect(ui->switchAccountAction,
            SIGNAL(triggered()),
            this,
            SLOT(on_switchAccountAction_trigger()));
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
     animation->setDuration(1000);
     animation->setStartValue(0);
     animation->setEndValue(1);
     animation->start();
    //
    //initCategory();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initFunction()
{
    initCategory();
    initFreight();
    initProduct();
}
void MainWindow::initCategory()
{
    ui->categoryWidget_1->setLevel(1);
    ui->categoryWidget_1->play(1);
    ui->categoryWidget_2->setLevel(2);
    ui->categoryWidget_2->play(2);
    ui->categoryComboBox->clear();
    QVector<CategoryListItem*> categories = ui->categoryWidget_1->getCategoryVector();
    for (int i = 0;i < categories.length(); ++i)
    {
        ui->categoryComboBox->addItem(QString::number(categories[i]->getCategoryEntity().getId())
                                      +": "
                                      + categories[i]->getCategoryEntity().getName());
    }
}
void MainWindow::on_switchAccountAction_trigger()
{
    Login* loginWin = new Login;
    this->close();
    loginWin->show();
}
void MainWindow::on_refreshBox()
{
    ui->categoryComboBox->clear();
    QVector<CategoryListItem*> categories = ui->categoryWidget_1->getCategoryVector();
    for (int i = 0;i < categories.length(); ++i)
    {
        ui->categoryComboBox->addItem(QString::number(categories[i]->getCategoryEntity().getId())
                                      +": "
                                      + categories[i]->getCategoryEntity().getName());
    }
}

void MainWindow::on_categoryPushButton_1_clicked()
{
    ui->categoryPushButton_1->setEnabled(false);
    QString name = ui->categoryLineEdit_1->text();
    if(name == "") return ;
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    CategoryEntity category;
    category.setParentId(0);
    category.setLevel(1);
    category.setName(name);
    httpProxy->post(GET_HOST() + "/category/insert", category.getQByteArrayForm());
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        initCategory();
        //
    }
    else
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
        ui->categoryPushButton_1->setEnabled(true);
        return ;
    }
    ui->categoryPushButton_1->setEnabled(true);
}


void MainWindow::on_categoryPushButton_2_clicked()
{
    ui->categoryPushButton_2->setEnabled(false);
    QString name = ui->categoryLineEdit_2->text();
    if(name == "")
    {
        ui->categoryPushButton_2->setEnabled(true);
        return ;
    }
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    CategoryEntity category;
    QString context = ui->categoryComboBox->currentText();
    long parent = 0 ;
    for(int i =0; context[i].isNumber() && i < context.length(); ++i)
    {
        parent *= 10;
        parent += context[i].toLatin1() - '0';
    }
    category.setParentId(parent);
    category.setLevel(2);
    category.setName(name);
    httpProxy->post(GET_HOST() + "/category/insert", category.getQByteArrayForm());
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        initCategory();
        //
    }
    else
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
        ui->categoryPushButton_2->setEnabled(true);
        return ;
    }
    ui->categoryPushButton_2->setEnabled(true);
}
void MainWindow::initFreight()
{
    ui->freightRefreshWidget->play();
}
void MainWindow::on_freightPushButton_clicked()
{
    ui->categoryPushButton_2->setEnabled(false);
    double price = ui->freightDoubleSpinBox->value();
    QScopedPointer<HttpProxy> httpProxy(new HttpProxy);
    httpProxy->get(GET_HOST() + "/freight/insert/price/" + QString::number(price, 'f', 2));
    QJsonObject jsonObject = httpProxy->getJsonObject();
    if(jsonObject["statusCode"] == "SUCCESS")
    {
        initFreight();
        //
    }
    else
    {
        AlertWindow *alertWin = new AlertWindow;
        alertWin->setMessage("网络异常");
        alertWin->show();
        ui->categoryPushButton_2->setEnabled(true);
        return ;
    }
    ui->categoryPushButton_2->setEnabled(true);
}
void MainWindow::initProduct()
{
    ui->productRefreshWidget->play();
}

void MainWindow::on_addProductButton_clicked()
{
    //qDebug()<<"Add new";
    AdminProductWindow *detailWin = new AdminProductWindow;
    detailWin->setStatus(detailWin->NEW_PRODUCT);
    ProductEntity productEntity;
    detailWin->setProduct(productEntity);
    connect(detailWin, &AdminProductWindow::modified, this, &MainWindow::initProduct);
    detailWin->show();
}

