#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RTree.h"

class Control
{
public:
    SDL_Rect rect;
    int z;
};

class System
{
protected:
    bool shutdown;
    bool verbose;
    std::string basePath;

    RTree<Control *, float, 2> controlsRTree;
    std::map<Control *, SDL_Rect> controlsRects;
public:
    void addControl(Control *control, SDL_Rect rect);
    void removeControl(Control *control);
    std::vector<Control *> controlsAt(float x, float y);

public:
    System();
    virtual ~System();
    virtual void init();
    virtual void cleanup();
    void requestShutdown();
    void pollAndDispatchEvent();
    void dispatchEvent(const SDL_Event& event);
    void run();
    long ticks();
    void clear();

    virtual void onDropEvent(const SDL_DropEvent& event);
    virtual void onKeyboardEvent(const SDL_KeyboardEvent& event);
    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent& event);
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent& event);
    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent& event);
    virtual void onWindowEvent(const SDL_WindowEvent& event);
    virtual void onQuitEvent(const SDL_QuitEvent& event);

    virtual void loop();
};

#endif // SYSTEM_H_INCLUDED
