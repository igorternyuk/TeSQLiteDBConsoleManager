QT += core sql
QT -= gui

CONFIG += c++14

TARGET = TeConsoleSQLiteDBConnector
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    persona.cpp \
    sqlexception.cpp \
    client.cpp \
    dbmanager.cpp

HEADERS += \
    persona.h \
    sqlexception.h \
    client.h \
    dbmanager.h \
    sql_cmd.h

QMAKE_CXXFLAGS += -std=c++14
