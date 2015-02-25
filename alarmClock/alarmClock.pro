#-------------------------------------------------
#
# Project created by QtCreator 2014-03-17T23:35:04
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += phonon

TARGET = alarmClock
TEMPLATE = app


SOURCES += main.cpp\
        logondialog.cpp \
    common.cpp \
    maindialog.cpp \
    userdialog.cpp \
    coursedialog.cpp \
    musicdialog.cpp \
    alarmdialog.cpp \
    mainwindow.cpp \
    itemwindow.cpp

HEADERS  += logondialog.h \
    common.h \
    maindialog.h \
    userdialog.h \
    coursedialog.h \
    musicdialog.h \
    alarmdialog.h \
    mainwindow.h \
    itemwindow.h

FORMS    += logondialog.ui \
    maindialog.ui \
    userdialog.ui \
    coursedialog.ui \
    musicdialog.ui \
    alarmdialog.ui \
    mainwindow.ui \
    itemwindow.ui
