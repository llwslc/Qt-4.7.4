#-------------------------------------------------
#
# Project created by QtCreator 2012-11-29T12:56:33
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += phonon
QT       += network
QT       += script

TARGET = wanmeiyichu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createbutton.cpp \
    common.cpp \
    animation.cpp \
    otherobject.cpp \
    drawcontrols.cpp \
    clotheswindow.cpp \
    mydatabase.cpp \
    filterwindow.cpp

HEADERS  += mainwindow.h \
    createbutton.h \
    common.h \
    animation.h \
    otherobject.h \
    drawcontrols.h \
    clotheswindow.h \
    mydatabase.h \
    filterwindow.h

FORMS    += mainwindow.ui \
    clotheswindow.ui \
    filterwindow.ui

RESOURCES += \
    weather.qrc \
    digiclock.qrc \
    images.qrc
