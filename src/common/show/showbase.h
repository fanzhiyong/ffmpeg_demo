#ifndef SHOWBASE_H
#define SHOWBASE_H

#include "showglobal.h"

class ShowBase
{
public:
    ShowBase();

    ~ShowBase();

    virtual void show(ShowFrame * frame) = 0;

    virtual void repaint() = 0;

    virtual void reset() = 0;
};

#endif // SHOWBASE_H
