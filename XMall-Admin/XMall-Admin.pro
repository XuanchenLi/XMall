QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ServiceImpl/AddressEntity.cpp \
    ServiceImpl/HttpProxy.cpp \
    ServiceImpl/UserInfoDto.cpp \
    ServiceImpl/UserInfoEntity.cpp \
    alertwindow.cpp \
    main.cpp \
    login.cpp \
    piclineedit.cpp \
    register.cpp

HEADERS += \
    Service/AddressEntity.h \
    Service/HttpProxy.h \
    Service/UserInfoDto.h \
    Service/UserInfoEntity.h \
    alertwindow.h \
    login.h \
    piclineedit.h \
    register.h

FORMS += \
    alertwindow.ui \
    login.ui \
    piclineedit.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc
