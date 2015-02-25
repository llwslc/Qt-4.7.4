#-------------------------------------------------
#
# Project created by QtCreator 2013-08-09T20:32:09
#
#-------------------------------------------------

QT       += core gui
QT       += sql

CONFIG   += qaxcontainer

TARGET = QExcel
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp \
    qexcel.cpp \
    database.cpp

HEADERS  += dialog.h \
    qexcel.h \
    common.h \
    database.h

FORMS    += dialog.ui

RESOURCES += \
    res.qrc

OTHER_FILES += \
    help.txt \
    res.rc

RC_FILE = \
     res.rc
