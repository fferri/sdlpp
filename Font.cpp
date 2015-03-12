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

void Font::setStyle(int style)
{
    TTF_SetFontStyle(font, style);
}

int Font::getStyle()
{
    return TTF_GetFontStyle(font);
}

void Font::setStyleAttributes(bool bold, bool italic, bool underline, bool strikethrough)
{
    if(!bold && !italic && !underline && !strikethrough)
        setStyle(TTF_STYLE_NORMAL);
    else
        setStyle((bold ? TTF_STYLE_BOLD : 0) | (italic ? TTF_STYLE_ITALIC : 0) | (underline ? TTF_STYLE_UNDERLINE : 0) | (strikethrough ? TTF_STYLE_STRIKETHROUGH : 0));
}

void Font::getStyleAttributes(bool& bold, bool& italic, bool& underline, bool& strikethrough)
{
    int s = getStyle();
    bool nm = s != TTF_STYLE_NORMAL;
    bold = nm && (s & TTF_STYLE_BOLD);
    italic = nm && (s & TTF_STYLE_BOLD);
    underline = nm && (s & TTF_STYLE_BOLD);
    strikethrough = nm && (s & TTF_STYLE_BOLD);
}

int Font::getOutline()
{
    return TTF_GetFontOutline(font);
}

void Font::setOutline(int size)
{
    TTF_SetFontOutline(font, size);
}

int Font::getHinting()
{
    return TTF_GetFontHinting(font);
}

void Font::setHinting(int hinting)
{
    /*
        TTF_HINTING_NORMAL
        TTF_HINTING_LIGHT
        TTF_HINTING_MONO
        TTF_HINTING_NONE
     */
    TTF_SetFontHinting(font, hinting);
}

bool Font::isKerningEnabled()
{
    return TTF_GetFontKerning(font);
}

void Font::setKerningEnabled(bool en)
{
    TTF_SetFontKerning(font, en ? 1 : 0);
}

int Font::getHeight()
{
    return TTF_FontHeight(font);
}

int Font::getAscent()
{
    return TTF_FontAscent(font);
}

int Font::getDescent()
{
    return TTF_FontDescent(font);
}

int Font::getLineSkip()
{
    return TTF_FontLineSkip(font);
}

bool Font::isFixedWidth()
{
    return TTF_FontFaceIsFixedWidth(font);
}

char * Font::getFamilyName()
{
    return TTF_FontFaceFamilyName(font);
}

char * Font::getStyleName()
{
    return TTF_FontFaceStyleName(font);
}

bool Font::isGlyphProvided(Uint16 character)
{
    return TTF_GlyphIsProvided(font, character);
}

int Font::getGlyphIndex(Uint16 character)
{
    return TTF_GlyphIsProvided(font, character);
}

bool Font::getGlyphMetrics(Uint16 character, int *minx, int *maxx, int *miny, int *maxy, int *advance)
{
    return 0 == TTF_GlyphMetrics(font, character, minx, maxx, miny, maxy, advance);
}

bool Font::getTextSize(const char *text, int *w, int *h)
{
    return 0 == TTF_SizeText(font, text, w, h);
}

bool Font::getTextSizeUTF8(const char *text, int *w, int *h)
{
    return 0 == TTF_SizeUTF8(font, text, w, h);
}

bool Font::getTextSizeUNICODE(const Uint16 *text, int *w, int *h)
{
    return 0 == TTF_SizeUNICODE(font, text, w, h);
}

SDL_Surface * Font::renderTextSolid(const char *text, SDL_Color color)
{
    return TTF_RenderText_Solid(font, text, color);
}

SDL_Surface * Font::renderTextSolidUTF8(const char *text, SDL_Color color)
{
    return TTF_RenderUTF8_Solid(font, text, color);
}

SDL_Surface * Font::renderTextSolidUNICODE(const Uint16 *text, SDL_Color color)
{
    return TTF_RenderUNICODE_Solid(font, text, color);
}

SDL_Surface * Font::renderGlyphSolid(Uint16 glyph, SDL_Color color)
{
    return TTF_RenderGlyph_Solid(font, glyph, color);
}

SDL_Surface * Font::renderTextShaded(const char *text, SDL_Color color, SDL_Color background)
{
    return TTF_RenderText_Shaded(font, text, color, background);
}

SDL_Surface * Font::renderTextShadedUTF8(const char *text, SDL_Color color, SDL_Color background)
{
    return TTF_RenderUTF8_Shaded(font, text, color, background);
}

SDL_Surface * Font::renderTextShadedUNICODE(const Uint16 *text, SDL_Color color, SDL_Color background)
{
    return TTF_RenderUNICODE_Shaded(font, text, color, background);
}

SDL_Surface * Font::renderGlyphShaded(Uint16 glyph, SDL_Color color, SDL_Color background)
{
    return TTF_RenderGlyph_Shaded(font, glyph, color, background);
}

SDL_Surface * Font::renderTextBlended(const char *text, SDL_Color color)
{
    return TTF_RenderText_Blended(font, text, color);
}

SDL_Surface * Font::renderTextBlendedUTF8(const char *text, SDL_Color color)
{
    return TTF_RenderUTF8_Blended(font, text, color);
}

SDL_Surface * Font::renderTextBlendedUNICODE(const Uint16 *text, SDL_Color color)
{
    return TTF_RenderUNICODE_Blended(font, text, color);
}

SDL_Surface * Font::renderGlyphBlended(Uint16 glyph, SDL_Color color)
{
    return TTF_RenderGlyph_Blended(font, glyph, color);
}
