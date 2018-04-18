#ifndef SHOWGLOBAL_H
#define SHOWGLOBAL_H

#include <QList>

struct ShowFrame
{
    ShowFrame(int w = 0, int h = 0)
    {
        this->w = w;
        this->h = h;
    }

    int w;
    int h;

    QList<unsigned char *> data;
    QList<int>             linesize;
};

#endif // SHOWGLOBAL_H
