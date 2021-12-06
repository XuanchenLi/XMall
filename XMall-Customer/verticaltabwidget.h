#ifndef VERTICALTABWIDGET_H
#define VERTICALTABWIDGET_H

#include <QTabWidget>
#include <QApplication>
#include <QStyleOptionTab>
#include <QStylePainter>
#include <QTabBar>
#include <QTabWidget>
#include "VerticalTabBar.h"
namespace Ui {
class VerticalTabWidget;
}

class VerticalTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    VerticalTabWidget(QWidget *parent=0):QTabWidget(parent){
        setTabBar(new VerticalTabBar);
        setTabPosition(QTabWidget::West);
    }
};

#endif // VERTICALTABWIDGET_H
