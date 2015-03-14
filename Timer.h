#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

class Timer
{
protected:
    SDL_TimerID id;

    virtual Uint32 callback(Uint32 interval);

public:
    Timer();
    virtual ~Timer();

    void start(Uint32 interval);
    bool cancel();

private:
    static Uint32 callbackStatic(Uint32 interval, void *data);
};

class CallbackTimer : public Timer
{
public:
    typedef boost::function<void(void)> Callback;

    void setCallback(Callback c);

protected:
    Callback callbackFunction;

    Uint32 callback(Uint32 interval);
};

#endif // TIMER_H_INCLUDED
