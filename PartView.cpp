#include "PartView.h"

PartView::PartView(const PartModel& model)
    : model(model),
      noteh(5),
      bg_tile(16 * noteh, noteh),
      data(256 * noteh, 64 * noteh),
      outline(128 * noteh, 64 * noteh)
{
    bg_color = {20, 20, 20, 255};
    bg_lines = {60, 60, 60, 255};
    fg_lines = {160, 160, 160, 255};
    data_bg = {0, 0, 0, 0};
    empty = {0, 0, 0, 0};

    zoomx = 1.0f;

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

    for(EventMap::const_iterator it = model.begin(); it != model.end(); ++it)
    {
        int x = it->first * zoomx;
        int y = 0;
        switch(it->second.getType(0)) {
            case 'f':
                y = data.getHeight() - (int)(noteh * it->second.get(0).f);
                break;
            case 'i':
                y = data.getHeight() - noteh * it->second.get(0).i;
                break;
            default:
                continue;
        }
        int w = 5 * noteh;
        int h = noteh;
        data.drawRect(x, y, w, h, fg_lines);
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
    for(int y = 0; y < (s.getHeight() - bg_tile.getHeight()); y += bg_tile.getHeight())
        for(int x = 0; x < (s.getWidth() - bg_tile.getWidth()); x += bg_tile.getWidth())
            s.blit(bg_tile, x, y);
    s.blit(data, 0, 0);
    s.blit(outline, 0, 0);
    s.render(window, 10, 10);
}

