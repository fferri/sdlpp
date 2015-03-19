#include "Viewport.h"
#include "Logger.h"

Viewport::Viewport(SDL_Rect rect, Control& child)
    : Control(rect),
      child(child),
      posX(0.0), posY(0.0)
{
}

Viewport::~Viewport()
{
}

template <class E>
void Viewport::translateMouseEvent(E& e)
{
    int tx, ty;
    getTranslation(tx, ty);
    e.x += tx;
    e.y += ty;
}

void Viewport::getTranslation(int& x, int& y)
{
    const SDL_Rect& r = getRect();
    const SDL_Rect& childRect = child.getRect();
    x = (childRect.w > r.w) ? int((childRect.w - r.w) * posX) : 0;
    y = (childRect.h > r.h) ? int((childRect.h - r.h) * posY) : 0;
}

void Viewport::set(double x, double y)
{
    posX = (x < 0 ? 0 : (x > 1 ? 1 : x));
    posY = (y < 0 ? 0 : (y > 1 ? 1 : y));
    rerender();
}

void Viewport::setX(double x)
{
    posX = (x < 0 ? 0 : (x > 1 ? 1 : x));
    rerender();
}

void Viewport::setY(double y)
{
    posY = (y < 0 ? 0 : (y > 1 ? 1 : y));
    rerender();
}

bool Viewport::acceptsKeyboardFocus() const
{
    return child.acceptsKeyboardFocus();
}

bool Viewport::shouldRerender()
{
    return Control::shouldRerender() || child.shouldRerender();
}

void Viewport::render(const Window& window)
{
    if(child.shouldRepaint())
    {
        child.paint();
        child.resetRepaintFlag();
    }
    Surface& childCanvas = child.getCanvas();
    SDL_Rect ar = getAbsoluteRect();
    int ox, oy;
    getTranslation(ox, oy);
    childCanvas.render(window, ox, oy, ar.w, ar.h, ar.x, ar.y, ar.w, ar.h);
    resetRerenderFlag();
    resetRepaintFlag();
    child.resetRerenderFlag();
    child.resetRepaintFlag();
}

void Viewport::onKeyboardEvent(SDL_KeyboardEvent event)
{
    child.onKeyboardEvent(event);
}

void Viewport::onMouseMotionEvent(SDL_MouseMotionEvent event)
{
    translateMouseEvent(event);
    child.onMouseMotionEvent(event);
}

void Viewport::onMouseButtonEvent(SDL_MouseButtonEvent event)
{
    translateMouseEvent(event);
    child.onMouseButtonEvent(event);
}

void Viewport::onMouseWheelEvent(SDL_MouseWheelEvent event)
{
    translateMouseEvent(event);
    child.onMouseWheelEvent(event);
}

