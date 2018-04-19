#include "ffmpegpacketqueue.h"
#include <QMutex>
#include "ffmpegglobal.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
}

FFmpegPacketQueue::FFmpegPacketQueue(int maxSize)
{
    m_maxSize = maxSize;
    m_semaphore.release(m_maxSize);
}

FFmpegPacketQueue::~FFmpegPacketQueue()
{
    //
}

void FFmpegPacketQueue::addPacket(AVPacket * packet)
{
    m_semaphore.acquire(1);

    FFmpegAutoLock al(&m_mutex);
    Q_UNUSED(al);

    m_packets.push_back(packet);
}

bool FFmpegPacketQueue::hasPacket()
{
    FFmpegAutoLock al(&m_mutex);
    Q_UNUSED(al);

    return m_packets.size() == 0 ? false : true;
}

bool FFmpegPacketQueue::isFull()
{
    FFmpegAutoLock al(&m_mutex);
    Q_UNUSED(al);

    return m_packets.size() >= m_maxSize;
}

AVPacket * FFmpegPacketQueue::getPacket()
{
    FFmpegAutoLock al(&m_mutex);
    Q_UNUSED(al);

    AVPacket * packet = NULL;
    if( m_packets.size() != 0 )
    {
        packet = m_packets.front();
        m_packets.pop_front();
        m_semaphore.release(1);
    }
    return packet;
}

void FFmpegPacketQueue::clear()
{
    FFmpegAutoLock al(&m_mutex);
    Q_UNUSED(al);

    while( m_packets.size() > 0 )
    {
        delete m_packets.front();
        m_packets.pop_front();
        m_semaphore.release(1);
    }
}

void FFmpegPacketQueue::removePacket()
{
    FFmpegAutoLock al(&m_mutex);
    Q_UNUSED(al);

    if( m_packets.size() != 0 )
    {
        m_packets.pop_front();
    }
}
