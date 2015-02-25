#-------------------------------------------------
#
# Project created by QtCreator 2013-05-25T12:56:28
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += webkit
QT       += script
QT       += sql
QT       += phonon

TARGET = procurement
TEMPLATE = app


SOURCES += main.cpp\
        logindialog.cpp \
    mydatabase.cpp \
    maindialog.cpp \
    pwddialog.cpp \
    clientdialog.cpp \
    orderdialog.cpp \
    orderstatusdialog.cpp \
    goodsdialog.cpp

HEADERS  += logindialog.h \
    mydatabase.h \
    maindialog.h \
    pwddialog.h \
    clientdialog.h \
    orderdialog.h \
    orderstatusdialog.h \
    goodsdialog.h

FORMS    += logindialog.ui \
    maindialog.ui \
    pwddialog.ui \
    clientdialog.ui \
    orderdialog.ui \
    orderstatusdialog.ui \
    goodsdialog.ui
