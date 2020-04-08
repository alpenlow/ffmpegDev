TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c

INCLUDEPATH += /usr/include/x86_64-linux-gnu/

LIBS += /usr/lib/x86_64-linux-gnu/libavcodec.so \
        /usr/lib/x86_64-linux-gnu/libavformat.so \
        /usr/lib/x86_64-linux-gnu/libswscale.so \
        /usr/lib/x86_64-linux-gnu/libavutil.so
