#ifndef FFMPEGPLAYERVIDEO_H
#define FFMPEGPLAYERVIDEO_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "ffmpegpacketqueue.h"
#include "mmtimer.h"

class  ShowBase;
struct AVFrame;
struct AVCodecContext;

class FFmpegPlayerVideo : public QObject, public FFmpegPacketQueue
{
    Q_OBJECT
public:
    explicit FFmpegPlayerVideo(QObject *parent = 0, ShowBase * showBase = NULL);

    void setFps(qreal fps);

    void setContext(AVCodecContext *context);

    void start();

    void pause();

    void stop();

private:

    void showFrame();

private slots:

    void onTimeout();

private:

    ShowBase         * m_show;
    AVFrame          * m_frame;

    qreal              m_fps;

    MMTimer          * m_timer;

    AVCodecContext   * m_context;
};

#endif // FFMPEGPLAYERVIDEO_H
