#include "Viewport.h"

Viewport::Viewport(ControlsManager& controlsManager, Control& child, SDL_Rect childRect)
    : Control(controlsManager),
      child(child), childRect(childRect),
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
    SDL_Rect r = getRect();
    x = (childRect.w > r.w) ? int((childRect.w - r.w) * posX) : 0;
    y = (childRect.h > r.h) ? int((childRect.h - r.h) * posY) : 0;
}

void Viewport::set(double x, double y)
{
    posX = (x < 0 ? 0 : (x > 1 ? 1 : x));
    posY = (y < 0 ? 0 : (y > 1 ? 1 : y));
    repaint();
}

void Viewport::setX(double x)
{
    posX = (x < 0 ? 0 : (x > 1 ? 1 : x));
    repaint();
}

void Viewport::setY(double y)
{
    posY = (y < 0 ? 0 : (y > 1 ? 1 : y));
    repaint();
}

bool Viewport::acceptsKeyboardFocus() const
{
    return child.acceptsKeyboardFocus();
}

void Viewport::repaint()
{
}

bool Viewport::needsRepaint()
{
    return child.needsRepaint();
}

void Viewport::paint(Surface& s)
{
    SDL_Rect r = getRect();
    Surface s1(childRect.w, childRect.h);
    child.paint(s1);
    int ox, oy;
    getTranslation(ox, oy);
    s.blit(s1, ox, oy, r.w, r.h, 0, 0);
}

void Viewport::onKeyboardEvent(SDL_KeyboardEvent& event)
{
    child.onKeyboardEvent(event);
}

void Viewport::onMouseMotionEvent(SDL_MouseMotionEvent& event)
{
    translateMouseEvent(event);
    child.onMouseMotionEvent(event);
}

void Viewport::onMouseButtonEvent(SDL_MouseButtonEvent& event)
{
    translateMouseEvent(event);
    child.onMouseButtonEvent(event);
}

void Viewport::onMouseWheelEvent(SDL_MouseWheelEvent& event)
{
    translateMouseEvent(event);
    child.onMouseWheelEvent(event);
}

