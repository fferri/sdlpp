#include "Scrollbar2.h"
#include "Cursor.h"
#include "Logger.h"

Scrollbar2::Scrollbar2(SDL_Rect rect)
    : Control(rect),
      bg({30, 40, 0, 255}),
      fg({30, 140, 200, 255}),
      fo({230, 240, 240, 255}),
      pos1(0.0),
      pos2(1.0),
      mouseDown(None),
      mouseHover(None)
{
    computeAllMetrics();
}

Scrollbar2::~Scrollbar2()
{
}

void Scrollbar2::computeAllMetrics()
{
    computeSizeAndOrientation();
}

void Scrollbar2::computeSizeAndOrientation()
{
    const SDL_Rect& r = getRect();
    horizontal = r.w > r.h;
    longSize = horizontal ? r.w : r.h;
    shortSize = horizontal ? r.h : r.w;
    computeHandleSizeAndPos();
}

void Scrollbar2::computeHandleSizeAndPos()
{
    int p1 = (longSize - shortSize) * pos1;
    int p2 = shortSize + (longSize - shortSize) * pos2;

    handleSize = p2 - p1 + 1;
    handlePos = p1;
}

Scrollbar2::UIPart Scrollbar2::partAt(int x, int y)
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
    if(y < (handlePos + shortSize / 3)) return HandleUpper;
    if(y < (handlePos + handleSize - shortSize / 3)) return Handle;
    if(y < (handlePos + handleSize)) return HandleLower;
    if(y < ls) return Lower;
    return None;
}

void Scrollbar2::paint()
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

    if(mouseHover == Handle || mouseHover == HandleLower || mouseHover == HandleUpper
       || mouseDown == Handle || mouseDown == HandleLower || mouseDown == HandleUpper)
        canvas.drawRect(hr.x, hr.y, hr.w, hr.h, fo);
}

bool Scrollbar2::acceptsKeyboardFocus() const
{
    return true;
}

void Scrollbar2::setPos(double p1, double p2)
{
    pos1 = std::min(1.0, std::max(0.0, p1));
    pos2 = std::max(pos1, std::min(1.0, std::max(0.0, p2)));
    computeHandleSizeAndPos();
    repaint();
    if(callback)
        callback(pos1, pos2);
}

void Scrollbar2::setCallback(boost::function<void(double,double)> f)
{
    callback = f;
}

void Scrollbar2::onMouseMotionEvent(SDL_MouseMotionEvent event)
{
    UIPart oldMouseHover = mouseHover;
    mouseHover = partAt(event.x, event.y);
    if(oldMouseHover != mouseHover)
    {
        repaint();
        if(mouseHover == HandleLower || mouseHover == HandleUpper)
            (horizontal ? Cursor::SIZEWE : Cursor::SIZENS).set();
        else
            Cursor::ARROW.set();
    }

    if(mouseDown != Handle && mouseDown != HandleLower && mouseDown != HandleUpper) return;

    double incr = 1.0 / double(longSize - shortSize);
    int dp = horizontal ? event.xrel : event.yrel;

    if(mouseDown == Handle)
    {
        double pos1_ = pos1 + dp * incr;
        double pos2_ = pos2 + dp * incr;
        if(pos1_ >= 0 && pos1_ <= 1 && pos2_ >= 0 && pos2_ <= 1 && pos1_ < pos2_)
            setPos(pos1_, pos2_);
    }
    else if(mouseDown == HandleUpper)
    {
        double pos1_ = pos1 + dp * incr;
        if(pos1_ >= 0 && pos1_ <= 1 && pos1_ < pos2)
            setPos(pos1_, pos2);
    }
    else if(mouseDown == HandleLower)
    {
        double pos2_ = pos2 + dp * incr;
        if(pos2_ >= 0 && pos2_ <= 1 && pos1 < pos2_)
            setPos(pos1, pos2_);
    }
}

void Scrollbar2::onMouseButtonEvent(SDL_MouseButtonEvent event)
{
    Window *window = Window::fromID(event.windowID);

    UIPart oldMouseDown = mouseDown;

    if(event.type == SDL_MOUSEBUTTONDOWN && event.button == 1)
    {
        mouseDown = partAt(event.x, event.y);
        if(mouseDown == Handle || mouseDown == HandleLower || mouseDown == HandleUpper)
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

void Scrollbar2::onKeyboardEvent(SDL_KeyboardEvent event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.keysym.sym)
        {
        case SDLK_UP:
            break;
        case SDLK_DOWN:
            break;
        }
    }
}

void Scrollbar2::onWindowEvent(SDL_WindowEvent event)
{
    switch(event.event)
    {
    case SDL_WINDOWEVENT_ENTER:
        break;
    case SDL_WINDOWEVENT_LEAVE:
        mouseHover = None;
        repaint();
        Cursor::ARROW.set();
        break;
    }
}

void Scrollbar2::onResize(int w, int h)
{
    computeAllMetrics();
    repaint();
}

