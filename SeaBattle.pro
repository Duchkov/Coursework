#-------------------------------------------------
#
# Project created by QtCreator 2022-12-04T04:52:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeaBattle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    images.cpp \
    battlefield.cpp \
    computer.cpp \
    battlewindow.cpp

HEADERS  += mainwindow.h \
    images.h \
    battlefield.h \
    computer.h \
    battlewindow.h

FORMS    += mainwindow.ui \
    battlewindow.ui

RESOURCES += \
    resources.qrc
