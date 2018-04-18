#ifndef MMTIMER_H
#define MMTIMER_H

#include <windows.h>
#include <QtCore/QObject>

// LIBS += -lwinmm

class MMTimer : public QObject
{
    Q_OBJECT
public:
    explicit MMTimer(QObject *parent = 0, int interval = 0);

    ~MMTimer();

    void setInterval(int interval);

    void start();

    void stop();

    bool isActive();

signals:

    void timeout();

private:

    friend void WINAPI CALLBACK mmtimer_proc(uint, uint, DWORD_PTR, DWORD_PTR, DWORD_PTR);

    void onTimeout();

private:

    int m_id;
    int m_interval;
};

#endif // MMTIMER_H
