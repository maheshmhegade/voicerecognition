#-------------------------------------------------
#
# Project created by QtCreator 2012-09-09T21:31:00
#
#-------------------------------------------------

QT       += core gui

TARGET = pcro
TEMPLATE = app
LIBS  += -lasound

SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    alsasoundcard.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    alsasoundcard.h

FORMS    += mainwindow.ui
