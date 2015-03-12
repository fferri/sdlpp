#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <SDL.h>

#include "Surface.h"

class ControlsManager;

class Control
{
protected:
    ControlsManager& controlsManager;
    bool repaintNeeded;

public:
    Control(ControlsManager& controlsManager);
    virtual ~Control();

    virtual bool acceptsKeyboardFocus() const;

    virtual void repaint();
    virtual bool needsRepaint() const;
    virtual void paint(Surface& s);

    virtual void onKeyboardEvent(SDL_KeyboardEvent& event);
    virtual void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    virtual void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    virtual void onMouseWheelEvent(SDL_MouseWheelEvent& event);

    SDL_Rect getRect();
    int getZ();
    
    void grabMouse();
    void releaseMouse();

    bool hasFocus();
};

#endif // CONTROL_H_INCLUDED
