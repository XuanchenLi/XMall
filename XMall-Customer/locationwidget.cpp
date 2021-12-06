#include "locationwidget.h"
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
LocationWidget::LocationWidget(QObject *parent)
    :QObject(parent)
{
    disposeCityList();
}

LocationWidget::~LocationWidget()
{

}

void LocationWidget::disposeCityList(void)
{
    QFile file(":/xml/xml/LocList.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement rootElement = doc.documentElement();
    if (rootElement.tagName() != "Location")
        return;

    QDomElement chinaElement;
    QDomNodeList nodeLsit = rootElement.childNodes();
    for (int i=0; i<nodeLsit.count(); ++i)
    {
        QDomElement element = nodeLsit.at(i).toElement();
        if (element.attribute("Name") == "中国")
        {
            chinaElement = element;
            break;
        }
    }

    if (chinaElement.isNull())
        return;

    QDomNodeList chinaNodeList = chinaElement.childNodes();
    for (int i=0; i<chinaNodeList.count(); ++i)
    {
        // 解析省/直辖市
        QDomElement element = chinaNodeList.at(i).toElement();
        QString stateName = element.attribute("Name");
        QList<CityInfo> cityInfoList;
        cityInfoList.clear();

        // 解析城市
        QDomNodeList cityNodeList = element.childNodes();
        for (int j=0; j<cityNodeList.count(); ++j)
        {
            QDomElement cityElement = cityNodeList.at(j).toElement();
            QString cityName = cityElement.attribute("Name");

            CityInfo cityInfo;
            cityInfo.cityName = cityName;
            QList<QString> regionNameList;
            regionNameList.clear();

            // 解析区
            QDomNodeList regionNodeList = cityElement.childNodes();
            for (int k=0; k<regionNodeList.count(); ++k)
            {
                QDomElement regionElement = regionNodeList.at(k).toElement();

                QString regionName = regionElement.attribute("Name");
                regionNameList.push_back(regionName);
            }

            cityInfo.regionName = regionNameList;
            cityInfoList.push_back(cityInfo);
        }

        chinaCityInfoMap.insert(stateName, cityInfoList);
    }
}

QList<QString> LocationWidget::getProvinceName(void)
{
    QList<QString> provinceNameList;
    provinceNameList.clear();
    for (auto itor = chinaCityInfoMap.begin(); itor != chinaCityInfoMap.end(); ++itor)
    {
        provinceNameList.push_back(itor.key());
    }
    return provinceNameList;
}

QList<QString> LocationWidget::getCitysName(QString name)
{
    auto itor = chinaCityInfoMap.find(name);
    QList<CityInfo> cityList = itor.value();
    QList<QString> cityNameList;
    cityNameList.clear();
    for (int i=0; i<cityList.count(); ++i)
    {
        cityNameList.push_back(cityList.at(i).cityName);
    }

    return cityNameList;
}

QList<QString> LocationWidget::getRegionsName(QString stateName, QString cityName)
{
    auto itor = chinaCityInfoMap.find(stateName);
    QList<CityInfo> cityList = itor.value();
    QList<QString> regionNameList;
    regionNameList.clear();
    for (int i=0; i<cityList.count(); ++i)
    {
        if (cityList.at(i).cityName == cityName)
            return cityList.at(i).regionName;
    }

    return regionNameList;
}
