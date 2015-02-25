#-------------------------------------------------
#
# Project created by QtCreator 2014-04-20T05:42:53
#
#-------------------------------------------------

QT       += core gui sql

TARGET = addressBook
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    logondialog.cpp \
    common.cpp \
    newaddressdialog.cpp \
    modaddressdialog.cpp

HEADERS  += maindialog.h \
    logondialog.h \
    common.h \
    newaddressdialog.h \
    modaddressdialog.h

FORMS    += maindialog.ui \
    logondialog.ui \
    newaddressdialog.ui \
    modaddressdialog.ui

RESOURCES += \
    images.qrc
