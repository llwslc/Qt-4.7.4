#-------------------------------------------------
#
# Project created by QtCreator 2014-12-25T00:40:00
#
#-------------------------------------------------

QT       += core gui
QT       += sql

TARGET = subjectTimetable
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    logondialog.cpp \
    common.cpp \
    database.cpp

HEADERS  += dialog.h \
    logondialog.h \
    common.h \
    database.h

FORMS    += dialog.ui \
    logondialog.ui
