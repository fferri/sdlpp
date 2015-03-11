#ifndef PARTVIEW_H_INCLUDED
#define PARTVIEW_H_INCLUDED

#include "System.h"
#include "PartModel.h"

class PartView
{
private:
    SDL_Surface *background, *data, *outline;
    PartModel model;
    SDL_Rect rect;
public:
    void updateBackground();
    void updateData();
    void updateOutline();
    void draw();
};

#endif // PARTVIEW_H_INCLUDED
