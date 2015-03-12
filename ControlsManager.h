#ifndef CONTROLSMANAGER_H_INCLUDED
#define CONTROLSMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RTree.h"
#include "Control.h"

class ControlsManager
{
protected:
    RTree<Control *, float, 2> controlsRTree;
    std::map<Control *, SDL_Rect> controlsRects;
    std::map<Control *, int> controlsZ;
    Control *focusedControl;
    Control *grabbingMouseControl;

    bool getMinMaxZ(int& minZ, int& maxZ) const;
    void repackZ();

    Window& window;

public:
    ControlsManager(Window& window);
    virtual ~ControlsManager();

    void add(Control *control, SDL_Rect rect);
    void add(Control *control, SDL_Rect rect, int z);
    void remove(Control *control);
    Control * at(int x, int y);
    void bringToFront(Control *control);
    void sendToBack(Control *control);
    void move(Control *control, SDL_Rect rect);
    SDL_Rect getRect(Control *control);
    int getZ(Control *control);

    virtual void render();
    virtual void paintControl(Control *control, Surface& s) const;

    virtual bool needsRepaint() const;

    virtual void onKeyboardEvent(const SDL_KeyboardEvent& event);
    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent& event);
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent& event);
    virtual void onMouseWheelEvent(const SDL_MouseWheelEvent& event);

    void grabMouse(Control *control);
    void releaseMouse(Control *control);

    bool hasFocus(Control *control);
    void setFocus(Control *control);
};

#endif // CONTROLSMANAGER_H_INCLUDED
