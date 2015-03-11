#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <string>

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
    void pollAndDispatchEvent();
    void dispatchEvent(const SDL_Event& event);
    void run();
    long ticks();
    void clear();

    virtual void onKeyUp(const SDL_Event& event);
    virtual void onKeyDown(const SDL_Event& event);

    virtual void loop();
};

#endif // SYSTEM_H_INCLUDED
