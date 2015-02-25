#-------------------------------------------------
#
# Project created by QtCreator 2012-06-18T19:20:17
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = orderDishes
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    adminwindow.cpp \
    servewindow.cpp \
    mydatabase.cpp

HEADERS  += loginwindow.h \
    adminwindow.h \
    servewindow.h \
    mydatabase.h \
    common.h

FORMS    += loginwindow.ui \
    adminwindow.ui \
    servewindow.ui
