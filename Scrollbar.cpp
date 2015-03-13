#include "Scrollbar.h"
#include "Logger.h"

Scrollbar::Scrollbar(SDL_Rect rect)
    : Control(rect)
{
    bg = {30, 40, 0, 255};
    fg = {30, 140, 200, 255};
    fo = {230, 240, 240, 255};
    contentSize = 0;
    pos = 0.0;
    mouseDown = false;

    paint();
}

Scrollbar::~Scrollbar()
{
}

int Scrollbar::getHandleSize()
{
    int h = getLongSize();
    if(contentSize <= h) return h;
    else return h * h / contentSize;
}

int Scrollbar::getHandlePos()
{
    return int((getLongSize() - getHandleSize()) * pos);
}

int Scrollbar::getLongSize()
{
    SDL_Rect r = getRect();
    return std::max(r.w, r.h);
}

bool Scrollbar::isHorizontal()
{
    SDL_Rect r = getRect();
    return r.w > r.h;
}

void Scrollbar::paint()
{
    const SDL_Rect& r = getRect();

    canvas.fill(bg);

    int p = getHandlePos(), sz = getHandleSize();

    if(isHorizontal())
        canvas.fillRect(p, 0, sz, r.h, fg);
    else
        canvas.fillRect(0, p, r.w, sz, fg);
}

bool Scrollbar::acceptsKeyboardFocus() const
{
    return true;
}

void Scrollbar::setContentSize(int sz)
{
    contentSize = sz;
    paint();
}

void Scrollbar::setPos(double p)
{
    if(p > 1.0) pos = 1.0;
    else if(p < 0.0) pos = 0.0;
    else pos = p;
    paint();
    callback(pos);
}

void Scrollbar::setCallback(boost::function<void(double)> f)
{
    callback = f;
}

void Scrollbar::onMouseMotionEvent(SDL_MouseMotionEvent& event)
{
    if(!mouseDown) return;
    double incr = 1.0 / double(getLongSize() - getHandleSize());
    setPos(pos + (isHorizontal() ? event.xrel : event.yrel) * incr);
}

void Scrollbar::onMouseButtonEvent(SDL_MouseButtonEvent& event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button == 1)
    {
        mouseDown = true;
        grabMouse();
    }
    if(event.type == SDL_MOUSEBUTTONUP && event.button == 1)
    {
        mouseDown = false;
        releaseMouse();
    }
}

void Scrollbar::onKeyboardEvent(SDL_KeyboardEvent& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.keysym.sym)
        {
        case SDLK_UP:
            setPos(pos - 0.1);
            break;
        case SDLK_DOWN:
            setPos(pos + 0.1);
            break;
        }
    }
}

