#ifndef VIEWPORT_H_INCLUDED
#define VIEWPORT_H_INCLUDED

#include "Control.h"
#include "ControlsManager.h"

class Viewport : public Control
{
protected:
    Control& child;
    double posX, posY;

    template <class E>
    void translateMouseEvent(E& e);

    SDL_Rect childRect;

public:
    Viewport(ControlsManager& controlsManager, Control& child, SDL_Rect childRect);
    virtual ~Viewport();

    void getTranslation(int& x, int& y);

    void set(double x, double y);
    void setX(double x);
    void setY(double y);

    bool acceptsKeyboardFocus() const;

    void repaint();
    bool needsRepaint();
    void paint(Surface& s);

    void onKeyboardEvent(SDL_KeyboardEvent& event);
    void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    void onMouseWheelEvent(SDL_MouseWheelEvent& event);
};

#endif // VIEWPORT_H_INCLUDED
