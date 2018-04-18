#include "widget.h"
#include <QApplication>

#undef main /* Prevents SDL from overriding main() */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
