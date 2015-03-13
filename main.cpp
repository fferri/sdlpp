#include "System.h"
#include "Surface.h"
#include "Logger.h"
#include "ControlsManager.h"
#include "Scrollbar.h"
#include "Viewport.h"
#include "DummyControl.h"

#include <cmath>
#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class App : public System
{
private:
    Window window;
    ControlsManager cm;
    
    Scrollbar scrollh, scrollv;
    SDL_Rect scrollhRect, scrollvRect;
    
    DummyControl dummy;
    SDL_Rect dummyRect;
    
    Viewport viewport;
    SDL_Rect viewportRect;
public:
    App();
    virtual ~App();
    void onKeyboardEvent(SDL_KeyboardEvent& event);
    void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    void onMouseWheelEvent(SDL_MouseWheelEvent& event);
    void onWindowEvent(SDL_WindowEvent& event);
    void loop();
};

App::App()
    : window("Hello, SDL world!", 640, 480),
      cm(window),
      scrollh(cm), scrollv(cm),
      scrollhRect({0, 460, 620, 20}), scrollvRect({620, 0, 20, 460}),
      dummy(cm),
      dummyRect({0, 0, 1000, 1000}),
      viewport(cm, dummy, dummyRect),
      viewportRect({0, 0, 620, 460})
{
    cm.add(&scrollh, scrollhRect);
    scrollh.setContentSize(dummyRect.w);

    cm.add(&scrollv, scrollvRect);
    scrollv.setContentSize(dummyRect.h);

    cm.add(&viewport, viewportRect);

    scrollh.setCallback(boost::bind(&Viewport::setX, &viewport, _1));
    scrollv.setCallback(boost::bind(&Viewport::setY, &viewport, _1));
}

App::~App()
{
}

void App::onKeyboardEvent(SDL_KeyboardEvent& event)
{
    cm.onKeyboardEvent(event);

    if(event.type == SDL_KEYDOWN)
    {
        switch(event.keysym.sym)
        {
        case SDLK_ESCAPE:
            requestShutdown();
            break;
        }
    }
}

void App::onMouseMotionEvent(SDL_MouseMotionEvent& event)
{
    cm.onMouseMotionEvent(event);
}

void App::onMouseButtonEvent(SDL_MouseButtonEvent& event)
{
    cm.onMouseButtonEvent(event);
}

void App::onMouseWheelEvent(SDL_MouseWheelEvent& event)
{
    cm.onMouseWheelEvent(event);
}

void App::onWindowEvent(SDL_WindowEvent& event)
{
    std::string eventName = "?";
#define gkjhgk(x) case x: eventName = #x; break;
    switch(event.event)
    {
    gkjhgk(SDL_WINDOWEVENT_SHOWN)
    gkjhgk(SDL_WINDOWEVENT_HIDDEN)
    gkjhgk(SDL_WINDOWEVENT_EXPOSED)
    gkjhgk(SDL_WINDOWEVENT_MOVED)
    gkjhgk(SDL_WINDOWEVENT_RESIZED)
    gkjhgk(SDL_WINDOWEVENT_MINIMIZED)
    gkjhgk(SDL_WINDOWEVENT_MAXIMIZED)
    gkjhgk(SDL_WINDOWEVENT_RESTORED)
    gkjhgk(SDL_WINDOWEVENT_ENTER)
    gkjhgk(SDL_WINDOWEVENT_LEAVE)
    gkjhgk(SDL_WINDOWEVENT_FOCUS_GAINED)
    gkjhgk(SDL_WINDOWEVENT_FOCUS_LOST)
    gkjhgk(SDL_WINDOWEVENT_CLOSE)
    }
    //LOG(INFO) << "WindowEvent: " << eventName << ", windowID=" << (int)event.windowID << ", data1=" << (int)event.data1 << ", data2=" << (int)event.data2 << "\n";
}

void App::loop()
{
    if(cm.needsRepaint())
    {
        window.clear();
        cm.render();
        window.swapBuffer();
    }
}

int main(int argc, char **argv)
{
    SET_LOG_LEVEL(DEBUG);

    App app;
    app.run();
}

