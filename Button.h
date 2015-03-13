#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SDL.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "Control.h"
#include "Font.h"

class Button : public Control
{
protected:
    SDL_Color bg, fg, fo;

    bool mouseDown;
    bool mouseHover;

    boost::function<void(void)> callback;

    Font *font;

public:
    Button(SDL_Rect rect, std::string text, Font *font);
    virtual ~Button();

    void paint();

    bool acceptsKeyboardFocus() const;

    void setCallback(boost::function<void(void)> f);

    void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    void onKeyboardEvent(SDL_KeyboardEvent& event);
    void onWindowEvent(SDL_WindowEvent& event);
};

#endif // BUTTON_H_INCLUDED
