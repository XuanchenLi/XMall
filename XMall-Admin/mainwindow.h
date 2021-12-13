#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Service/AdminEntity.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCurrentAdmin(AdminEntity admin) {currentAdmin = admin;}
    AdminEntity getCurrentAdmin() const {return currentAdmin;}
    void initFunction();
    void initCategory();
private:
    Ui::MainWindow *ui;
    AdminEntity currentAdmin;

private slots:
void on_switchAccountAction_trigger();
void on_refreshBox();

void on_categoryPushButton_1_clicked();
void on_categoryPushButton_2_clicked();
};

#endif // MAINWINDOW_H
