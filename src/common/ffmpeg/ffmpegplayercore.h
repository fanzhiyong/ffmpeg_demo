#ifndef FFMPEGPLAYERCORE_H
#define FFMPEGPLAYERCORE_H

#include <QObject>
#include "ffmpegglobal.h"
#include <QMutex>
#include <QWaitCondition>
#include <QThread>

class  ShowBase;
struct AVFormatContext;
struct AVPacket;
struct AVCodecContext;
class  FFmpegPlayerVideo;

class FFmpegPlayerCore : public QThread
{
    Q_OBJECT
public:
    explicit FFmpegPlayerCore(QObject *parent = 0, ShowBase * showBase = NULL);

    void setFps(qreal fps);

    void play(const QString & address);

    void stop();

    void pause();

private:

    void setStatus(PlayStatus status);

    // meida
    void loadMedia();

    bool _loadMedia();

    void playMedia();

    AVCodecContext * loadCodec(int index);

    // run
    void run();

    void globalInit();

private:

    QString             m_address;
    PlayStatus          m_status;

    AVFormatContext   * m_formatCtx;

    int                 m_audioIndex;
    int                 m_videoIndex;

    FFmpegPlayerVideo * m_video;
    //FFmpegPlayerAudio * m_audio;
};

#endif // FFMPEGPLAYERCORE_H
