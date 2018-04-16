#include "ffmpegcore.h"
#include <QDebug>

FFmpegCore *FFmpegCore::getInstance()
{
    static FFmpegCore fc;
    return &fc;
}

bool FFmpegCore::load(const QString &name)
{
    // open
    if( avformat_open_input(&m_formatCtx, name.toStdString().c_str(), NULL, NULL) != 0 )
    {
        qWarning()<<"open "<<name<<" error.";
        return false;
    }

    // info
    if( avformat_find_stream_info(m_formatCtx, NULL) < 0 )
    {
        qWarning()<<"can't find stream info.";
        return false;
    }

    for( unsigned int i = 0; i < m_formatCtx->nb_streams; i++ )
    {
        AVStream * avStream = m_formatCtx->streams[i];
        if( avStream->codec->codec_type == AVMEDIA_TYPE_VIDEO )
        {
            qInfo()<<"Duration: "<<getDurationMs(avStream);
            qInfo()<<"Frames: "<<avStream->nb_frames;
            qInfo()<<"FPS: "<<avStream->avg_frame_rate.num/(double)avStream->avg_frame_rate.den;
            qInfo()<<"BitRate: "<<avStream->codecpar->bit_rate;
            qInfo()<<"Size: "<<avStream->codecpar->width<<" "<<avStream->codecpar->height;
        }
    }

    return true;
}

FFmpegCore::FFmpegCore(QObject *parent) : QObject(parent)
{
    m_formatCtx = NULL;

    init();
}

void FFmpegCore::init()
{
    av_register_all();
}

qint64 FFmpegCore::getDurationMs(AVStream *stream)
{
    if( stream == NULL ) return 0;

    qint64 duration = stream->time_base.num * stream->duration * 1000 / (double)stream->time_base.den;
    return duration;
}
