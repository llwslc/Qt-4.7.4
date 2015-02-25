#-------------------------------------------------
#
# Project created by QtCreator 2013-03-22T17:17:24
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = football
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    playerdialog.cpp \
    scoredialog.cpp \
    accountsdialog.cpp \
    gamedialog.cpp \
    mysqldata.cpp \
    logindialog.cpp

HEADERS  += maindialog.h \
    playerdialog.h \
    scoredialog.h \
    accountsdialog.h \
    gamedialog.h \
    mysqldata.h \
    logindialog.h

FORMS    += maindialog.ui \
    playerdialog.ui \
    scoredialog.ui \
    accountsdialog.ui \
    gamedialog.ui \
    logindialog.ui

RESOURCES += \
    image.qrc
