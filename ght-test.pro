#-------------------------------------------------
#
# Project created by QtCreator 2014-11-23T15:52:04
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ght-test
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
