#include "Button.h"
#include "Logger.h"

Button::Button(SDL_Rect rect, std::string text, const Font& font)
    : Control(rect),
      bg({30, 40, 0, 255}),
      fg({30, 140, 200, 255}),
      fo({230, 240, 240, 255}),
      font(font),
      surfText(font, text.c_str(), fo)
{
    mouseDown = false;
    mouseHover = false;
}

Button::~Button()
{
}

void Button::paint()
{
    const SDL_Rect& r = getRect();

    canvas.fill(bg);

    canvas.fillRect(0, 0, r.w, r.h, fg);

    canvas.blit(surfText, (mouseDown ? 1 : 0) + r.w / 2 - surfText.getWidth() / 2, (mouseDown ? 1 : 0) + r.h / 2 - surfText.getHeight() / 2);

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

void Button::onMouseButtonEvent(SDL_MouseButtonEvent event)
{
    Window *window = Window::fromID(event.windowID);

    if(event.type == SDL_MOUSEBUTTONDOWN && event.button == 1)
    {
        mouseDown = true;
        grabMouse();
        if(window) window->grabMouse();
        repaint();
    }
    if(event.type == SDL_MOUSEBUTTONUP && event.button == 1)
    {
        mouseDown = false;
        releaseMouse();
        if(window) window->releaseMouse();
        if(callback && event.x >= 0 && event.y >= 0 && event.x < getWidth() && event.y < getHeight())
            callback();
        repaint();
    }
}

void Button::onKeyboardEvent(SDL_KeyboardEvent event)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.keysym.sym)
        {
        }
    }
}

void Button::onWindowEvent(SDL_WindowEvent event)
{
    switch(event.event)
    {
    case SDL_WINDOWEVENT_ENTER:
        mouseHover = true;
        repaint();
        break;
    case SDL_WINDOWEVENT_LEAVE:
        mouseHover = false;
        repaint();
        break;
    }
}

