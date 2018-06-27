#-------------------------------------------------
#
# Project created by QtCreator 2018-06-22T16:24:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app_chatRoom
TEMPLATE = app


CONFIG+=no_keywords

SOURCES += main.cpp\
        mainwindow.cpp \
    myqtextedit.cpp

HEADERS  += mainwindow.h \
    myqtextedit.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += /home/test/my_Code/socketio/socket.io-client-cpp/build/include
DEPENDPATH += /home/test/my_Code/socketio/socket.io-client-cpp/build/lib

LIBS += -L/home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/ -lsioclient
#else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/lib/Debug/ -lsioclient


LIBS += -L/home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/ -lboost_random
#else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/lib/Debug/ -lboost_random

LIBS += -L/home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/ -lboost_system
#else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/lib/Debug/ -lboost_system

LIBS += -L/home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/ -lboost_date_time
#else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../build/lib/Debug/ -lboost_date_time

LIBS += -L/home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/ -lsioclient_tls
