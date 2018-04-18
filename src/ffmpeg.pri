PROJECTROOT = $$PWD/..
INCLUDEPATH += $$PROJECTROOT/include/sdl2.0
INCLUDEPATH += $$PROJECTROOT/include/ffmpeg
INCLUDEPATH += $$PROJECTROOT/src/common

# SDL
LIBS += $$PROJECTROOT/lib/sdl2.0/x86/sdl2.lib

# ffmpeg
LIBS += $$PROJECTROOT/lib/ffmpeg/avcodec.lib
LIBS += $$PROJECTROOT/lib/ffmpeg/avformat.lib
LIBS += $$PROJECTROOT/lib/ffmpeg/swscale.lib

LIBS += $$PROJECTROOT/lib/ffmpeg/avutil.lib
LIBS += $$PROJECTROOT/lib/ffmpeg/postproc.lib
LIBS += $$PROJECTROOT/lib/ffmpeg/swresample.lib
LIBS += $$PROJECTROOT/lib/ffmpeg/avdevice.lib
LIBS += $$PROJECTROOT/lib/ffmpeg/avfilter.lib

# windows
LIBS += -luser32
LIBS += -lwinmm
