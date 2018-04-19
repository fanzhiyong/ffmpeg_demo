#ifndef FFMPEGPLAYER_H
#define FFMPEGPLAYER_H

#include <QWidget>
#include "ffmpegglobal.h"

class FFmpegPlayerCore;
class ShowBase;

class FFmpegPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit FFmpegPlayer(QWidget *parent = 0);

    //void setFps(qreal fps);

    void play(const QString & address);

    void stop();

    void pause();

    int  getLength(void);

signals:

    void timeChange(int ms);

protected:

    bool event(QEvent *event);

    void paintEvent(QPaintEvent * event);

private:

    FFmpegPlayerCore * m_core;
    ShowBase         * m_show;
};

#endif // FFMPEGPLAYER_H
