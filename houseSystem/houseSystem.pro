#-------------------------------------------------
#
# Project created by QtCreator 2013-02-25T00:50:18
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = houseSystem
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    mydatabase.cpp \
    adminwindow.cpp \
    userwindow.cpp \
    common.cpp \
    messagewindow.cpp

HEADERS  += loginwindow.h \
    mydatabase.h \
    common.h \
    adminwindow.h \
    userwindow.h \
    messagewindow.h

FORMS    += loginwindow.ui \
    adminwindow.ui \
    userwindow.ui \
    messagewindow.ui
