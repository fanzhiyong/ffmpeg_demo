#include "ffmpegplayer.h"
#include "show/sdlshow.h"
#include "ffmpegplayercore.h"
#include <QPainter>

FFmpegPlayer::FFmpegPlayer(QWidget *parent) : QWidget(parent)
{
    m_show = new SDLShow(this);
    m_core = new FFmpegPlayerCore(this, m_show);

    // 不更新，更新会导致闪烁的问题
    setUpdatesEnabled(false);
}

//void FFmpegPlayer::setFps(qreal fps)
//{
//    m_core->setFps(fps);
//}

void FFmpegPlayer::play(const QString &address)
{
    m_core->play(address);
}

void FFmpegPlayer::stop()
{
    m_core->stop();
}

void FFmpegPlayer::pause()
{
    m_core->pause();
}

int FFmpegPlayer::getLength()
{
    return m_core->getLength();
}

bool FFmpegPlayer::event(QEvent *event)
{
    if( event->type() == QEvent::Resize || event->type() == QEvent::Show )
    {
        m_show->repaint();
    }

    return QWidget::event(event);
}

void FFmpegPlayer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.fillRect(rect(), QBrush(QColor(0,0,0)));
}
