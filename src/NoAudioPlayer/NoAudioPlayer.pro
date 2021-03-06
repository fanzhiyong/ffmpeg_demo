#-------------------------------------------------
#
# Project created by QtCreator 2018-04-18T09:24:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoAudioPlayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include(../ffmpeg.pri)

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    ../common/show/sdlshow.cpp \
    ../common/show/showbase.cpp \
    ../common/show/showglobal.cpp \
    ../common/ffmpeg/ffmpegglobal.cpp \
    ../common/ffmpeg/ffmpegpacketqueue.cpp \
    ../common/ffmpeg/ffmpegplayer.cpp \
    ../common/ffmpeg/ffmpegplayercore.cpp \
    ../common/ffmpeg/ffmpegplayervideo.cpp \
    ../common/ffmpeg/mmtimer.cpp

HEADERS += \
        widget.h \
    ../common/show/sdlshow.h \
    ../common/show/showbase.h \
    ../common/show/showglobal.h \
    ../common/ffmpeg/ffmpegglobal.h \
    ../common/ffmpeg/ffmpegpacketqueue.h \
    ../common/ffmpeg/ffmpegplayer.h \
    ../common/ffmpeg/ffmpegplayercore.h \
    ../common/ffmpeg/ffmpegplayervideo.h \
    ../common/ffmpeg/mmtimer.h

FORMS += \
        widget.ui
