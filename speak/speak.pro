#-------------------------------------------------
#
# Project created by QtCreator 2013-03-31T11:42:52
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += network

CONFIG   += qaxcontainer

TARGET = speak
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    win7tts.cpp \
    itts.cpp

HEADERS  += mainwindow.h \
    itts.h \
    win7tts.h

FORMS    += mainwindow.ui
