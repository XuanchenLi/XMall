#ifndef MENULISTWIDGET_H
#define MENULISTWIDGET_H

#include <QWidget>
#include <QWidgetAction>
#include "Service/CategoryEntity.h"
#include "mainwindow.h"

class MenuListWidget : public QWidgetAction
{
    Q_OBJECT

public:


    explicit MenuListWidget(QObject *parent = nullptr,QVector<CategoryEntity>* category1 = nullptr,
                            QVector<CategoryEntity>* category2 = nullptr ,int start = 0, int end = 0);
    ~MenuListWidget();
    //void init();

    MainWindow *getFather() const;
    void setFather(MainWindow *newFather);

protected:
    // is an virtual function in QWidgetAction(important)
    QWidget* createWidget(QWidget *parent);

private:
    int start;
    int end;
    QVector<CategoryEntity>* category1;
    QVector<CategoryEntity>* category2;
    MainWindow *father;
};

#endif // MENULISTWIDGET_H
