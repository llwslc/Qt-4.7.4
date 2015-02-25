#-------------------------------------------------
#
# Project created by QtCreator 2014-02-15T18:01:14
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += script
QT       += sql

TARGET = express
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    goodsdialog.cpp \
    ordersdialog.cpp \
    cardialog.cpp \
    userdialog.cpp \
    mydatabase.cpp \
    logindialog.cpp

HEADERS  += maindialog.h \
    goodsdialog.h \
    ordersdialog.h \
    cardialog.h \
    userdialog.h \
    mydatabase.h \
    logindialog.h

FORMS    += maindialog.ui \
    goodsdialog.ui \
    ordersdialog.ui \
    cardialog.ui \
    userdialog.ui \
    logindialog.ui

RESOURCES += \
    image.qrc
