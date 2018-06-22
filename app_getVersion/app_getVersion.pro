QT += core
QT -= gui

CONFIG += c++11

TARGET = app_getVersion
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    feedsourcereadermgr.cpp

HEADERS += \
    feedsourcereadermgr.h

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += /usr/include

LIBS += -L/home/test/Downloads/jsoncpp-src-0.5.0/libs/linux-gcc-5.5.0/ -ljson_linux-gcc-5.5.0_libmt

