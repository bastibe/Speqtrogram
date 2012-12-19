#-------------------------------------------------
#
# Project created by QtCreator 2012-12-12T22:09:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Speqtrogram
TEMPLATE = app
win32:INCLUDEPATH += "C:/bin"


SOURCES += main.cpp\
        mainwindow.cpp \
    devicelist.cpp

HEADERS  += mainwindow.h\
        portaudio.h \
    devicelist.h

FORMS    += mainwindow.ui

unix:LIBS     += -lportaudio
win32:LIBS    += c:/bin/portaudio_x86.dll
