#ifndef SCROLLBAR_H_INCLUDED
#define SCROLLBAR_H_INCLUDED

#include <SDL.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "Control.h"

class Scrollbar : public Control
{
public:
    enum UIPart
    {
        None,
        Upper,
        Handle,
        Lower
    };
protected:
    SDL_Color bg, fg, fo;

    int contentSize;
    double pos;
    UIPart mouseDown;
    UIPart mouseHover;

    int getHandleSize();
    int getHandlePos();
    int getLongSize();
    bool isHorizontal();

    boost::function<void(double)> callback;

public:
    Scrollbar(SDL_Rect rect);
    virtual ~Scrollbar();

    UIPart partAt(int x, int y);

    void paint();

    bool acceptsKeyboardFocus() const;

    void setContentSize(int sz);
    void setPos(double p);

    void setCallback(boost::function<void(double)> f);

    void onMouseMotionEvent(SDL_MouseMotionEvent event);
    void onMouseButtonEvent(SDL_MouseButtonEvent event);
    void onKeyboardEvent(SDL_KeyboardEvent event);
    void onWindowEvent(SDL_WindowEvent event);
};

#endif // SCROLLBAR_H_INCLUDED
