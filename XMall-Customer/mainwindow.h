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
    void setCurrentUser(UserInfoDto userInfoDto) { currentUser = userInfoDto;}
    UserInfoDto getCurrentUser() const {return currentUser;}
private slots:
void on_switchAccountAction_trigger();
private:
    Ui::MainWindow *ui;
    UserInfoDto currentUser;
};


#endif // MAINWINDOW_H
