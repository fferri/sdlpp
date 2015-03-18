#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <SDL.h>

#include <vector>

#include "Surface.h"
#include "Window.h"

class Control;
class ControlsManager;

typedef std::vector<Control *> Controls;

class Control
{
private:
    SDL_Rect rect;

    Control *parent;
    Controls children;

    Control *grabbingMouseControl;
    Control *underMouseControl;

    bool needsRerender;
    bool needsRepaint;

protected:
    Surface canvas;

public:
    Control(SDL_Rect rect);
    virtual ~Control();

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
    virtual void onWindowEvent(SDL_WindowEvent& event);

    void setRect(SDL_Rect newRect);
    const SDL_Rect& getRect();
    virtual SDL_Rect getAbsoluteRect();

    virtual Surface& getCanvas();

    virtual bool shouldRerender();
    virtual void rerender();
    virtual void resetRerenderFlag();

    virtual void render(const Window& window);
    virtual void renderChildren(const Window& window);

    virtual bool shouldRepaint();
    virtual void repaint();
    virtual void resetRepaintFlag();

    virtual void paint();
};

#endif // CONTROL_H_INCLUDED
