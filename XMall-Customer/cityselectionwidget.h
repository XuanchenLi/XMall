#ifndef CITYSELECTIONWIDGET_H
#define CITYSELECTIONWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "locationwidget.h"
namespace Ui {
class CitySelectionWidget;
}

class CitySelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CitySelectionWidget(QWidget *parent = nullptr);
    ~CitySelectionWidget();
    QString getProvince() const;
    QString getCity()const;
    QString getRegion()const;

private:
    QComboBox *m_StateComboBox = nullptr;
    QComboBox *m_CityComboBox = nullptr;
    QComboBox *m_RegionComboBox = nullptr;

    QLabel *m_StateLabel;
    QLabel *m_CityLabel;
    QLabel *m_RegionLabel;


    LocationWidget *chinaCityManager = nullptr;

    Ui::CitySelectionWidget *ui;

private slots:
    void onStateComboBoxIndexChanged(int);
    void onCityComboBoxIndexChanged(int);


signals:
    void changeCity(void);

};

#endif // CITYSELECTIONWIDGET_H
