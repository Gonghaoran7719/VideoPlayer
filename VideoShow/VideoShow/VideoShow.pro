#-------------------------------------------------
#
# Project created by QtCreator 2020-12-08T20:03:54
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoShow
TEMPLATE = app

RC_ICONS = logo.ico

include(./netapi/netapi.pri)
INCLUDEPATH += ./netapi/

include(./RecordVideo/RecordVideo.pri)
INCLUDEPATH += ./RecordVideo/

INCLUDEPATH += $$PWD/ffmpeg-4.2.2/include\
                $$PWD/SDL2-2.0.10/include

LIBS += $$PWD/ffmpeg-4.2.2/lib/avcodec.lib\
        $$PWD/ffmpeg-4.2.2/lib/avdevice.lib\
        $$PWD/ffmpeg-4.2.2/lib/avfilter.lib\
        $$PWD/ffmpeg-4.2.2/lib/avformat.lib\
        $$PWD/ffmpeg-4.2.2/lib/avutil.lib\
        $$PWD/ffmpeg-4.2.2/lib/postproc.lib\
        $$PWD/ffmpeg-4.2.2/lib/swresample.lib\
        $$PWD/ffmpeg-4.2.2/lib/swscale.lib\
        $$PWD/SDL2-2.0.10/lib/x86/SDL2.lib


SOURCES += main.cpp\
        videoshow.cpp \
    videoplayer.cpp \
    videoitem.cpp \
    packetqueue.cpp \
    videoslider.cpp \
    onlinedialog.cpp \
    logindialog.cpp \
    uploaddialog.cpp \
    qmymovielabel.cpp

HEADERS  += videoshow.h \
    videoplayer.h \
    videoitem.h \
    packetqueue.h \
    videoslider.h \
    onlinedialog.h \
    logindialog.h \
    uploaddialog.h \
    qmymovielabel.h

FORMS    += videoshow.ui \
    videoitem.ui \
    onlinedialog.ui \
    logindialog.ui \
    uploaddialog.ui \
    qmymovielabel.ui

RESOURCES += \
    resource.qrc
