#include "window.h"
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>
Window::Window()
{
    QRect screenRect = QApplication::desktop()->screenGeometry();
    this->winWidth=screenRect.width();
    this->winHeight=screenRect.height();
}
