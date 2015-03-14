#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class System
{
protected:
    bool shutdown;
    bool verbose;
    std::string basePath;

public:
    System();
    virtual ~System();
    virtual void init();
    virtual void cleanup();
    void requestShutdown();
    void processPendingEvents();
    void dispatchEvent(SDL_Event& event);
    void run();
    long ticks();
    void clear();

    virtual void onDropEvent(SDL_DropEvent& event);
    virtual void onKeyboardEvent(SDL_KeyboardEvent& event);
    virtual void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    virtual void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    virtual void onMouseWheelEvent(SDL_MouseWheelEvent& event);
    virtual void onWindowEvent(SDL_WindowEvent& event);
    virtual void onQuitEvent(SDL_QuitEvent& event);
    virtual void onUserEvent(SDL_UserEvent& event);

    void pushUserEvent(SDL_UserEvent& event);

    virtual void loop();
};

#endif // SYSTEM_H_INCLUDED
