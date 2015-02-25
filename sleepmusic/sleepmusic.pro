#-------------------------------------------------
#
# Project created by QtCreator 2013-03-20T02:43:45
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += phonon

TARGET = sleepmusic
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    myfunc.cpp \
    musicdialog.cpp \
    picdialog.cpp \
    messagedialog.cpp \
    picshowdialog.cpp

HEADERS  += maindialog.h \
    myfunc.h \
    musicdialog.h \
    picdialog.h \
    messagedialog.h \
    picshowdialog.h

FORMS    += maindialog.ui \
    musicdialog.ui \
    picdialog.ui \
    messagedialog.ui \
    picshowdialog.ui

RESOURCES += \
    image.qrc
