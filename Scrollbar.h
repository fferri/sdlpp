#ifndef SCROLLBAR_H_INCLUDED
#define SCROLLBAR_H_INCLUDED

#include <SDL.h>

#include "Control.h"
#include "ControlsManager.h"

class Scrollbar : public Control
{
protected:
    SDL_Color bg, fg, fo;

    int contentSize;
    double pos;
    bool mouseDown;

    int getHandleSize();
    int getHandlePos();
    int getLongSize();
    bool isHorizontal();

public:
    Scrollbar(ControlsManager& cm);
    virtual ~Scrollbar();

    void paint(Surface& s);

    bool acceptsKeyboardFocus() const;

    void setContentSize(int sz);
    void setPos(double p);

    void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    void onKeyboardEvent(SDL_KeyboardEvent& event);
};

#endif // SCROLLBAR_H_INCLUDED
