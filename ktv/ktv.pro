#-------------------------------------------------
#
# Project created by QtCreator 2013-03-11T23:04:49
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += phonon

TARGET = ktv
TEMPLATE = app


SOURCES += main.cpp\
        frontwidget.cpp \
    function.cpp \
    adminwidget.cpp \
    serverwidget.cpp \
    logindialog.cpp \
    songtopdialog.cpp

HEADERS  += frontwidget.h \
    function.h \
    adminwidget.h \
    serverwidget.h \
    logindialog.h \
    songtopdialog.h

FORMS    += frontwidget.ui \
    adminwidget.ui \
    serverwidget.ui \
    logindialog.ui \
    songtopdialog.ui

RESOURCES += \
    image.qrc
