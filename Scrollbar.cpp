#include "Scrollbar.h"
#include "Logger.h"

Scrollbar::Scrollbar(SDL_Rect rect)
    : Control(rect),
      bg({30, 40, 0, 255}),
      fg({30, 140, 200, 255}),
      fo({230, 240, 240, 255}),
      contentSize(0),
      pos(0.0),
      mouseDown(None),
      mouseHover(None)
{
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
    const SDL_Rect& r = getRect();
    return std::max(r.w, r.h);
}

bool Scrollbar::isHorizontal()
{
    const SDL_Rect& r = getRect();
    return r.w > r.h;
}

Scrollbar::UIPart Scrollbar::partAt(int x, int y)
{
    const SDL_Rect& r = getRect();
    int hp = getHandlePos(), hs = getHandleSize(), ss = r.w, ls = r.h;

    if(isHorizontal())
    {
        std::swap(x, y);
        std::swap(ss, ls);
    }

    if(x < 0 || x >= ss) return None;
    if(y < 0) return None;
    if(y < hp) return Upper;
    if(y < (hp + hs)) return Handle;
    if(y < ls) return Lower;
    return None;
}

void Scrollbar::paint()
{
    const SDL_Rect& r = getRect();

    canvas.fill(bg);

    int p = getHandlePos(), sz = getHandleSize();

    bool h = isHorizontal();
    SDL_Rect hr = {h ? p : 0, h ? 0 : p, h ? sz : r.w, h ? r.h : sz};
    canvas.fillRect(hr.x, hr.y, hr.w, hr.h, mouseDown == Handle ? fo : fg);

    if(mouseHover == Handle)
        canvas.drawRect(hr.x, hr.y, hr.w, hr.h, fo);
}

bool Scrollbar::acceptsKeyboardFocus() const
{
    return true;
}

void Scrollbar::setContentSize(int sz)
{
    contentSize = sz;
    repaint();
}

void Scrollbar::setPos(double p)
{
    if(p > 1.0) pos = 1.0;
    else if(p < 0.0) pos = 0.0;
    else pos = p;
    repaint();
    callback(pos);
}

void Scrollbar::setCallback(boost::function<void(double)> f)
{
    callback = f;
}

void Scrollbar::onMouseMotionEvent(SDL_MouseMotionEvent event)
{
    const SDL_Rect& r = getRect();
    UIPart oldMouseHover = mouseHover;
    mouseHover = partAt(event.x - r.x, event.y - r.y);
    if(oldMouseHover != mouseHover)
    {
        repaint();
    }

    if(mouseDown != Handle) return;

    double incr = 1.0 / double(getLongSize() - getHandleSize());
    setPos(pos + (isHorizontal() ? event.xrel : event.yrel) * incr);
}

void Scrollbar::onMouseButtonEvent(SDL_MouseButtonEvent event)
{
    Window *window = Window::fromID(event.windowID);

    UIPart oldMouseDown = mouseDown;

    if(event.type == SDL_MOUSEBUTTONDOWN && event.button == 1)
    {
        const SDL_Rect& r = getRect();
        mouseDown = partAt(event.x - r.x, event.y - r.y);
        if(mouseDown == Handle)
        {
            grabMouse();
            if(window) window->grabMouse();
        }
    }
    if(event.type == SDL_MOUSEBUTTONUP && event.button == 1)
    {
        mouseDown = None;
        releaseMouse();
        if(window) window->releaseMouse();
    }

    if(mouseDown != oldMouseDown)
    {
        repaint();
    }
}

void Scrollbar::onKeyboardEvent(SDL_KeyboardEvent event)
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

void Scrollbar::onWindowEvent(SDL_WindowEvent event)
{
    switch(event.event)
    {
    case SDL_WINDOWEVENT_ENTER:
        break;
    case SDL_WINDOWEVENT_LEAVE:
        mouseHover = None;
        repaint();
        break;
    }
}

