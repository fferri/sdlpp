#include "PartView.h"

PartView::PartView(SDL_Rect rect, const PartModel& model)
    : Control(rect),
      model(model),
      bg_color({20, 20, 20, 255}),
      bg_lines({40, 40, 40, 255}),
      fg_lines({160, 160, 160, 255}),
      data_bg({0, 0, 0, 0}),
      empty({0, 0, 0, 0}),
      y_min(0.0f), y_max(127.0f), y_offset(0.0f),
      x_min(0), x_max(384), x_offset(0)
{
}

int PartView::localToScreenX(float localX)
{
    const SDL_Rect& r = getRect();
    float localNX = (localX + x_offset - x_min) / (x_max - x_min);
    return int(r.w * localNX + 0.5);
}

int PartView::localToScreenY(float localY)
{
    const SDL_Rect& r = getRect();
    float localNY = (localY + y_offset - y_min) / (y_max - y_min);
    return int(r.h * localNY + 0.5);
}

float PartView::screenToLocalX(int screenX)
{
    const SDL_Rect& r = getRect();
    float screenNX = screenX / float(r.w);
    return screenNX * (x_max - x_min) + x_min - x_offset;
}

float PartView::screenToLocalY(int screenY)
{
    const SDL_Rect& r = getRect();
    float screenNY = screenY / float(r.h);
    return screenNY * (y_max - y_min) + y_min - y_offset;
}

void PartView::paint()
{
    canvas.fill(bg_color);

    for(EventMap::const_iterator it = model.begin(); it != model.end(); ++it)
    {
        TimeStamp timestamp = it->first;
        const Event& event = it->second;
        if(event.getType() != "note") continue;
        SDL_Rect n;
        float lx = timestamp, ly = event.getNote() + event.getFinetune() / 127.0;
        n.x = localToScreenX(lx);
        n.y = localToScreenY(ly);
        // scale to screen
        n.w = localToScreenX(lx + event.getLength()) - n.x;
        n.h = localToScreenY(1) - localToScreenY(0);
        n.y -= 0.5 * n.h;
        canvas.drawRect(n.x, n.y, n.w, n.h, fg_lines);
    }
}

