#-------------------------------------------------
#
# Project created by QtCreator 2013-04-28T02:15:52
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webkit
QT       += script
QT       += sql
QT       += phonon

TARGET = travel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mydatabase.cpp \
    logindialog.cpp \
    mapdialog.cpp \
    hoteldialog.cpp \
    placedialog.cpp \
    userdialog.cpp

HEADERS  += mainwindow.h \
    mydatabase.h \
    logindialog.h \
    mapdialog.h \
    hoteldialog.h \
    placedialog.h \
    userdialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    mapdialog.ui \
    hoteldialog.ui \
    placedialog.ui \
    userdialog.ui

RESOURCES += \
    res.qrc
