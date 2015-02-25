#-------------------------------------------------
#
# Project created by QtCreator 2014-03-25T00:58:30
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webkit
QT       += script
QT       += sql
QT       += phonon

CONFIG   += qaxcontainer

TARGET = catchFish
TEMPLATE = app


SOURCES += main.cpp\
        logondialog.cpp \
    common.cpp \
    recorddialog.cpp \
    listdialog.cpp \
    fishdialog.cpp \
    fishitem.cpp \
    mouse.cpp \
    baritem.cpp \
    cannonitem.cpp \
    bulletitem.cpp \
    pauseitem.cpp \
    webitem.cpp \
    aboutitem.cpp

HEADERS  += logondialog.h \
    common.h \
    recorddialog.h \
    listdialog.h \
    fishdialog.h \
    fishitem.h \
    mouse.h \
    baritem.h \
    cannonitem.h \
    bulletitem.h \
    pauseitem.h \
    webitem.h \
    aboutitem.h

FORMS    += logondialog.ui \
    recorddialog.ui \
    listdialog.ui \
    fishdialog.ui

RESOURCES += \
    images.qrc
