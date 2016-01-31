#-------------------------------------------------
#
# Project created by QtCreator 2016-01-31T13:22:50
#
#-------------------------------------------------

QT += core gui widgets


include(./qtsingleapplication/src/qtsingleapplication.pri)



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SingleApplication
TEMPLATE = app


SOURCES += main.cpp\
        singleapplication.cpp

HEADERS  += singleapplication.h

FORMS    += singleapplication.ui
