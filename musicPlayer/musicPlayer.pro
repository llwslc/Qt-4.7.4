#-------------------------------------------------
#
# Project created by QtCreator 2012-09-22T20:13:00
#
#-------------------------------------------------

QT       += core gui phonon sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = musicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    myplaylist.cpp \
    mylrc.cpp \
    common.cpp

HEADERS  += mywidget.h \
    myplaylist.h \
    mylrc.h \
    common.h

FORMS    += mywidget.ui

RESOURCES += \
    images.qrc
