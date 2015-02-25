#-------------------------------------------------
#
# Project created by QtCreator 2013-03-16T21:42:45
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = propertySystem
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    mydatabase.cpp \
    userdialog.cpp \
    admindialog.cpp \
    cardialog.cpp \
    ownerdialog.cpp \
    userinfodialog.cpp

HEADERS  += loginwindow.h \
    mydatabase.h \
    userdialog.h \
    admindialog.h \
    cardialog.h \
    ownerdialog.h \
    userinfodialog.h

FORMS    += loginwindow.ui \
    userdialog.ui \
    admindialog.ui \
    cardialog.ui \
    ownerdialog.ui \
    userinfodialog.ui

RESOURCES += \
    image.qrc
