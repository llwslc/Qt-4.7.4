#-------------------------------------------------
#
# Project created by QtCreator 2014-04-17T01:43:05
#
#-------------------------------------------------

QT       += core gui sql

TARGET = convenientStore
TEMPLATE = app


SOURCES += main.cpp\
        storedialog.cpp \
    common.cpp \
    bgupitem.cpp \
    aboutitem.cpp \
    bgdownitem.cpp \
    manitem.cpp \
    thinkitem.cpp \
    recorddialog.cpp \
    listdialog.cpp

HEADERS  += storedialog.h \
    common.h \
    bgupitem.h \
    aboutitem.h \
    bgdownitem.h \
    manitem.h \
    thinkitem.h \
    recorddialog.h \
    listdialog.h

FORMS    += storedialog.ui \
    recorddialog.ui \
    listdialog.ui

RESOURCES += \
    images.qrc
