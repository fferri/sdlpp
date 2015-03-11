#include "PartView.h"

PartView::PartView(const PartModel& model)
    : model(model),
      bg_tile(16, 12),
      data(256, 64),
      outline(128, 64)
{
    bg_color = {20, 20, 20, 255};
    bg_lines = {40, 40, 40, 255};
    fg_lines = {160, 160, 160, 255};
    data_bg = {0, 0, 0, 0};
    empty = {0, 0, 0, 0};

    y_min = 0.0f;
    y_max = 127.0f;
    y_offset = 0.0f;
    x_min = 0;
    x_max = 32;
    x_offset = 0;

    rect = {30, 30, 400, 200};

    updateBackground();
    updateData();
    updateOutline();
}

void PartView::updateBackground()
{
    bg_tile.fill(bg_color);
    bg_tile.fillRect(0, 0, bg_tile.getWidth(), 1, bg_lines);
    bg_tile.fillRect(0, 0, 1, bg_tile.getHeight(), bg_lines);
}

void PartView::updateData()
{
    data.fill(data_bg);

    SDL_Rect n = {0, 0, 20, 1};

    for(EventMap::const_iterator it = model.begin(); it != model.end(); ++it)
    {
        n.x = it->first + x_offset;
        if(n.x < x_min || n.x > x_max) continue;
        n.y = 0;
        switch(it->second.getType(0)) {
            case 'f':
                n.y = (int)it->second.get(0).f;
                break;
            case 'i':
                n.y = it->second.get(0).i;
                break;
            default:
                continue;
        }
        n.y = n.y + y_offset;
        if(n.y < y_min || n.y > y_max) continue;

        // scale to screen
        n.x = (n.x - x_min) * rect.w / (x_max - x_min);
        n.y = (n.y - y_min) * rect.h / (y_max - y_min);
        n.h = rect.h / (y_max - y_min);
        if(n.h < 1) n.h = 1;
        data.drawRect(n.x, n.y, n.w, n.h, fg_lines);
    }
}

void PartView::updateOutline()
{
    outline.fill(empty);
    outline.drawRect(0, 0, outline.getWidth(), outline.getHeight(), fg_lines);
}

void PartView::draw(const Window& window)
{
    Surface s(outline.getWidth(), outline.getHeight());
    for(int y = 0; y < s.getHeight(); y += bg_tile.getHeight())
        for(int x = 0; x < s.getWidth(); x += bg_tile.getWidth())
            s.blit(bg_tile, x, y);
    s.blit(data, 0, 0);
    s.blit(outline, 0, 0);
    s.render(window, rect.x, rect.y);
}

