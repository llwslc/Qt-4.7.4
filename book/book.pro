#-------------------------------------------------
#
# Project created by QtCreator 2013-05-16T04:05:09
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

TARGET = book
TEMPLATE = app


SOURCES += main.cpp\
    logindialog.cpp \
    mydatabase.cpp \
    adbookdialog.cpp \
    adstudialog.cpp \
    adborrowdialog.cpp \
    usinfodialog.cpp \
    usborrowdialog.cpp \
    admindialog.cpp \
    userdialog.cpp \
    booksearchdialog.cpp \
    adoverdialog.cpp \
    admodifybookdialog.cpp \
    admodifystudialog.cpp \
    server.cpp \
    peermanager.cpp \
    connection.cpp \
    client.cpp \
    chatdialog.cpp

HEADERS  += logindialog.h \
    mydatabase.h \
    adbookdialog.h \
    adstudialog.h \
    adborrowdialog.h \
    usinfodialog.h \
    usborrowdialog.h \
    admindialog.h \
    userdialog.h \
    booksearchdialog.h \
    adoverdialog.h \
    admodifybookdialog.h \
    admodifystudialog.h \
    server.h \
    peermanager.h \
    connection.h \
    client.h \
    chatdialog.h


FORMS    += logindialog.ui \
    adbookdialog.ui \
    adstudialog.ui \
    adborrowdialog.ui \
    usinfodialog.ui \
    usborrowdialog.ui \
    admindialog.ui \
    userdialog.ui \
    booksearchdialog.ui \
    adoverdialog.ui \
    admodifybookdialog.ui \
    admodifystudialog.ui \
    chatdialog.ui
