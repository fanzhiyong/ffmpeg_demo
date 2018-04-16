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
        if( m_formatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO )
        {
            qInfo()<<"Video Info";
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
