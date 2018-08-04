#-------------------------------------------------
#
# Project created by QtCreator 2018-08-03T13:41:37
#
#-------------------------------------------------

QT       += core gui
QT       += sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manager
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    pieview.cpp

HEADERS  += widget.h \
    connection.h \
    pieview.h

FORMS    += widget.ui
