#ifndef FFMPEGCORE_H
#define FFMPEGCORE_H

#include <QObject>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

class FFmpegCore : public QObject
{
    Q_OBJECT
public:

    static FFmpegCore * getInstance();

    bool load(const QString & name);

private:

    explicit FFmpegCore(QObject *parent = nullptr);

    void init();

private:

    AVFormatContext * m_formatCtx;
};

#endif // FFMPEGCORE_H
