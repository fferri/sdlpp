#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <SDL.h>

#include <set>

#include "Surface.h"
#include "Window.h"

class ControlsManager;

class Control
{
private:
    SDL_Rect rect;
    int zIndex;

    Control *parent;
    std::set<Control *> children;

    Control *grabbingMouseControl;

    bool needsRedraw;

protected:
    Surface canvas;

public:
    Control(SDL_Rect rect);
    virtual ~Control();

    bool operator<(const Control& rhs) const;

    void addChild(Control *control);
    void removeChild(Control *control);
    Control * childAt(int x, int y);
    Control * getParent();
    Control * getRoot();

    void grabMouse();
    void releaseMouse();

    virtual bool acceptsKeyboardFocus() const;

    virtual void onKeyboardEvent(SDL_KeyboardEvent& event);
    virtual void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    virtual void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    virtual void onMouseWheelEvent(SDL_MouseWheelEvent& event);

    void setRect(SDL_Rect newRect);
    const SDL_Rect& getRect();
    virtual SDL_Rect getAbsoluteRect();

    virtual Surface& getCanvas();

    virtual bool shouldRedraw();
    virtual void redraw();
    virtual void resetRedrawFlag();

    virtual void render(const Window& window);
    virtual void renderChildren(const Window& window);
};

#endif // CONTROL_H_INCLUDED
