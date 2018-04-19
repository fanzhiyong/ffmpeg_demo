#include "ffmpegplayervideo.h"
#include <QDebug>
#include "show/showbase.h"
#include "ffmpegplayercore.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

FFmpegPlayerVideo::FFmpegPlayerVideo(QObject *parent, ShowBase * showBase) : QObject(parent)
{
    m_fps     = 0;
    m_show    = showBase;
    m_frame   = av_frame_alloc();
    m_context = NULL;

    m_timer   = new MMTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void FFmpegPlayerVideo::setFps(qreal fps)
{
    m_fps = fps;
}

void FFmpegPlayerVideo::setContext(AVCodecContext *context)
{
    m_context = context;
}

void FFmpegPlayerVideo::start()
{
    int ms =  m_fps > 0 ? 1000/m_fps : 40;    // 25fps
    m_timer->setInterval(ms);
    m_timer->start();
}

void FFmpegPlayerVideo::pause()
{
    if( m_timer->isActive() )
    {
        m_timer->stop();
    }
    else
    {
        m_timer->start();
    }
}

void FFmpegPlayerVideo::stop()
{
    m_timer->stop();
    clear();
    // reset
    m_show->reset();
}

void FFmpegPlayerVideo::showFrame()
{
    if( m_show == NULL ) return;

    ShowFrame showFrame(m_frame->width, m_frame->height);
    for( int i = 0; i < 3; i++ )
    {
        showFrame.data.push_back(m_frame->data[i]);
        showFrame.linesize.push_back(m_frame->linesize[i]);
    }
    m_show->show(&showFrame);
}

void FFmpegPlayerVideo::onTimeout()
{
    AVPacket * packet = getPacket();
    if( packet != NULL )
    {
        int gotPicture = 0;
        if( avcodec_decode_video2(m_context, m_frame, &gotPicture, packet) < 0 )
        {
            qInfo()<<"Decode error.";
        }
        else
        {
            if( gotPicture )
            {
                showFrame();
            }
        }

        av_free_packet(packet);
    }

}
