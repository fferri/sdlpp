#include "Control.h"
#include "Logger.h"

Control::Control(SDL_Rect rect)
    : rect(rect),
      parent(NULL),
      grabbingMouseControl(NULL),
      underMouseControl(NULL),
      canvas(rect.w, rect.h),
      needsRepaint(true),
      needsRerender(true)
{
}

Control::~Control()
{
}

void Control::addChild(Control *control)
{
    if(!control)
    {
        LOG(ERROR) << "Control::addChild(NULL)\n";
        return;
    }

    for(Controls::iterator it = children.begin(); it != children.end(); ++it)
    {
        if(*it == control)
        {
            LOG(WARN) << "Control::addChild(" << control << "): already added\n";
            return;
        }
    }

    children.push_back(control);
    rerender();

    if(control->parent)
    {
        LOG(WARN) << "Control::addChild(" << control << "): control has already another parent (" << control->parent << ")\n";
    }
    else
    {
        control->parent = this;
    }
}

void Control::removeChild(Control *control)
{
    if(!control)
    {
        return;
    }

    for(Controls::iterator it = children.begin(); it != children.end(); )
    {
        if(*it == control)
        {
            it = children.erase(it);
            rerender();
        }
        else
        {
            ++it;
        }
    }

    if(control->parent != this)
    {
        LOG(WARN) << "Control::removeChild(" << control << "): control has another parent (" << control->parent << ")\n";
    }
    else
    {
        control->parent = NULL;
    }
}

Control * Control::childAt(int x, int y)
{
    if(parent)
    {
        SDL_Rect pr = parent->getAbsoluteRect();
        x -= pr.x;
        y -= pr.y;
    }
    x -= rect.x;
    y -= rect.y;
    for(Controls::reverse_iterator it = children.rbegin(); it != children.rend(); ++it)
    {
        Control *c = *it;
        const SDL_Rect& r = c->getRect();
        if(x >= r.x && y >= r.y && x < (r.x + r.w) && y < (r.y + r.h))
        {
            return c;
        }
    }

    return NULL;
}

Control * Control::getParent()
{
    return parent;
}

Control * Control::getRoot()
{
    Control *root = this;
    
    while(root->parent) root = root->parent;

    return root;
}

void Control::grabMouse()
{
    Control *root = getRoot();

    if(root->grabbingMouseControl)
    {
        LOG(DEBUG) << "Control::grabMouse: mouse was already grabbed\n";
    }

    root->grabbingMouseControl = this;
}

void Control::releaseMouse()
{
    Control *root = getRoot();

    if(!root->grabbingMouseControl)
    {
        LOG(DEBUG) << "Control::releaseMouse: mouse was not grabbed\n";
    }

    root->grabbingMouseControl = NULL;
}

bool Control::acceptsKeyboardFocus() const
{
    return false;
}

void Control::onKeyboardEvent(SDL_KeyboardEvent event)
{
}

template <typename T>
void Control::translateMouseEventCoords(T& mouseEvent)
{
    mouseEvent.x -= rect.x;
    mouseEvent.y -= rect.y;
}

void Control::onMouseMotionEvent(SDL_MouseMotionEvent event)
{
    if(grabbingMouseControl)
    {
        grabbingMouseControl->translateMouseEventCoords(event);
        grabbingMouseControl->onMouseMotionEvent(event);
        return;
    }

    Control *c = childAt(event.x, event.y);
    if(c != underMouseControl)
    {
        if(underMouseControl)
        {
            SDL_WindowEvent leave;
            leave.type = SDL_WINDOWEVENT;
            leave.timestamp = event.timestamp;
            leave.windowID = event.windowID;
            leave.event = SDL_WINDOWEVENT_LEAVE;
            underMouseControl->onWindowEvent(leave);
        }

        if(c)
        {
            SDL_WindowEvent enter;
            enter.type = SDL_WINDOWEVENT;
            enter.timestamp = event.timestamp;
            enter.windowID = event.windowID;
            enter.event = SDL_WINDOWEVENT_ENTER;
            c->onWindowEvent(enter);
        }

        underMouseControl = c;
    }

    if(c)
    {
        c->translateMouseEventCoords(event);
        c->onMouseMotionEvent(event);
    }
}

void Control::onMouseButtonEvent(SDL_MouseButtonEvent event)
{
    Control *c = grabbingMouseControl ? grabbingMouseControl : childAt(event.x, event.y);
    if(c)
    {
        c->translateMouseEventCoords(event);
        c->onMouseButtonEvent(event);
    }
}

void Control::onMouseWheelEvent(SDL_MouseWheelEvent event)
{
    Control *c = grabbingMouseControl ? grabbingMouseControl : childAt(event.x, event.y);
    if(c)
    {
        c->translateMouseEventCoords(event);
        c->onMouseWheelEvent(event);
    }
}

void Control::onWindowEvent(SDL_WindowEvent event)
{
    if(underMouseControl && event.event == SDL_WINDOWEVENT_LEAVE)
    {
        SDL_WindowEvent leave;
        leave.type = SDL_WINDOWEVENT;
        leave.timestamp = event.timestamp;
        leave.windowID = event.windowID;
        leave.event = SDL_WINDOWEVENT_LEAVE;
        underMouseControl->onWindowEvent(leave);

        underMouseControl = NULL;
    }
}

void Control::setRect(SDL_Rect newRect)
{
    SDL_Rect oldRect = rect;
    rect = newRect;
    canvas.resize(newRect.w, newRect.h, true);
    if(oldRect.x != newRect.x || oldRect.y != newRect.y)
        onMove(newRect.x, newRect.y);
    if(oldRect.w != newRect.w || oldRect.h != newRect.h)
        onMove(newRect.w, newRect.h);
    repaint();
}

const SDL_Rect& Control::getRect()
{
    return rect;
}

int Control::getX()
{
    return rect.x;
}

int Control::getY()
{
    return rect.y;
}

int Control::getWidth()
{
    return rect.w;
}

int Control::getHeight()
{
    return rect.h;
}

void Control::onResize(int width, int height)
{
}

void Control::onMove(int x, int y)
{
}

SDL_Rect Control::getAbsoluteRect()
{
    SDL_Rect r = rect;
    if(parent)
    {
        SDL_Rect pr = parent->getAbsoluteRect();
        r.x += pr.x;
        r.y += pr.y;
    }
    return r;
}

Surface& Control::getCanvas()
{
    return canvas;
}

bool Control::shouldRerender()
{
    if(shouldRepaint()) return true;

    if(needsRerender) return true;

    for(Controls::iterator it = children.begin(); it != children.end(); ++it)
    {
        if((*it)->shouldRerender()) return true;
    }

    return false;
}

void Control::rerender()
{
    needsRerender = true;
}

void Control::resetRerenderFlag()
{
    needsRerender = false;
}

void Control::render(const Window& window)
{
    if(shouldRepaint())
    {
        paint();
        resetRepaintFlag();
    }

    SDL_Rect ar = getAbsoluteRect();
    canvas.render(window, ar.x, ar.y);
    resetRerenderFlag();

    renderChildren(window);
}

void Control::renderChildren(const Window& window)
{
    for(Controls::iterator it = children.begin(); it != children.end(); ++it)
    {
        (*it)->render(window);
    }
}

bool Control::shouldRepaint()
{
    return needsRepaint;
}

void Control::repaint()
{
    needsRepaint = true;
}

void Control::resetRepaintFlag()
{
    needsRepaint = false;
}

void Control::paint()
{
    LOG(DEBUG) << "called\n";
}

