#ifndef PARTVIEW_H_INCLUDED
#define PARTVIEW_H_INCLUDED

#include "Window.h"
#include "Surface.h"
#include "PartModel.h"

class PartView
{
private:
    Surface bg_tile, data, outline;
    const PartModel& model;
    SDL_Rect rect;
    SDL_Color bg_color, bg_lines, fg_lines, data_bg, empty;

    float y_min, y_max, y_offset;
    TimeStamp x_min, x_max, x_offset;

public:
    PartView(const PartModel& model);
    void updateBackground();
    void updateData();
    void updateOutline();
    void draw(const Window& window);
};

#endif // PARTVIEW_H_INCLUDED
