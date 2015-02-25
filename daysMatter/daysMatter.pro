#-------------------------------------------------
#
# Project created by QtCreator 2013-03-02T18:56:14
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = daysMatter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    itemwindow.cpp \
    optionswindow.cpp \
    loginwindow.cpp \
    common.cpp \
    mydatabase.cpp

HEADERS  += mainwindow.h \
    itemwindow.h \
    optionswindow.h \
    loginwindow.h \
    common.h \
    mydatabase.h

FORMS    += mainwindow.ui \
    itemwindow.ui \
    optionswindow.ui \
    loginwindow.ui

RESOURCES += \
    image.qrc
