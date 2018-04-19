#include "showglobal.h"

ShowFrame *ShowFrame::crate(int w, int h, unsigned char *buffer)
{
    ShowFrame * frame = new ShowFrame(w, h);

    // lineSize
    frame->linesize.push_back(w);
    frame->linesize.push_back(w * 0.5);
    frame->linesize.push_back(w * 0.5);

    // data
    frame->data.push_back(buffer);
    frame->data.push_back(buffer + w * h);
    frame->data.push_back(buffer + int(w * h * 1.25));

    return frame;
}

unsigned char *ShowFrame::createYUV(int w, int h, int y, int u, int v)
{
    int size = w * h * 1.5;
    unsigned char * buffer = new unsigned char[size];

    int ySize = w * h;
    int uSize = w * h * 0.25;
    int vSize = w * h * 0.25;

    memset(buffer,                 y, ySize);
    memset(buffer + ySize,         u, uSize);
    memset(buffer + ySize + uSize, v, vSize);

    return buffer;
}
