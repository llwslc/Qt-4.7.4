#-------------------------------------------------
#
# Project created by QtCreator 2013-03-19T21:40:49
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = carpark
TEMPLATE = app


SOURCES += main.cpp\
        userlogin.cpp \
    cardialog.cpp \
    userdialog.cpp \
    spacedialog.cpp \
    mydatabase.cpp \
    common.cpp \
    maindialog.cpp \
    incomedialog.cpp

HEADERS  += userlogin.h \
    cardialog.h \
    userdialog.h \
    spacedialog.h \
    mydatabase.h \
    common.h \
    maindialog.h \
    incomedialog.h

FORMS    += userlogin.ui \
    cardialog.ui \
    userdialog.ui \
    spacedialog.ui \
    maindialog.ui \
    incomedialog.ui

RESOURCES += \
    image.qrc
