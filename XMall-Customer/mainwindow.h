#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Service/MyThread.h"
#include <QMainWindow>
#include "Service/UserInfoDto.h"
#include "Service/HttpProxy.h"
#include "Service/OrderItemEntity.h"
#include "Service/CategoryEntity.h"
#include "Service/MyThread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCurrentUser(UserInfoDto userInfoDto) {currentUser = userInfoDto;}
    UserInfoDto getCurrentUser() const {return currentUser;}
    void initUserBaseInfo();
    void initFunction();
    void initAddress();
    void initCategoryMenu();
    void initProduction();
    void initSlide();
    void initOrder(QString);
    void initCart(QString);
private slots:
void on_switchAccountAction_trigger();
void on_ackPushButton_clicked();

void on_avatarPushButton_clicked();

//void on_ackPushButton_2_clicked();

void on_saveAddressPushButton_clicked();
void on_allCheckBox_stateChanged(int arg1);


void on_orderPushButton_clicked();

void on_allPushButton_clicked();

void on_waitPayPushButton_clicked();

void on_waitDeliveryPushButton_clicked();

void on_waitRecvPushButton_clicked();


void on_waitRefundPushButton_clicked();

public slots:
void on_changeCategory(CategoryEntity);
void on_finishCalculate(double);


void on_refreshPushButton_clicked();
void on_order(OrderItemEntity);
void on_addCart();

private:
    Ui::MainWindow *ui;
    UserInfoDto currentUser;
    QVector<CategoryEntity> categoryLevel1;
    QVector<CategoryEntity> categoryLevel2;
    MyThread my_thread;
};


#endif // MAINWINDOW_H
