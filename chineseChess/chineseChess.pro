#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T18:12:53
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = chineseChess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    commfunc.cpp \
    ceveluation.cpp \
    cmovegenerator.cpp \
    cnegamaxengine.cpp \
    csearchengine.cpp

HEADERS  += mainwindow.h \
    commfunc.h \
    ceveluation.h \
    cmovegenerator.h \
    cnegamaxengine.h \
    csearchengine.h

FORMS    += mainwindow.ui

RESOURCES += \
    image.qrc
