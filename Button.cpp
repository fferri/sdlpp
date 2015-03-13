#include "Button.h"
#include "Logger.h"

Button::Button(SDL_Rect rect, std::string text, Font *font)
    : Control(rect)
{
    bg = {30, 40, 0, 255};
    fg = {30, 140, 200, 255};
    fo = {230, 240, 240, 255};

    mouseDown = false;
    mouseHover = false;

    paint();
}

Button::~Button()
{
}

void Button::paint()
{
    const SDL_Rect& r = getRect();

    canvas.fill(bg);

    canvas.fillRect(0, 0, r.w, r.h, fg);

    if(mouseHover)
        canvas.drawRect(0, 0, r.w, r.h, fo);
}

bool Button::acceptsKeyboardFocus() const
{
    return true;
}

void Button::setCallback(boost::function<void(void)> f)
{
    callback = f;
}

void Button::onMouseButtonEvent(SDL_MouseButtonEvent& event)
{
    Window *window = Window::fromID(event.windowID);

    if(event.type == SDL_MOUSEBUTTONDOWN && event.button == 1)
    {
        mouseDown = true;
        grabMouse();
        if(window) window->grabMouse();
    }
    if(event.type == SDL_MOUSEBUTTONUP && event.button == 1)
    {
        mouseDown = false;
        releaseMouse();
        if(window) window->releaseMouse();
        SDL_Rect ar = getAbsoluteRect();
        if(callback && event.x >= ar.x && event.y >= ar.y && event.x < (ar.x + ar.w) && event.y < (ar.y + ar.h))
            callback();
    }
}

void Button::onKeyboardEvent(SDL_KeyboardEvent& event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.keysym.sym)
        {
        }
    }
}

void Button::onWindowEvent(SDL_WindowEvent& event)
{
    switch(event.event)
    {
    case SDL_WINDOWEVENT_ENTER:
        mouseHover = true;
        paint();
        redraw();
        break;
    case SDL_WINDOWEVENT_LEAVE:
        mouseHover = false;
        paint();
        redraw();
        break;
    }
}

