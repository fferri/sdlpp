#include "Control.h"

Control::Control()
{
}

Control::~Control()
{
}

bool Control::acceptsKeyboardFocus() const
{
    return false;
}

void Control::paint(Surface& s)
{
}

void Control::onKeyboardEvent(const SDL_KeyboardEvent& event)
{
}

void Control::onMouseMotionEvent(const SDL_MouseMotionEvent& event)
{
}

void Control::onMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
}

void Control::onMouseWheelEvent(const SDL_MouseWheelEvent& event)
{
}

