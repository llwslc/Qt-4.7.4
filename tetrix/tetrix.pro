
QT       += core gui
QT       += sql
QT       += network
QT       += widgets

HEADERS       = \
    tetrixpiece.h \
    tetrixboard.h \
    tetrixwindow.h \
    listdialog.h \
    common.h \
    recorddialog.h
SOURCES       = main.cpp \
    tetrixpiece.cpp \
    tetrixboard.cpp \
    tetrixwindow.cpp \
    listdialog.cpp \
    common.cpp \
    recorddialog.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/tetrix
INSTALLS += target

FORMS += \
    listdialog.ui \
    recorddialog.ui
