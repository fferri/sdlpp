#ifndef PARTVIEW_H_INCLUDED
#define PARTVIEW_H_INCLUDED

#include "System.h"
#include "Surface.h"
#include "PartModel.h"

class PartView
{
private:
    const int noteh;
    Surface bg_tile, data, outline;
    const PartModel& model;
    SDL_Rect rect;
    SDL_Color bg_color, bg_lines, fg_lines, data_bg, empty;
    float zoomx;
public:
    PartView(const PartModel& model);
    void updateBackground();
    void updateData();
    void updateOutline();
    void draw(const Window& window);
};

#endif // PARTVIEW_H_INCLUDED
