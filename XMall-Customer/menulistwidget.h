#ifndef MENULISTWIDGET_H
#define MENULISTWIDGET_H

#include <QWidget>
#include <QWidgetAction>


class MenuListWidget : public QWidgetAction
{
    Q_OBJECT

public:
    explicit MenuListWidget(QObject *parent = nullptr);
    ~MenuListWidget();


protected:
    // is an virtual function in QWidgetAction(important)
    QWidget* createWidget(QWidget *parent);

private:



};

#endif // MENULISTWIDGET_H
