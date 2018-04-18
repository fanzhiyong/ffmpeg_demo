#ifndef FFMPEGPLAYERVIDEO_H
#define FFMPEGPLAYERVIDEO_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "ffmpegpacketqueue.h"

class  ShowBase;
struct AVFrame;
struct AVCodecContext;

class FFmpegPlayerVideo : public QThread, public FFmpegPacketQueue
{
    Q_OBJECT
public:
    explicit FFmpegPlayerVideo(QObject *parent = 0, ShowBase * showBase = NULL);

    void setFps(qreal fps);

    void setContext(AVCodecContext *context);

private:

    void run();

    void showFrame();

    void waitPlayNext();

private:

    ShowBase         * m_show;
    AVFrame          * m_frame;

    qreal              m_fps;

    AVCodecContext   * m_context;
};

#endif // FFMPEGPLAYERVIDEO_H
