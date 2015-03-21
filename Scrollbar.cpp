#include "Scrollbar.h"
#include "Logger.h"

Scrollbar::Scrollbar(SDL_Rect rect)
    : Control(rect),
      bg({30, 40, 0, 255}),
      fg({30, 140, 200, 255}),
      fo({230, 240, 240, 255}),
      contentSize(1),
      pos(0.0),
      mouseDown(None),
      mouseHover(None)
{
    computeAllMetrics();
}

Scrollbar::~Scrollbar()
{
}

void Scrollbar::computeAllMetrics()
{
    computeSizeAndOrientation();
}

void Scrollbar::computeSizeAndOrientation()
{
    const SDL_Rect& r = getRect();
    horizontal = r.w > r.h;
    longSize = horizontal ? r.w : r.h;
    shortSize = horizontal ? r.h : r.w;
    computeHandleSize();
}

void Scrollbar::computeHandlePos()
{
    handlePos = int((longSize - handleSize) * pos);
}

void Scrollbar::computeHandleSize()
{
    handleSize = longSize * longSize / contentSize;
    if(handleSize < shortSize)
        handleSize = shortSize;
    if(handleSize > longSize)
        handleSize = longSize;
    computeHandlePos();
}

Scrollbar::UIPart Scrollbar::partAt(int x, int y)
{
    int ss = getWidth(), ls = getHeight();

    if(horizontal)
    {
        std::swap(x, y);
        std::swap(ss, ls);
    }

    if(x < 0 || x >= ss) return None;
    if(y < 0) return None;
    if(y < handlePos) return Upper;
    if(y < (handlePos + handleSize)) return Handle;
    if(y < ls) return Lower;
    return None;
}

void Scrollbar::paint()
{
    const SDL_Rect& r = getRect();

    canvas.fill(bg);

    SDL_Rect hr = {
        horizontal ? handlePos : 0,
        horizontal ? 0 : handlePos,
        horizontal ? handleSize : r.w,
        horizontal ? r.h : handleSize
    };
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
    computeHandleSize();
    repaint();
}

void Scrollbar::setPos(double p)
{
    if(p > 1.0) pos = 1.0;
    else if(p < 0.0) pos = 0.0;
    else pos = p;
    computeHandlePos();
    repaint();
    if(callback)
        callback(pos);
}

void Scrollbar::setCallback(boost::function<void(double)> f)
{
    callback = f;
}

void Scrollbar::onMouseMotionEvent(SDL_MouseMotionEvent event)
{
    UIPart oldMouseHover = mouseHover;
    mouseHover = partAt(event.x, event.y);
    if(oldMouseHover != mouseHover)
    {
        repaint();
    }

    if(mouseDown != Handle) return;

    double incr = 1.0 / double(longSize - handleSize);
    setPos(pos + (horizontal ? event.xrel : event.yrel) * incr);
}

void Scrollbar::onMouseButtonEvent(SDL_MouseButtonEvent event)
{
    Window *window = Window::fromID(event.windowID);

    UIPart oldMouseDown = mouseDown;

    if(event.type == SDL_MOUSEBUTTONDOWN && event.button == 1)
    {
        mouseDown = partAt(event.x, event.y);
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

void Scrollbar::onResize(int w, int h)
{
    Control::onResize(w, h); // resizes canvas
    computeAllMetrics();
    repaint();
}

