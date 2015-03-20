#ifndef SCROLLBAR2_H_INCLUDED
#define SCROLLBAR2_H_INCLUDED

#include <SDL.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "Control.h"

class Scrollbar2 : public Control
{
public:
    enum UIPart
    {
        None,
        Upper,
        HandleUpper,
        Handle,
        HandleLower,
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
    void computeHandleSizeAndPos();

    // state variables:
    double pos1, pos2;

    // mouse state variables:
    UIPart mouseDown;
    UIPart mouseHover;

    // click callback:
    boost::function<void(double,double)> callback;

public:
    Scrollbar2(SDL_Rect rect);
    virtual ~Scrollbar2();

    UIPart partAt(int x, int y);

    void paint();

    bool acceptsKeyboardFocus() const;

    void setPos(double p1, double p2);

    void setCallback(boost::function<void(double,double)> f);

    void onMouseMotionEvent(SDL_MouseMotionEvent event);
    void onMouseButtonEvent(SDL_MouseButtonEvent event);
    void onKeyboardEvent(SDL_KeyboardEvent event);
    void onWindowEvent(SDL_WindowEvent event);

    void onResize(int w, int h);
};

#endif // SCROLLBAR2_H_INCLUDED
