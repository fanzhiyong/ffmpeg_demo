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

    static ShowFrame * crate(int w, int h, unsigned char * buffer);

    static unsigned char * createYUV(int w, int h, int y, int u, int v);

    int w;
    int h;

    QList<unsigned char *> data;
    QList<int>             linesize;
};

#endif // SHOWGLOBAL_H
