#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SDL.h>

class Window
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    void createAll(const char *title, int x, int y, int w, int h);
    void createWindow(const char *title, int x, int y, int w, int h);
    void createRenderer();

public:
    Window(const char *title, int x, int y, int w, int h);
    Window(const char *title, int w, int h);
    virtual ~Window();

    virtual void draw();

    SDL_Window * getWindow() const;
    SDL_Renderer * getRenderer() const;
    void clear();
    void swapBuffer();
    void grabMouse();
    void releaseMouse();

    virtual void onKeyboardEvent(SDL_KeyboardEvent& event);
    virtual void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    virtual void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    virtual void onMouseWheelEvent(SDL_MouseWheelEvent& event);
    virtual void onWindowEvent(SDL_WindowEvent& event);
    virtual void onUserEvent(SDL_UserEvent& event);

    Uint32 getID();

    static Window * fromID(Uint32 windowID);
    static Window * fromPtr(SDL_Window *window);
};

#endif // WINDOW_H_INCLUDED
