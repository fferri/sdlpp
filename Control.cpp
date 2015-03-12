#include "Control.h"
#include "ControlsManager.h"

Control::Control(ControlsManager& controlsManager)
    : controlsManager(controlsManager),
      repaintNeeded(true)
{
}

Control::~Control()
{
}

bool Control::acceptsKeyboardFocus() const
{
    return false;
}

void Control::repaint()
{
    repaintNeeded = true;
}

bool Control::needsRepaint() const
{
    return repaintNeeded;
}

void Control::paint(Surface& s)
{
    repaintNeeded = false;
}

void Control::onKeyboardEvent(SDL_KeyboardEvent& event)
{
}

void Control::onMouseMotionEvent(SDL_MouseMotionEvent& event)
{
}

void Control::onMouseButtonEvent(SDL_MouseButtonEvent& event)
{
}

void Control::onMouseWheelEvent(SDL_MouseWheelEvent& event)
{
}

SDL_Rect Control::getRect()
{
    return controlsManager.getRect(this);
}

int Control::getZ()
{
    return controlsManager.getZ(this);
}

void Control::grabMouse()
{
    controlsManager.grabMouse(this);
}

void Control::releaseMouse()
{
    controlsManager.releaseMouse(this);
}

bool Control::hasFocus()
{
    return controlsManager.hasFocus(this);
}

