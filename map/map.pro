#-------------------------------------------------
#
# Project created by QtCreator 2013-04-05T12:07:40
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webkit
QT       += script
QT       += sql
QT       += phonon

TARGET = map
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    mydatabase.cpp

HEADERS  += maindialog.h \
    mydatabase.h

FORMS    += maindialog.ui

RESOURCES += \
    resources.qrc
