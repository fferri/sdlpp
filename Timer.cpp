#include "Timer.h"
#include "Logger.h"

Timer::Timer()
    : id(0)
{
}

Timer::~Timer()
{
    if(id) cancel();
}

void Timer::start(Uint32 interval)
{
    if(id)
    {
        LOG(ERROR) << "Timer::start(): timer already started\n";
    }
    else
    {
        id = SDL_AddTimer(interval, &Timer::callbackStatic, reinterpret_cast<void *>(this));
    }
}

bool Timer::cancel()
{
    if(id)
    {
        return SDL_RemoveTimer(id) == SDL_TRUE;
    }
    else
    {
        LOG(ERROR) << "Timer::cancel(): timer not started\n";
        return false;
    }
}

Uint32 Timer::callbackStatic(Uint32 interval, void *data)
{
    Timer *timer = reinterpret_cast<Timer *>(data);
    return timer->callback(interval);
}

Uint32 Timer::callback(Uint32 interval)
{
    return 0;
}

void CallbackTimer::setCallback(Callback c)
{
    callbackFunction = c;
}

Uint32 CallbackTimer::callback(Uint32 interval)
{
    if(callbackFunction)
    {
        callbackFunction();
        return interval;
    }
    else
    {
        return 0;
    }
}

EventTimer::EventTimer(Application& app_, SDL_UserEvent userEvent_)
    : app(app_), userEvent(userEvent_)
{
    userEvent.type = app.getEventTypeTimer();
}

Uint32 EventTimer::callback(Uint32 interval)
{
    app.pushUserEvent(userEvent);
    return interval;
}

