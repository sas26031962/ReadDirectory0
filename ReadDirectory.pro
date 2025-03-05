#QT -= gui
QT += core gui

CONFIG += c++11 console
CONFIG -= app_bundle
CONFIG += c++14 # Добавляем поддержку C++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    crecord.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    crecord.h

DISTFILES += \
    Data/FilesConfig.ini \
    Data/Protocol.txt \
    Data/TODO_List.txt
