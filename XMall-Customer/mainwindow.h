#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Service/UserInfoDto.h"
#include "Service/HttpProxy.h"
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
private slots:
void on_switchAccountAction_trigger();
void on_ackPushButton_clicked();

void on_avatarPushButton_clicked();

//void on_ackPushButton_2_clicked();

void on_saveAddressPushButton_clicked();

private:
    Ui::MainWindow *ui;
    UserInfoDto currentUser;
};


#endif // MAINWINDOW_H
