#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T14:44:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeaBattle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chatclient.cpp \
    chatserver.cpp \
    cimplupta.cpp \
    corabie.cpp \
    corabiemenu.cpp \
    gamemenu.cpp \
    logmenu.cpp \
    statistica.cpp

HEADERS  += mainwindow.h \
    chatclient.h \
    chatserver.h \
    cimplupta.h \
    comun.h \
    corabie.h \
    corabiemenu.h \
    gamemenu.h \
    logmenu.h \
    statistica.h

FORMS    += mainwindow.ui
