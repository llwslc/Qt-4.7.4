#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T12:06:05
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = fitBox
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqldate.cpp \
    func.cpp \
    logindialog.cpp \
    bmidialog.cpp \
    admindialog.cpp \
    stdweightdialog.cpp \
    sizedialog.cpp \
    caloriedialog.cpp \
    recorddialog.cpp \
    weightdialog.cpp \
    historydialog.cpp \
    passworddialog.cpp

HEADERS  += mainwindow.h \
    sqldate.h \
    func.h \
    logindialog.h \
    bmidialog.h \
    admindialog.h \
    stdweightdialog.h \
    sizedialog.h \
    caloriedialog.h \
    recorddialog.h \
    weightdialog.h \
    historydialog.h \
    passworddialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    bmidialog.ui \
    admindialog.ui \
    stdweightdialog.ui \
    sizedialog.ui \
    caloriedialog.ui \
    recorddialog.ui \
    weightdialog.ui \
    historydialog.ui \
    passworddialog.ui

RESOURCES += \
    image.qrc
