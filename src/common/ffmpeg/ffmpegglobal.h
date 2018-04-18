#ifndef FFMPEGGLOBAL_H
#define FFMPEGGLOBAL_H

#include <QObject>
#include <QMutex>

enum PlayStatus
{
    StopStatus,     // 停止
    LoadingStatus,  // 加载中
    RunningStatus   // 播放中
};

class FFmpegAutoLock
{
public:
    FFmpegAutoLock(QMutex * mutex)
    {
        m_mutex = mutex;
        m_mutex->lock();
    }

    ~FFmpegAutoLock()
    {
        m_mutex->unlock();
    }

private:

    QMutex * m_mutex;
};

#endif // FFMPEGGLOBAL_H
