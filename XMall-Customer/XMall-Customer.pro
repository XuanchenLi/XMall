QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ServiceImpl/HttpProxy.cpp \
    ServiceImpl/UserInfoDto.cpp \
    alertwindow.cpp \
    main.cpp \
    login.cpp \
    mainwindow.cpp \
    piclineedit.cpp \
    register.cpp \
    topbar.cpp

HEADERS += \
    Service/HttpProxy.h \
    Service/UserInfoDto.h \
    alertwindow.h \
    login.h \
    mainwindow.h \
    piclineedit.h \
    register.h \
    topbar.h

FORMS += \
    alertwindow.ui \
    login.ui \
    mainwindow.ui \
    piclineedit.ui \
    register.ui \
    topbar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc
