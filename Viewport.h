#ifndef VIEWPORT_H_INCLUDED
#define VIEWPORT_H_INCLUDED

#include "Control.h"

class Viewport : public Control
{
protected:
    Control& child;
    double posX, posY;

    template <class E>
    void translateMouseEvent(E& e);

public:
    Viewport(SDL_Rect rect, Control& child);
    virtual ~Viewport();

    void getTranslation(int& x, int& y);

    void set(double x, double y);
    void setX(double x);
    void setY(double y);

    bool acceptsKeyboardFocus() const;

    bool shouldRedraw();    

    void render(const Window& window);

    void onKeyboardEvent(SDL_KeyboardEvent& event);
    void onMouseMotionEvent(SDL_MouseMotionEvent& event);
    void onMouseButtonEvent(SDL_MouseButtonEvent& event);
    void onMouseWheelEvent(SDL_MouseWheelEvent& event);
};

#endif // VIEWPORT_H_INCLUDED
