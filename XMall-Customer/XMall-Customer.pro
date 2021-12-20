QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ServiceImpl/AddressEntity.cpp \
    ServiceImpl/CartEntity.cpp \
    ServiceImpl/CategoryEntity.cpp \
    ServiceImpl/CommentEntity.cpp \
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
    alertwindow.cpp \
    cartlistitem.cpp \
    cartrefreshwidget.cpp \
    cityselectionwidget.cpp \
    commentlistitem.cpp \
    commentlistwidget.cpp \
    locationwidget.cpp \
    main.cpp \
    login.cpp \
    mainwindow.cpp \
    menulistitem.cpp \
    menulistwidget.cpp \
    orderlistitem.cpp \
    orderlistwidget.cpp \
    orderviewitem.cpp \
    orderviewwidget.cpp \
    orderwindow.cpp \
    piclineedit.cpp \
    productionwindow.cpp \
    productlistwidget.cpp \
    productrefreshwidget.cpp \
    productwindow.cpp \
    refreshlistwidget.cpp \
    refreshwidget.cpp \
    register.cpp \
    slidewidget.cpp

HEADERS += \
    Service/AddressEntity.h \
    Service/CartEntity.h \
    Service/CategoryEntity.h \
    Service/CommentEntity.h \
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
    alertwindow.h \
    cartlistitem.h \
    cartrefreshwidget.h \
    cityselectionwidget.h \
    commentlistitem.h \
    commentlistwidget.h \
    locationwidget.h \
    login.h \
    mainwindow.h \
    menulistitem.h \
    menulistwidget.h \
    orderlistitem.h \
    orderlistwidget.h \
    orderviewitem.h \
    orderviewwidget.h \
    orderwindow.h \
    piclineedit.h \
    productionwindow.h \
    productlistwidget.h \
    productrefreshwidget.h \
    productwindow.h \
    refreshlistwidget.h \
    refreshwidget.h \
    register.h \
    slidewidget.h \
    verticaltabwidget.h

FORMS += \
    addresslistitem.ui \
    addressrefreshwidget.ui \
    alertwindow.ui \
    cartlistitem.ui \
    cartrefreshwidget.ui \
    cityselectionwidget.ui \
    commentlistitem.ui \
    commentlistwidget.ui \
    login.ui \
    mainwindow.ui \
    menulistitem.ui \
    menulistwidget.ui \
    orderlistitem.ui \
    orderlistwidget.ui \
    orderviewitem.ui \
    orderviewwidget.ui \
    orderwindow.ui \
    piclineedit.ui \
    productionwindow.ui \
    productlistwidget.ui \
    productrefreshwidget.ui \
    productwindow.ui \
    refreshwidget.ui \
    register.ui \
    slidewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc
