#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <SDL_ttf.h>

class Font
{
private:
    TTF_Font *font;
public:
    Font(const char *filename, int size);
    virtual ~Font();
    TTF_Font * getFont() const;
};

#endif // FONT_H_INCLUDED
