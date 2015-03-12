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

    virtual void onKeyboardEvent(const SDL_KeyboardEvent& event);
    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent& event);
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent& event);
    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent& event);

    SDL_Rect getRect();
    int getZ();
    
    void grabMouse();
    void releaseMouse();
};

#endif // CONTROL_H_INCLUDED
