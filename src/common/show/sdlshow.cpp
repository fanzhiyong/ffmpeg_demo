#include "sdlshow.h"
#include <QDebug>
#include <QFile>
#include <Windows.h>

SDLShow::SDLShow(QWidget *parent)
{
    m_window   = NULL;
    m_renderer = NULL;
    m_texture  = NULL;

    m_textureWidth  = 0;
    m_textureHeight = 0;

    init(parent);
}

void SDLShow::init(QWidget *parent)
{
    // init
    if( !globalInit() ) return;

    // create window
    m_window = SDL_CreateWindowFrom((HWND)parent->winId());
    if( m_window == NULL )
    {
        qInfo()<<"SDL_CreateWindow error.";
        return;
    }

    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if( m_renderer == NULL )
    {
        qInfo()<<"SDL_CreateRenderer error.";
        return;
    }
}

void SDLShow::initTexture(int w, int h)
{
    if( w != m_textureWidth || h != m_textureHeight || m_texture == NULL )
    {
        m_textureWidth  = w;
        m_textureHeight = h;

        // create texture
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING,
                                                  m_textureWidth, m_textureHeight);
        if( m_texture == NULL )
        {
            qInfo()<<"SDL_CreateTexture error.";
        }
    }
}

SDL_Rect SDLShow::getWindowsRect()
{
    int w = 0, h = 0;
    SDL_GetWindowSize(m_window, &w, &h);
    SDL_Rect rt;
    rt.x = 0, rt.y = 0, rt.w = w, rt.h = h;
    return rt;
}

bool SDLShow::globalInit()
{
    static bool inited = false;
    if( inited ) return true;

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if( result != 0 )
    {
        qInfo()<<"SDL_Init : "<<result;
        return false;
    }
    else
    {
        inited = true;
        return true;
    }
}


void SDLShow::show(ShowFrame * frame)
{
    if( frame == NULL || frame->data.size() != 3 || frame->linesize.size() != 3 )
    {
        return;
    }

    initTexture(frame->w, frame->h);

    m_mutex.lock();
    // rect
    SDL_Rect rt = getWindowsRect();
    SDL_UpdateYUVTexture(m_texture, NULL,
                        frame->data[0], frame->linesize[0],
                        frame->data[1], frame->linesize[1],
                        frame->data[2], frame->linesize[2]);
    // clear
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, &rt);
    SDL_RenderPresent(m_renderer);
    m_mutex.unlock();
}

void SDLShow::repaint()
{
    m_mutex.lock();

    SDL_Rect rt = getWindowsRect();
    // clear
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, &rt);
    SDL_RenderPresent(m_renderer);

    m_mutex.unlock();
}

void SDLShow::reset()
{
    // create
    int w = 128;
    int h = 128;
    unsigned char * buffer = ShowFrame::createYUV(w, h, 0, 0x80, 0x80);
    ShowFrame * frame = ShowFrame::crate(w, h, buffer);

    // show
    show(frame);

    // release
    delete frame;
    delete [] buffer;
}
