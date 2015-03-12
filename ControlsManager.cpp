#include "ControlsManager.h"
#include "Logger.h"

ControlsManager::ControlsManager()
{
}

ControlsManager::~ControlsManager()
{
}

bool ControlsManager::getMinMaxZ(int& minZ, int& maxZ) const
{
    bool ret = false;

    if(controlsZOrder.size() > 0)
    {
        for(std::map<Control *, int>::const_iterator it = controlsZOrder.begin(); it != controlsZOrder.end(); ++it)
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
    std::map<int, Control *> inv;
    for(std::map<Control *, int>::const_iterator it = controlsZOrder.begin(); it != controlsZOrder.end(); ++it)
    {
        inv[it->second] = it->first;
    }

    if(inv.size() != controlsZOrder.size())
    {
        LOG(ERROR) << "ControlsManager: cannot repack controlsZOrder (duplicate Zs?)\n";
        return;
    }

    controlsZOrder.clear();
    int z = 0;
    for(std::map<int, Control *>::const_iterator it = inv.begin(); it != inv.end(); ++it)
    {
        controlsZOrder[it->second] = ++z;
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
    controlsZOrder[control] = z;
}

void ControlsManager::remove(Control *control)
{
    SDL_Rect& rect = controlsRects[control];
    float a_min[2] = {float(rect.x), float(rect.y)};
    float a_max[2] = {float(rect.x + rect.w), float(rect.y + rect.h)};
    controlsRTree.Remove(a_min, a_max, control);
    controlsRects.erase(control);
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
    int z = controlsZOrder[ret];
    for(std::vector<Control *>::iterator it = v.begin(); it != v.end(); ++it)
    {
        if(controlsZOrder[*it] > z)
        {
            ret = *it;
            z = controlsZOrder[ret];
        }
    }
    return ret;
}

void ControlsManager::bringToFront(Control *control)
{
    int minZ = 1, maxZ = 1;
    getMinMaxZ(minZ, maxZ);
    controlsZOrder[control] = maxZ + 1;
    repackZ(); // TODO: call this once in a while instead of every time
}

void ControlsManager::sendToBack(Control *control)
{
    int minZ = 1, maxZ = 1;
    getMinMaxZ(minZ, maxZ);
    controlsZOrder[control] = minZ - 1;
    repackZ(); // TODO: call this once in a while instead of every time
}

void ControlsManager::move(Control *control, SDL_Rect rect)
{
    int z = controlsZOrder[control];
    remove(control);
    add(control, rect, z);
}

SDL_Rect ControlsManager::getRect(Control *control) const
{
    return controlsRects.at(control);
}

int ControlsManager::getZ(Control *control) const
{
    return controlsZOrder.at(control);
}

void ControlsManager::onKeyboardEvent(const SDL_KeyboardEvent& event)
{
    if(focusedControl)
        focusedControl->onKeyboardEvent(event);
}

void ControlsManager::onMouseMotionEvent(const SDL_MouseMotionEvent& event)
{
    Control *control = at(event.x, event.y);
    if(control)
        control->onMouseMotionEvent(event);
}

void ControlsManager::onMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
    Control *control = at(event.x, event.y);
    if(control)
        control->onMouseButtonEvent(event);
}

void ControlsManager::onMouseWheelEvent(const SDL_MouseWheelEvent& event)
{
    Control *control = at(event.x, event.y);
    if(control)
        control->onMouseWheelEvent(event);
}

