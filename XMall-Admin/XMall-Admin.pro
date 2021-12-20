QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ServiceImpl/AddressEntity.cpp \
    ServiceImpl/AdminEntity.cpp \
    ServiceImpl/CategoryEntity.cpp \
    ServiceImpl/FreightEntity.cpp \
    ServiceImpl/HttpProxy.cpp \
    ServiceImpl/OrderEntity.cpp \
    ServiceImpl/OrderItemEntity.cpp \
    ServiceImpl/OrderRefundFormEntity.cpp \
    ServiceImpl/ProductEntity.cpp \
    ServiceImpl/UserInfoDto.cpp \
    ServiceImpl/UserInfoEntity.cpp \
    addresslistitem.cpp \
    addressrefreshwidget.cpp \
    adminproductwindow.cpp \
    alertwindow.cpp \
    categorylistitem.cpp \
    categoryrefreshwidget.cpp \
    freightlistitem.cpp \
    freightrefreshwidget.cpp \
    main.cpp \
    login.cpp \
    mainwindow.cpp \
    orderlistitem.cpp \
    orderlistwidget.cpp \
    orderviewitem.cpp \
    orderviewwidget.cpp \
    orderwindow.cpp \
    piclineedit.cpp \
    productlistwidget.cpp \
    productrefreshwidget.cpp \
    refreshlistwidget.cpp \
    refreshwidget.cpp \
    register.cpp

HEADERS += \
    Service/AddressEntity.h \
    Service/AdminEntity.h \
    Service/CategoryEntity.h \
    Service/FreightEntity.h \
    Service/HttpProxy.h \
    Service/OrderEntity.h \
    Service/OrderItemEntity.h \
    Service/OrderRefundFormEntity.h \
    Service/ProductEntity.h \
    Service/UserInfoDto.h \
    Service/UserInfoEntity.h \
    VerticalTabBar.h \
    addresslistitem.h \
    addressrefreshwidget.h \
    adminproductwindow.h \
    alertwindow.h \
    categorylistitem.h \
    categoryrefreshwidget.h \
    freightlistitem.h \
    freightrefreshwidget.h \
    login.h \
    mainwindow.h \
    orderlistitem.h \
    orderlistwidget.h \
    orderviewitem.h \
    orderviewwidget.h \
    orderwindow.h \
    piclineedit.h \
    productlistwidget.h \
    productrefreshwidget.h \
    refreshlistwidget.h \
    refreshwidget.h \
    register.h \
    verticaltabwidget.h

FORMS += \
    addresslistitem.ui \
    addressrefreshwidget.ui \
    adminproductwindow.ui \
    alertwindow.ui \
    categorylistitem.ui \
    categoryrefreshwidget.ui \
    freightlistitem.ui \
    freightrefreshwidget.ui \
    login.ui \
    mainwindow.ui \
    orderlistitem.ui \
    orderlistwidget.ui \
    orderviewitem.ui \
    orderviewwidget.ui \
    orderwindow.ui \
    piclineedit.ui \
    productlistwidget.ui \
    productrefreshwidget.ui \
    refreshwidget.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc
