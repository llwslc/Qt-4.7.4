#-------------------------------------------------
#
# Project created by QtCreator 2014-09-10T21:49:48
#
#-------------------------------------------------

QT       += core gui
QT       += sql

CONFIG   += qaxcontainer

TARGET = fingerprint
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
        database.cpp \
        logondialog.cpp \
        common.cpp \
    qfingerprint.cpp \
    registerdialog.cpp \
    goodsdialog.cpp \
    stockadddialog.cpp \
    stockseldialog.cpp \
    borrowdialog.cpp \
    backdialog.cpp \
    stockmoddialog.cpp \
    crackerdialog.cpp

HEADERS  += maindialog.h \
        database.h \
        logondialog.h \
        common.h \
    qfingerprint.h \
    registerdialog.h \
    goodsdialog.h \
    stockadddialog.h \
    stockseldialog.h \
    borrowdialog.h \
    backdialog.h \
    stockmoddialog.h \
    crackerdialog.h

FORMS    += maindialog.ui \
        logondialog.ui \
    registerdialog.ui \
    goodsdialog.ui \
    stockadddialog.ui \
    stockseldialog.ui \
    borrowdialog.ui \
    backdialog.ui \
    stockmoddialog.ui \
    crackerdialog.ui

OTHER_FILES += \
    readme.txt
