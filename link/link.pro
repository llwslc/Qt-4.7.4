#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T20:33:55
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

TARGET = link
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    client.cpp \
    server.cpp \
    connection.cpp \
    peermanager.cpp \
    common.cpp \
    chatdialog.cpp \
    listdialog.cpp \
    recorddialog.cpp

HEADERS  += dialog.h \
    client.h \
    server.h \
    connection.h \
    peermanager.h \
    common.h \
    chatdialog.h \
    listdialog.h \
    recorddialog.h

FORMS    += dialog.ui \
    chatdialog.ui \
    listdialog.ui \
    recorddialog.ui

RESOURCES += \
    image.qrc
