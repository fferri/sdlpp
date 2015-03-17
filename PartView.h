#ifndef PARTVIEW_H_INCLUDED
#define PARTVIEW_H_INCLUDED

#include "Control.h"
#include "PartModel.h"

class PartView : public Control
{
private:
    const PartModel& model;
    SDL_Color bg_color, bg_lines, fg_lines, data_bg, empty;

    float y_min, y_max, y_offset;
    TimeStamp x_min, x_max, x_offset;

public:
    PartView(SDL_Rect rect, const PartModel& model);
    void paint();
};

#endif // PARTVIEW_H_INCLUDED
