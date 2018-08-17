#-------------------------------------------------
#
# Project created by QtCreator 2018-08-15T08:35:35
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = protecter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp \
    threading.cpp

HEADERS  += mainwindow.h \
    config.h \
    threading.h

FORMS    += mainwindow.ui \
    config.ui
