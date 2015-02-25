#-------------------------------------------------
#
# Project created by QtCreator 2013-07-01T01:23:22
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += network
QT       += sql

TARGET = painter
TEMPLATE = app

HEADERS += \
    paintarea.h \
    mainwindow.h \
    donewdialog.h

SOURCES += \
    paintarea.cpp \
    mainwindow.cpp \
    main.cpp \
    donewdialog.cpp

FORMS += \
    mainwindow.ui \
    donewdialog.ui

RESOURCES += \
    image.qrc
