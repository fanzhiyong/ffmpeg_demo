#include "ffmpegplayercore.h"
#include <QSemaphore>
//#include "mmtimer.h"
#include <QDebug>
#include "show/showbase.h"
#include "ffmpegplayervideo.h"
//#include "ffmpegplayeraudio.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

FFmpegPlayerCore::FFmpegPlayerCore(QObject *parent, ShowBase * showBase) : QThread(parent)
{
    m_status     = StopStatus;
    m_audioIndex = -1;
    m_videoIndex = -1;

    globalInit();

    m_formatCtx = avformat_alloc_context();
    m_video     = new FFmpegPlayerVideo(this, showBase);

    //m_timer     = new MMTimer(this, 5);
    //connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void FFmpegPlayerCore::setFps(qreal fps)
{
    m_video->setFps(fps);
}

void FFmpegPlayerCore::play(const QString &address)
{
    stop();

    m_address = address;
    if( m_address.isEmpty() ) return;

    // load
    loadMedia();
}

void FFmpegPlayerCore::stop()
{
    setStatus(StopStatus);
    m_video->stop();
}

void FFmpegPlayerCore::pause()
{
    m_video->pause();
}

void FFmpegPlayerCore::setStatus(PlayStatus status)
{
    m_status = status;
}

void FFmpegPlayerCore::loadMedia()
{
    setStatus(LoadingStatus);
    if( _loadMedia() )
    {
        setStatus(RunningStatus);
        playMedia();
    }
    else
    {
        setStatus(StopStatus);
    }
}

bool FFmpegPlayerCore::_loadMedia()
{
    // open
    int result = avformat_open_input(&m_formatCtx, m_address.toStdString().c_str(), NULL, NULL);
    if( result != 0 )
    {
        qInfo()<<"avformat_open_input : "<<result;
        return false;
    }

    // stream info
    result = avformat_find_stream_info(m_formatCtx, NULL);
    if( result < 0 )
    {
        qInfo()<<"avformat_find_stream_info : "<<result;
        return false;
    }

    // index
    m_audioIndex = m_videoIndex = -1;
    for( unsigned i = 0; i < m_formatCtx->nb_streams; i++ )
    {
        switch( m_formatCtx->streams[i]->codec->codec_type )
        {
        case AVMEDIA_TYPE_VIDEO:
            m_videoIndex = i;
            break;
        case AVMEDIA_TYPE_AUDIO:
            m_audioIndex = i;
            break;
        default:
            break;
        }
    }

    if( m_audioIndex == -1 && m_videoIndex == -1 )
    {
        qInfo()<<"Has not video and audio.";
        return false;
    }

    // video codec
    if( m_videoIndex != -1 )
    {
        AVCodecContext * context = loadCodec(m_videoIndex);
        if( context == NULL )
        {
            return false;
        }
        m_video->setContext(context);
    }

    // audio codec
//    if( m_audioIndex != -1 )
//    {
//        AVCodecContext * context = loadCodec(m_audioIndex);
//        if( context == NULL )
//        {
//            return false;
//        }
//        m_audio->setContext(context);
//    }

    return true;
}

AVCodecContext * FFmpegPlayerCore::loadCodec(int index)
{
    AVCodecContext * tmp = m_formatCtx->streams[index]->codec;
    AVCodec * decoder = avcodec_find_decoder(tmp->codec_id);
    if( decoder == NULL )
    {
        qInfo()<<"Can't find decoder.";
        return NULL;
    }

    int result = avcodec_open2(tmp, decoder, NULL);
    if( result < 0 )
    {
        qInfo()<<"Can't open decoder.";
        return NULL;
    }

    return tmp;
}

void FFmpegPlayerCore::run()
{
    AVPacket * packet = new AVPacket();
    while( av_read_frame(m_formatCtx, packet) >= 0 && m_status != StopStatus )
    {
        if( packet->stream_index == m_videoIndex )
        {
            // if full, waiting
            m_video->addPacket(packet);
        }
        else if( packet->stream_index == m_audioIndex )
        {
            //m_audio->addPacket(packet);
        }
        else
        {
            av_free_packet(packet);
        }

        packet = new AVPacket();
    }

    setStatus(StopStatus);
}

void FFmpegPlayerCore::globalInit()
{
    static bool inited = false;
    if( inited ) return;

    // register ffmpeg
    av_register_all();
}

void FFmpegPlayerCore::playMedia()
{
    QThread::start();
    m_video->start();
}
