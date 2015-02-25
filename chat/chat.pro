#-------------------------------------------------
#
# Project created by QtCreator 2010-06-02T08:59:18
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

TARGET = chat
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    tcpclient.cpp \
    tcpserver.cpp \
    chat.cpp \
    logondialog.cpp \
    common.cpp

HEADERS  += widget.h \
    tcpclient.h \
    tcpserver.h \
    chat.h \
    logondialog.h \
    common.h

FORMS    += widget.ui \
    tcpclient.ui \
    tcpserver.ui \
    chat.ui \
    logondialog.ui


RESOURCES += \
    resource.qrc
