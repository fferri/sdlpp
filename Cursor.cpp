#include "Cursor.h"
#include "Logger.h"

Cursor::Cursor(SDL_SystemCursor id)
{
    cursor = SDL_CreateSystemCursor(id);

    if(!cursor)
    {
        LOG(FATAL) << "SDL_CreateSystemCursor: " << SDL_GetError() << "\n";
        exit(1);
    }
}

Cursor::Cursor(Surface& surface, int hot_x, int hot_y)
{
    cursor = SDL_CreateColorCursor(surface.surface, hot_x, hot_y);

    if(!cursor)
    {
        LOG(FATAL) << "SDL_CreateColorCursor: " << SDL_GetError() << "\n";
        exit(1);
    }
}

Cursor::Cursor(const Uint8 *data, const Uint8 *mask, int w, int h, int hot_x, int hot_y)
{
    cursor = SDL_CreateCursor(data, mask, w, h, hot_x, hot_y);

    if(!cursor)
    {
        LOG(FATAL) << "SDL_CreateCursor: " << SDL_GetError() << "\n";
        exit(1);
    }
}

Cursor::~Cursor()
{
    SDL_FreeCursor(cursor);
}

void Cursor::set()
{
    SDL_SetCursor(cursor);
}

void Cursor::redraw()
{
    SDL_SetCursor(NULL);
}

void Cursor::show()
{
    SDL_ShowCursor(1);
}

void Cursor::hide()
{
    SDL_ShowCursor(0);
}

Cursor Cursor::ARROW(SDL_SYSTEM_CURSOR_ARROW);
Cursor Cursor::IBEAM(SDL_SYSTEM_CURSOR_IBEAM);
Cursor Cursor::WAIT(SDL_SYSTEM_CURSOR_WAIT);
Cursor Cursor::CROSSHAIR(SDL_SYSTEM_CURSOR_CROSSHAIR);
Cursor Cursor::WAITARROW(SDL_SYSTEM_CURSOR_WAITARROW);
Cursor Cursor::SIZENWSE(SDL_SYSTEM_CURSOR_SIZENWSE);
Cursor Cursor::SIZENESW(SDL_SYSTEM_CURSOR_SIZENESW);
Cursor Cursor::SIZEWE(SDL_SYSTEM_CURSOR_SIZEWE);
Cursor Cursor::SIZENS(SDL_SYSTEM_CURSOR_SIZENS);
Cursor Cursor::SIZEALL(SDL_SYSTEM_CURSOR_SIZEALL);
Cursor Cursor::NO(SDL_SYSTEM_CURSOR_NO);
Cursor Cursor::HAND(SDL_SYSTEM_CURSOR_HAND);

