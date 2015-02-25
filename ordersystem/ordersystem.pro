#-------------------------------------------------
#
# Project created by QtCreator 2012-05-31T15:33:37
#
#-------------------------------------------------

QT       += core gui
QT+=sql

TARGET = ordersystem
TEMPLATE = app


SOURCES += main.cpp\
        logdialog.cpp \
    servedialog.cpp \
    mydatabase.cpp \
    admindialog.cpp \
    cpgl.cpp \
    rygl.cpp \
    dishlist.cpp

HEADERS  += logdialog.h \
    servedialog.h \
    mydatabase.h \
    admindialog.h \
    cpgl.h \
    rygl.h \
    dishlist.h \
    dish.h

FORMS    += logdialog.ui \
    servedialog.ui \
    admindialog.ui \
    cpgl.ui \
    rygl.ui \
    dishlist.ui

RESOURCES += \
    face.qrc
