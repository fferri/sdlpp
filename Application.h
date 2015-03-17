#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Application
{
protected:
    bool shutdown;
    bool verbose;
    std::string basePath;

    virtual void init();
    virtual void cleanup();
    void processPendingEvents();
    void dispatchEvent(SDL_Event& event);

    Uint32 EVENT_TYPE_TIMER;

public:
    Application();
    virtual ~Application();
    void requestShutdown();
    void run();

    long ticks();

    virtual void onDropEvent(SDL_DropEvent& event);
    virtual void onKeyboardEvent(SDL_KeyboardEvent& event);
    virtual void onTextInputEvent(SDL_TextInputEvent& event);
    virtual void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    virtual void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    virtual void onMouseWheelEvent(SDL_MouseWheelEvent& event);
    virtual void onWindowEvent(SDL_WindowEvent& event);
    virtual void onTouchFingerEvent(SDL_TouchFingerEvent& event);
    virtual void onMultiGestureEvent(SDL_MultiGestureEvent& event);
    virtual void onDollarGestureEvent(SDL_DollarGestureEvent& event);
    virtual void onQuitEvent(SDL_QuitEvent& event);
    virtual void onUserEvent(SDL_UserEvent& event);

    void pushUserEvent(SDL_UserEvent& event);

    Uint32 getEventTypeTimer();

    virtual void loop();
};

#endif // APPLICATION_H_INCLUDED
