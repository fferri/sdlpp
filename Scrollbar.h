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

    // UI metrics:
    bool horizontal;
    int handleSize;
    int handlePos;
    int longSize;
    int shortSize;

    void computeAllMetrics();
    void computeSizeAndOrientation();
    void computeHandlePos();
    void computeHandleSize();

    // state variables:
    int contentSize;
    double pos;

    // mouse state variables:
    UIPart mouseDown;
    UIPart mouseHover;

    // click callback:
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

    void onResize(int w, int h);
};

#endif // SCROLLBAR_H_INCLUDED
