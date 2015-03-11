#include "Font.h"
#include "Logger.h"

Font::Font(const char *filename, int size)
{
    font = TTF_OpenFont(filename, size);

    if(!font)
    {
        LOG(FATAL) << "TTF_OpenFont: " << TTF_GetError() << "\n";
        exit(1);
    }
}

Font::~Font()
{
    TTF_CloseFont(font);
}

TTF_Font * Font::getFont() const
{
    return font;
}

