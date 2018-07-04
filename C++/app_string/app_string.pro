QT += core
QT -= gui

CONFIG += c++11

TARGET = app_string
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++0x


