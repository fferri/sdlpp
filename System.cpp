#include "System.h"
#include "Logger.h"

System::System()
{
    LOG(TRACE) << "System: constructor\n";

    shutdown = false;
    verbose = true;

    init();
}

System::~System()
{
    LOG(TRACE) << "System: destructor\n";

    cleanup();
}

void System::init()
{
    LOG(TRACE) << "System: init()\n";

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
}

void System::cleanup()
{
    LOG(TRACE) << "System: cleanSystem()\n";

    LOG(TRACE) << "System: IMG_Quit()\n";
    IMG_Quit();

    LOG(TRACE) << "System: TTF_Quit()\n";
    TTF_Quit();

    LOG(TRACE) << "System: SDL_Quit()\n";
    SDL_Quit();
}

void System::requestShutdown()
{
    LOG(TRACE) << "System: requestShutdown()\n";
    shutdown = true;
}

void System::dispatchEvent(const SDL_Event& event)
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
    case SDL_QUIT:
        onQuitEvent(event.quit);
        break;
    }
}

void System::processPendingEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        dispatchEvent(event);
    }
}

void System::run()
{
    LOG(TRACE) << "System: run()\n";

    while(!shutdown)
    {
        processPendingEvents();
        loop();
        SDL_Delay(0);
    }
}

long System::ticks()
{
    return SDL_GetTicks();
}

void System::onDropEvent(const SDL_DropEvent& event)
{
}

void System::onKeyboardEvent(const SDL_KeyboardEvent& event)
{
}

void System::onMouseMotionEvent(const SDL_MouseMotionEvent& event)
{
}

void System::onMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
}

void System::onMouseWheelEvent(const SDL_MouseWheelEvent& event)
{
}

void System::onWindowEvent(const SDL_WindowEvent& event)
{
}

void System::onQuitEvent(const SDL_QuitEvent& event)
{
    requestShutdown();
}

void System::loop()
{
}

