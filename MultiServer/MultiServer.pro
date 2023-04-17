#-------------------------------------------------
#
# Project created by QtCreator 2013-04-08T23:15:39
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

TARGET = MultiServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    myserver.cpp \
    mythread.cpp

HEADERS += \
    myserver.h \
    mythread.h
