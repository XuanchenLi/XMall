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
    ServiceImpl/HttpProxy.cpp \
    ServiceImpl/UserInfoDto.cpp \
    ServiceImpl/UserInfoEntity.cpp \
    alertwindow.cpp \
    categorylistitem.cpp \
    categoryrefreshwidget.cpp \
    main.cpp \
    login.cpp \
    mainwindow.cpp \
    piclineedit.cpp \
    refreshlistwidget.cpp \
    refreshwidget.cpp \
    register.cpp

HEADERS += \
    Service/AddressEntity.h \
    Service/AdminEntity.h \
    Service/CategoryEntity.h \
    Service/HttpProxy.h \
    Service/UserInfoDto.h \
    Service/UserInfoEntity.h \
    VerticalTabBar.h \
    alertwindow.h \
    categorylistitem.h \
    categoryrefreshwidget.h \
    login.h \
    mainwindow.h \
    piclineedit.h \
    refreshlistwidget.h \
    refreshwidget.h \
    register.h \
    verticaltabwidget.h

FORMS += \
    alertwindow.ui \
    categorylistitem.ui \
    categoryrefreshwidget.ui \
    login.ui \
    mainwindow.ui \
    piclineedit.ui \
    refreshwidget.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc
