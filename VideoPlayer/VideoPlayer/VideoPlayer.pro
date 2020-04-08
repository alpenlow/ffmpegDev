#-------------------------------------------------
#
# Project created by QtCreator 2019-10-25T01:16:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPlayer
TEMPLATE = app


SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/videoplayer.cpp

HEADERS  += inc/mainwindow.h \
    inc/videoplayer.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/inc \
               /usr/local/include/ \
               /usr/include/SDL2


LIBS += /usr/local/lib/libavformat.so \
        /usr/local/lib/libavdevice.so \
        /usr/local/lib/libavcodec.so \
        /usr/local/lib/libavfilter.so \
        /usr/local/lib/libavutil.so \
        /usr/local/lib/libswresample.so \
        /usr/local/lib/libswscale.so \
        /usr/lib/x86_64-linux-gnu/libSDL2.so
