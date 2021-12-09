#include "cityselectionwidget.h"
#include "ui_cityselectionwidget.h"
#include <QVBoxLayout>
#include <QListView>
CitySelectionWidget::CitySelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CitySelectionWidget)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
        //layout->addSpacing(30);

        chinaCityManager = new LocationWidget(this);

        QWidget *mainWidget = new QWidget(this);
        QVBoxLayout *bottomLayout = new QVBoxLayout(mainWidget);

        // 初始化下拉Tag
        QHBoxLayout *tagLabelLayout = new QHBoxLayout;
        m_StateLabel = new QLabel("省/直辖市");
        m_CityLabel = new QLabel("城市/直辖市区");
        m_RegionLabel = new QLabel("区/县");
        tagLabelLayout->addWidget(m_StateLabel, 0, Qt::AlignCenter);
        tagLabelLayout->addWidget(m_CityLabel, 0, Qt::AlignCenter);
        tagLabelLayout->addWidget(m_RegionLabel, 0, Qt::AlignCenter);

        // 初始化下拉按钮
        QHBoxLayout *comboLayout = new QHBoxLayout;
        m_StateComboBox = new QComboBox;
        m_StateComboBox->addItems(chinaCityManager->getProvinceName());
        m_StateComboBox->setView(new QListView(m_StateComboBox));
        comboLayout->addWidget(m_StateComboBox);

        m_CityComboBox = new QComboBox;
        comboLayout->addWidget(m_CityComboBox);
        m_CityComboBox->setView(new QListView(m_CityComboBox));

        m_RegionComboBox = new QComboBox;
        m_RegionComboBox->setView(new QListView(m_RegionComboBox));

        comboLayout->addWidget(m_RegionComboBox);

        // 初始化按钮
        //QHBoxLayout *buttonLayout = new QHBoxLayout;
        //buttonLayout->addStretch();


        // 添加布局
        bottomLayout->addLayout(tagLabelLayout);
        bottomLayout->addLayout(comboLayout);
        bottomLayout->addStretch();
        //bottomLayout->addLayout(buttonLayout);
        layout->addWidget(mainWidget);

        // 建立信号和槽的连接
        QObject::connect(m_StateComboBox, SIGNAL(currentIndexChanged(int)), \
                         this, SLOT(onStateComboBoxIndexChanged(int)));
        QObject::connect(m_CityComboBox, SIGNAL(currentIndexChanged(int)), \
                         this, SLOT(onCityComboBoxIndexChanged(int)));


        // 初始化值
        m_StateComboBox->setCurrentText("吉林");
        m_CityComboBox->setCurrentText("长春");


}

CitySelectionWidget::~CitySelectionWidget()
{
    delete ui;
}
void CitySelectionWidget::onStateComboBoxIndexChanged(int index)
{
    QString nProvinceName = m_StateComboBox->currentText();
    QList<QString> cityNameList = chinaCityManager->getCitysName(nProvinceName);
    m_CityComboBox->clear();
    m_RegionComboBox->clear();
    m_CityComboBox->addItems(cityNameList);
}

void CitySelectionWidget::onCityComboBoxIndexChanged(int index)
{
    QString nProvinceName = m_StateComboBox->currentText();
    QString nCityName = m_CityComboBox->currentText();

    QList<QString> regionNameList = chinaCityManager->getRegionsName(nProvinceName, nCityName);
    m_RegionComboBox->clear();

    m_RegionComboBox->addItems(regionNameList);
}
QString CitySelectionWidget::getProvince() const
{
    return m_StateComboBox->currentText();
}
QString CitySelectionWidget::getCity() const
{
    return m_CityComboBox->currentText();
}
QString CitySelectionWidget::getRegion() const
{
    return m_RegionComboBox->currentText();
}

