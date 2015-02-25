#-------------------------------------------------
#
# Project created by QtCreator 2013-02-27T15:22:06
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = sportsSystem
TEMPLATE = app


SOURCES += main.cpp\
        loginsystem.cpp \
    adminsystem.cpp \
    servesystem.cpp \
    database.cpp \
    keepersystem.cpp \
    turnoversystem.cpp \
    function.cpp

HEADERS  += loginsystem.h \
    adminsystem.h \
    servesystem.h \
    database.h \
    keepersystem.h \
    turnoversystem.h \
    function.h

FORMS    += loginsystem.ui \
    adminsystem.ui \
    servesystem.ui \
    keepersystem.ui \
    turnoversystem.ui

RESOURCES += \
    image.qrc
