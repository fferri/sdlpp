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
    paint();
}

void PartView::paint()
{
    canvas.fill(bg_color);

    for(EventMap::const_iterator it = model.begin(); it != model.end(); ++it)
    {
        TimeStamp timestamp = it->first;
        const Event& event = it->second;
        if(event.getType() != "note") continue;
        SDL_Rect n, r;
        n.x = timestamp + x_offset;
        n.y = event.getNote() + event.getFinetune() / 127.0 + y_offset;
        if(n.x < x_min || n.x > x_max) continue;
        if(n.y < y_min || n.y > y_max) continue;
        r = getRect();
        // scale to screen
        n.x = (n.x - x_min) * r.w / (x_max - x_min);
        n.y = (n.y - y_min) * r.h / (y_max - y_min);
        n.w = event.getLength() * r.w / (x_max - x_min);
        if(n.w < 1) n.w = 1;
        n.h = r.h / (y_max - y_min);
        if(n.h < 1) n.h = 1;
        canvas.drawRect(n.x, n.y, n.w, n.h, fg_lines);
    }
}

