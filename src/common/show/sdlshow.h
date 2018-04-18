#ifndef SDLSHOW_H
#define SDLSHOW_H

#include <QObject>
#include <SDL.h>
#include "showbase.h"
#include <QWidget>
#include <QMutex>

class SDLShow : public ShowBase
{
public:
    SDLShow(QWidget * parent);

    void show(ShowFrame * frame);

    void repaint();

private:

    void init(QWidget *parent);

    void initTexture(int w, int h);

    SDL_Rect getWindowsRect();

    bool globalInit();

private:

    SDL_Window   * m_window;
    SDL_Renderer * m_renderer;
    SDL_Texture  * m_texture;

    QMutex         m_mutex;

    int            m_textureWidth;
    int            m_textureHeight;
};

#endif // SDLSHOW_H
