#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T10:49:39
#
#-------------------------------------------------

QT       += core gui
QT       += network widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hotelServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    roomdata.cpp \
    guestdata.cpp

HEADERS  += mainwindow.h \
    roomdata.h \
    guestdata.h

FORMS    += mainwindow.ui
# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneserver
INSTALLS += target
