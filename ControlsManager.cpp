#include "ControlsManager.h"
#include "Logger.h"

#include <utility>
#include <cassert>

ControlsManager::ControlsManager(Window& window)
    : window(window),
      focusedControl(NULL),
      grabbingMouseControl(NULL)
{
}

ControlsManager::~ControlsManager()
{
}

bool ControlsManager::getMinMaxZ(int& minZ, int& maxZ) const
{
    bool ret = false;

    if(controlsZ.size() > 0)
    {
        for(std::map<Control *, int>::const_iterator it = controlsZ.begin(); it != controlsZ.end(); ++it)
        {
            if(ret)
            {
                minZ = std::min(minZ, it->second);
                maxZ = std::max(maxZ, it->second);
            }
            else
            {
                minZ = it->second;
                maxZ = it->second;
                ret = true;
            }
        }
        ret = true;
    }

    return ret;
}

void ControlsManager::repackZ()
{
    std::multimap<int, Control *> controlsZInv;
    for(std::map<Control *, int>::const_iterator it = controlsZ.begin(); it != controlsZ.end(); ++it)
    {
        controlsZInv.insert(std::make_pair(it->second, it->first));
    }

    assert(controlsZInv.size() == controlsZ.size());

    int z = 0;
    controlsZ.clear();
    for(std::multimap<int, Control *>::const_iterator it = controlsZInv.begin(); it != controlsZInv.end(); ++it)
    {
        controlsZ[it->second] = ++z;
    }
}

void ControlsManager::add(Control *control, SDL_Rect rect)
{
    int minZ = 1, maxZ = 1;
    getMinMaxZ(minZ, maxZ);
    add(control, rect, maxZ + 1);
}

void ControlsManager::add(Control *control, SDL_Rect rect, int z)
{
    if(controlsRects.find(control) != controlsRects.end())
    {
        LOG(ERROR) << "ControlsManager::add(): control " << control << " already added\n";
        return;
    }
    float a_min[2] = {float(rect.x), float(rect.y)};
    float a_max[2] = {float(rect.x + rect.w), float(rect.y + rect.h)};
    controlsRTree.Insert(a_min, a_max, control);
    controlsRects[control] = rect;
    controlsZ.insert(std::make_pair(control, z));
}

void ControlsManager::remove(Control *control)
{
    SDL_Rect& rect = controlsRects[control];
    float a_min[2] = {float(rect.x), float(rect.y)};
    float a_max[2] = {float(rect.x + rect.w), float(rect.y + rect.h)};
    controlsRTree.Remove(a_min, a_max, control);
    controlsRects.erase(control);
    controlsZ.erase(control);
}

bool cb(Control *control, void *data)
{
    std::vector<Control *> *pvector = (std::vector<Control *> *)data;;
    pvector->push_back(control);
    return true;
}

Control * ControlsManager::at(int x, int y)
{
    std::vector<Control *> v;
    float p[2] = {float(x), float(y)};
    controlsRTree.Search(p, p, cb, &v);
    if(v.size() == 1) return v[0];
    if(v.size() < 1) return NULL;
    Control *ret = v[0];
    int maxZ = controlsZ[ret];
    for(std::vector<Control *>::iterator it = v.begin(); it != v.end(); ++it)
    {
        Control *c = *it;
        int z = controlsZ[c];

        if(z > maxZ)
        {
            ret = c;
            maxZ = z;
        }
    }
    return ret;
}

void ControlsManager::bringToFront(Control *control)
{
    int minZ = 1, maxZ = 1;
    getMinMaxZ(minZ, maxZ);
    controlsZ[control] = maxZ + 1;
    repackZ(); // TODO: call this once in a while instead of every time
}

void ControlsManager::sendToBack(Control *control)
{
    int minZ = 1, maxZ = 1;
    getMinMaxZ(minZ, maxZ);
    controlsZ[control] = minZ - 1;
    repackZ(); // TODO: call this once in a while instead of every time
}

void ControlsManager::move(Control *control, SDL_Rect rect)
{
    int z = controlsZ[control];
    remove(control);
    add(control, rect, z);
}

SDL_Rect ControlsManager::getRect(Control *control)
{
    return controlsRects.at(control);
}

int ControlsManager::getZ(Control *control)
{
    return controlsZ.at(control);
}

void ControlsManager::render()
{
    std::multimap<int, Control *> controlsZInv;
    for(std::map<Control *, int>::const_iterator it = controlsZ.begin(); it != controlsZ.end(); ++it)
    {
        controlsZInv.insert(std::make_pair(it->second, it->first));
    }
    for(std::multimap<int, Control *>::const_iterator it = controlsZInv.begin(); it != controlsZInv.end(); ++it)
    {
        Control *control = it->second;
        SDL_Rect& r = controlsRects[control];
        // XXX: don't recreate surface every time!
        Surface s(r.w, r.h);
        paintControl(control, s);
        s.render(window, r.x, r.y);
    }
}

void ControlsManager::paintControl(Control *control, Surface& s) const
{
    control->paint(s);
}

bool ControlsManager::needsRepaint() const
{
    for(std::map<Control *, int>::const_iterator it = controlsZ.begin(); it != controlsZ.end(); ++it)
    {
        if(it->first->needsRepaint())
            return true;
    }
    return false;
}

void ControlsManager::onKeyboardEvent(const SDL_KeyboardEvent& event)
{
    if(event.type == SDL_KEYDOWN && event.keysym.sym == SDLK_TAB)
    {
        // cycle through controls that accept keyboard focus
        std::map<Control *, int>::iterator it = focusedControl ? controlsZ.find(focusedControl) : controlsZ.begin();;
        ++it;
        Control *newFocusedControl = NULL;
        for(int i = 0; i < 2; i++)
        {
            while(newFocusedControl == NULL && it != controlsZ.end())
            {
                if(it->first->acceptsKeyboardFocus())
                    newFocusedControl = it->first;
                ++it;
            }
            it = controlsZ.begin();
        }
        setFocus(newFocusedControl);
        return;
    }

    if(focusedControl)
        focusedControl->onKeyboardEvent(event);
}

void ControlsManager::onMouseMotionEvent(const SDL_MouseMotionEvent& event)
{
    Control *control = grabbingMouseControl ? grabbingMouseControl : at(event.x, event.y);
    if(control)
        control->onMouseMotionEvent(event);
}

void ControlsManager::onMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
    Control *control = grabbingMouseControl ? grabbingMouseControl : at(event.x, event.y);
    if(control)
        control->onMouseButtonEvent(event);
}

void ControlsManager::onMouseWheelEvent(const SDL_MouseWheelEvent& event)
{
    Control *control = grabbingMouseControl ? grabbingMouseControl : at(event.x, event.y);
    if(control)
        control->onMouseWheelEvent(event);
}

void ControlsManager::grabMouse(Control *control)
{
    if(grabbingMouseControl && grabbingMouseControl != control)
    {
        LOG(ERROR) << "ControlsManager::grabMouse(): already grabbed by another control\n";
        return;
    }
    grabbingMouseControl = control;
    window.grabMouse();
}

void ControlsManager::releaseMouse(Control *control)
{
    if(grabbingMouseControl != control)
    {
        LOG(ERROR) << "ControlsManager::releaseMouse(): not grabbed by the releasing control\n";
        return;
    }
    grabbingMouseControl = NULL;
    window.releaseMouse();
}

bool ControlsManager::hasFocus(Control *control)
{
    return control == focusedControl;
}

void ControlsManager::setFocus(Control *control)
{
    if(control == focusedControl) return;

    Control *oldFocusedControl = focusedControl;
    focusedControl = control;

    if(oldFocusedControl)
        oldFocusedControl->repaint();
    if(focusedControl)
        focusedControl->repaint();
}

