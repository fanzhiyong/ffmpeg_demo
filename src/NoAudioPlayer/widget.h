#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "show/sdlshow.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    ~Widget();

private:

    Ui::Widget *ui;

    SDLShow * m_show;
};

#endif // WIDGET_H
