#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ffmpeg/ffmpegplayer.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

private slots:
    void on_playBtn_clicked();

    void on_stopBtn_clicked();

    void on_pauseBtn_clicked();

private:

    Ui::Widget *ui;

    FFmpegPlayer * m_player;
};

#endif // WIDGET_H
