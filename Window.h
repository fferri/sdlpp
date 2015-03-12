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
    SDL_Window * getWindow() const;
    SDL_Renderer * getRenderer() const;
    void clear();
    void swapBuffer();
    void grabMouse();
    void releaseMouse();
};

#endif // WINDOW_H_INCLUDED
