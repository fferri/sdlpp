#include "Window.h"
#include "Logger.h"

Window::Window(const char *title, int x, int y, int w, int h)
{
    createAll(title, x, y, w, h);
}

Window::Window(const char *title, int w, int h)
{
    createAll(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h);
}

Window::~Window()
{
}

void Window::draw()
{
}

void Window::createAll(const char *title, int x, int y, int w, int h)
{
    createWindow(title, x, y, w, h);
    createRenderer();
}

void Window::createWindow(const char *title, int x, int y, int w, int h)
{
    window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(!window)
    {
        LOG(FATAL) << "SDL_CreateWindow: " << SDL_GetError() << "\n";
        exit(1);
    }

    SDL_SetWindowData(window, "Window*", this);
}

void Window::createRenderer()
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer)
    {
        LOG(FATAL) << "SDL_CreateRenderer: " << SDL_GetError() << "\n";
        exit(1);
    }
}

SDL_Window * Window::getWindow() const
{
    return window;
}

SDL_Renderer * Window::getRenderer() const
{
    return renderer;
}

void Window::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
}

void Window::swapBuffer()
{
    SDL_RenderPresent(renderer);
}

void Window::grabMouse()
{
    SDL_SetWindowGrab(window, SDL_TRUE);
}

void Window::releaseMouse()
{
    SDL_SetWindowGrab(window, SDL_FALSE);
}

void Window::onKeyboardEvent(SDL_KeyboardEvent& event)
{
}

void Window::onMouseMotionEvent(SDL_MouseMotionEvent& event)
{
}

void Window::onMouseButtonEvent(SDL_MouseButtonEvent& event)
{
}

void Window::onMouseWheelEvent(SDL_MouseWheelEvent& event)
{
}

void Window::onWindowEvent(SDL_WindowEvent& event)
{
}

void Window::onUserEvent(SDL_UserEvent& event)
{
}

Window * Window::fromID(Uint32 windowID)
{
    SDL_Window *win = SDL_GetWindowFromID(windowID);

    if(!win) return NULL;

    return reinterpret_cast<Window *>(SDL_GetWindowData(win, "Window*"));
}
