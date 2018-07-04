#-------------------------------------------------
#
# Project created by QtCreator 2018-05-16T11:51:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StringAnalytic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataprocessing.cpp \
    dynamicallycreatingcontrol.cpp

HEADERS  += mainwindow.h \
    datastructure.h \
    dataprocessing.h \
    dynamicallycreatingcontrol.h

FORMS    += mainwindow.ui

LIBS += -L/home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release -lboost_date_time -lsioclient

INCLUDEPATH += /home/test/my_Code/socketio/socket.io-client-cpp/build/include
