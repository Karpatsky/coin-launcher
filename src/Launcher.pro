#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T17:57:55
#
#-------------------------------------------------

QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++
QMAKE_CXXFLAGS += -std=c++11

TARGET = Launcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    coin.cpp \
    coinsxmldocument.cpp

HEADERS  += mainwindow.h \
    coin.h \
    coinsxmldocument.h

FORMS    += mainwindow.ui

