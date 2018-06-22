QT += core
QT -= gui

QMAKE_CXXFLAGS += -std=c++0x
CONFIG+=no_keywords

TARGET = app_socketioClient
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

#LIBS += /home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/libboost_date_time.a
#LIBS += /home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/libboost_system.a
#LIBS += /home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/libsioclient_tls.a
#LIBS += /home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/libboost_random.a
#LIBS += /home/test/my_Code/socketio/socket.io-client-cpp/build/lib/Release/libsioclient.a

#INCLUDEPATH += /home/test/my_Code/socketio/socket.io-client-cpp/build/include

#QMAKE_CXXFLAGS += -std=c++11

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

HEADERS +=
