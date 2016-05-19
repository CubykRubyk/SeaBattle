#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T15:40:05
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia
QT       += gui

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

RESOURCES += \
    mysounds.qrc
