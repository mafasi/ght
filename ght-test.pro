#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T15:52:04
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ght-test
CONFIG   -= console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    labelslidereditwidget.cpp \
    algorithm.cpp \
    imageview.cpp \
    optionsview.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

FORMS += \
    labelslidereditwidget.ui \
    imageview.ui \
    optionsview.ui

HEADERS += \
    labelslidereditwidget.h \
    algorithm.h \
    imageview.h \
    optionsview.h
