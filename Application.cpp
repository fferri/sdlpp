#include "Application.h"
#include "Window.h"
#include "Logger.h"

Application::Application()
    : EVENT_TYPE_TIMER(0)
{
    shutdown = false;
    verbose = true;

    init();
}

Application::~Application()
{
    cleanup();
}

void Application::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        LOG(FATAL) << "SDL_Init: " << SDL_GetError() << "\n";
        exit(1);
    }

    int IMG_Init_Flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if((IMG_Init(IMG_Init_Flags) & IMG_Init_Flags) != IMG_Init_Flags)
    {
        LOG(FATAL) << "IMG_Init: " << IMG_GetError() << "\n";
        exit(1);
    }

    if(TTF_Init() != 0)
    {
        LOG(FATAL) << "TTF_Init: " << TTF_GetError() << "\n";
        exit(1);
    }

    char *basePath_ = SDL_GetBasePath();
    if(basePath_)
    {
        basePath = basePath_;
        SDL_free(basePath_);
        LOG(TRACE) << "basePath is '" << basePath.c_str() << "'\n";
    }

    SDL_EventState(SDL_QUIT, SDL_ENABLE);
    SDL_EventState(SDL_WINDOWEVENT, SDL_ENABLE);
    SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

    EVENT_TYPE_TIMER = SDL_RegisterEvents(1);
}

void Application::cleanup()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Application::requestShutdown()
{
    shutdown = true;
}

void Application::dispatchEvent(SDL_Event& event)
{
    switch(event.type)
    {
    case SDL_DROPFILE:
        onDropEvent(event.drop);
        break;
    case SDL_KEYUP:
    case SDL_KEYDOWN:
        onKeyboardEvent(event.key);
        break;
    case SDL_TEXTINPUT:
        onTextInputEvent(event.text);
        break;
    case SDL_MOUSEMOTION:
        onMouseMotionEvent(event.motion);
        break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        onMouseButtonEvent(event.button);
        break;
    case SDL_MOUSEWHEEL:
        onMouseWheelEvent(event.wheel);
        break;
    case SDL_WINDOWEVENT:
        onWindowEvent(event.window);
        break;
    case SDL_FINGERDOWN:
    case SDL_FINGERUP:
    case SDL_FINGERMOTION:
        onTouchFingerEvent(event.tfinger);
        break;
    case SDL_MULTIGESTURE:
        onMultiGestureEvent(event.mgesture);
        break;
    case SDL_DOLLARGESTURE:
        onDollarGestureEvent(event.dgesture);
        break;
    case SDL_QUIT:
        onQuitEvent(event.quit);
        break;
    case SDL_USEREVENT:
        onUserEvent(event.user);
        break;
    default:
        LOG(TRACE) << "Application::dispatchEvent({type=" << event.type << "})\n";
        break;
    }
}

void Application::processPendingEvents()
{
    SDL_Event event;
    if(SDL_WaitEvent(&event))
    {
        dispatchEvent(event);
    }
    else
    {
        LOG(ERROR) << "Application::run(): SDL_WaitEvent: " << SDL_GetError() << "\n";
        SDL_Delay(80);
    }
}

void Application::run()
{
    while(!shutdown)
    {
        loop();
        processPendingEvents();
    }
}

long Application::ticks()
{
    return SDL_GetTicks();
}

void Application::onDropEvent(SDL_DropEvent& event)
{
}

void Application::onKeyboardEvent(SDL_KeyboardEvent& event)
{
    Window *win = Window::fromID(event.windowID);
    if(win)
        win->onKeyboardEvent(event);
}

void Application::onTextInputEvent(SDL_TextInputEvent& event)
{
    Window *win = Window::fromID(event.windowID);
    if(win)
        win->onTextInputEvent(event);
}

void Application::onMouseMotionEvent(SDL_MouseMotionEvent& event)
{
    Window *win = Window::fromID(event.windowID);
    if(win)
        win->onMouseMotionEvent(event);
}

void Application::onMouseButtonEvent(SDL_MouseButtonEvent& event)
{
    Window *win = Window::fromID(event.windowID);
    if(win)
        win->onMouseButtonEvent(event);
}

void Application::onMouseWheelEvent(SDL_MouseWheelEvent& event)
{
    Window *win = Window::fromID(event.windowID);
    if(win)
        win->onMouseWheelEvent(event);
}

void Application::onWindowEvent(SDL_WindowEvent& event)
{
    Window *win = Window::fromID(event.windowID);
    if(win)
        win->onWindowEvent(event);
}

void Application::onTouchFingerEvent(SDL_TouchFingerEvent& event)
{
}

void Application::onMultiGestureEvent(SDL_MultiGestureEvent& event)
{
}

void Application::onDollarGestureEvent(SDL_DollarGestureEvent& event)
{
}

void Application::onQuitEvent(SDL_QuitEvent& event)
{
    requestShutdown();
}

void Application::onUserEvent(SDL_UserEvent& event)
{
    LOG(TRACE) << "Application::onUserEvent({timestamp=" << event.timestamp << ", windowID=" << event.windowID << ", code=" << event.code << ", data1=" << event.data1 << ", data2=" << event.data2 << "})\n";

    Window *win = Window::fromID(event.windowID);
    if(win)
        win->onUserEvent(event);
}

void Application::pushUserEvent(SDL_UserEvent& event)
{
    LOG(TRACE) << "Application::pushUserEvent({type=" << event.type << "})\n";

    SDL_Event e;
    e.type = SDL_USEREVENT;
    e.user = event;
    int r = SDL_PushEvent(&e);
    if(r > 0) return;
    if(r == 0)
    {
        LOG(WARN) << "Application::pushUserEvent(): event was filtered\n";
    }
    if(r < 0)
    {
        LOG(ERROR) << "Application::pushUserEvent(): SDL_PushEvent: " << SDL_GetError() << "\n";
    }
}

Uint32 Application::getEventTypeTimer()
{
    return EVENT_TYPE_TIMER;
}

void Application::loop()
{
}

