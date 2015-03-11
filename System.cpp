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
    case SDL_QUIT:
        shutdown = true;
        break;
    case SDL_KEYUP:
        onKeyUp(event);
        break;
    case SDL_KEYDOWN:
        onKeyDown(event);
        break;
    }
}

void System::pollAndDispatchEvent()
{
    SDL_Event event;
    if(SDL_PollEvent(&event))
    {
        dispatchEvent(event);
    }
}

void System::run()
{
    LOG(TRACE) << "System: run()\n";

    while(!shutdown)
    {
        pollAndDispatchEvent();
        loop();
    }
}

long System::ticks()
{
    return SDL_GetTicks();
}

void System::onKeyUp(const SDL_Event& event)
{
}

void System::onKeyDown(const SDL_Event& event)
{
}

void System::loop()
{
}

