#ifndef FFMPEG_PACKET_QUEUE_H
#define FFMPEG_PACKET_QUEUE_H

#include <QList>
#include <QMutex>
#include <QSemaphore>

struct AVPacket;

class FFmpegPacketQueue
{
public:
    FFmpegPacketQueue(int maxSize = 8);

    virtual ~FFmpegPacketQueue();

    void addPacket(AVPacket * packet);

    bool hasPacket();

    bool isFull();

    AVPacket * getPacket();

protected:

    void clear();

private:

    void removePacket();

private:

    int               m_maxSize;
    QList<AVPacket *> m_packets;

    QMutex            m_mutex;
    QSemaphore        m_semaphore;
};

#endif
