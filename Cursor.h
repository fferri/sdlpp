#ifndef CURSOR_H_INCLUDED
#define CURSOR_H_INCLUDED

#include "Surface.h"

class Cursor
{
protected:
    SDL_Cursor *cursor;
public:
    Cursor(SDL_SystemCursor id);
    Cursor(Surface& surface, int hot_x, int hot_y);
    Cursor(const Uint8 *data, const Uint8 *mask, int w, int h, int hot_x, int hot_y);
    virtual ~Cursor();
    void set();
    static void redraw();
    static void show();
    static void hide();

    static Cursor ARROW;
    static Cursor IBEAM;
    static Cursor WAIT;
    static Cursor CROSSHAIR;
    static Cursor WAITARROW;
    static Cursor SIZENWSE;
    static Cursor SIZENESW;
    static Cursor SIZEWE;
    static Cursor SIZENS;
    static Cursor SIZEALL;
    static Cursor NO;
    static Cursor HAND;
};

#endif // CURSOR_H_INCLUDED
