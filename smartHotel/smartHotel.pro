#-------------------------------------------------
#
# Project created by QtCreator 2014-04-01T01:39:28
#
#-------------------------------------------------

QT       += core gui sql

TARGET = smartHotel
TEMPLATE = app


SOURCES += main.cpp\
        logondialog.cpp \
    common.cpp \
    admindialog.cpp \
    adminguestsdialog.cpp \
    adminusersdialog.cpp \
    adminroomsdialog.cpp \
    adminorderdialog.cpp \
    userroomdialog.cpp \
    roomitem.cpp \
    lighttwoitem.cpp \
    lightthritem.cpp \
    lightoneitem.cpp \
    win_qextserialport.cpp \
    qextserialport.cpp \
    qextserialbase.cpp \
    timeitem.cpp

HEADERS  += logondialog.h \
    common.h \
    admindialog.h \
    adminguestsdialog.h \
    adminusersdialog.h \
    adminroomsdialog.h \
    adminorderdialog.h \
    userroomdialog.h \
    roomitem.h \
    lighttwoitem.h \
    lightthritem.h \
    lightoneitem.h \
    win_qextserialport.h \
    qextserialport.h \
    qextserialbase.h \
    timeitem.h

FORMS    += logondialog.ui \
    admindialog.ui \
    adminguestsdialog.ui \
    adminusersdialog.ui \
    adminroomsdialog.ui \
    adminorderdialog.ui \
    userroomdialog.ui

RESOURCES += \
    images.qrc
