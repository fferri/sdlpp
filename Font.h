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
    void setStyle(int style);
    int getStyle();
    void setStyleAttributes(bool bold, bool italic, bool underline, bool strikethrough);
    void getStyleAttributes(bool& bold, bool& italic, bool& underline, bool& strikethrough);
    int getOutline();
    void setOutline(int size);
    int getHinting();
    void setHinting(int hinting);
    bool isKerningEnabled();
    void setKerningEnabled(bool en);
    int getHeight();
    int getAscent();
    int getDescent();
    int getLineSkip();
    bool isFixedWidth();
    char * getFamilyName();
    char * getStyleName();
    bool isGlyphProvided(Uint16 character);
    int getGlyphIndex(Uint16 character);
    bool getGlyphMetrics(Uint16 character, int *minx, int *maxx, int *miny, int *maxy, int *advance);
    bool getTextSize(const char *text, int *w, int *h);
    bool getTextSizeUTF8(const char *text, int *w, int *h);
    bool getTextSizeUNICODE(const Uint16 *text, int *w, int *h);
    SDL_Surface * renderTextSolid(const char *text, SDL_Color color);
    SDL_Surface * renderTextSolidUTF8(const char *text, SDL_Color color);
    SDL_Surface * renderTextSolidUNICODE(const Uint16 *text, SDL_Color color);
    SDL_Surface * renderGlyphSolid(Uint16 glyph, SDL_Color color);
    SDL_Surface * renderTextShaded(const char *text, SDL_Color color, SDL_Color background);
    SDL_Surface * renderTextShadedUTF8(const char *text, SDL_Color color, SDL_Color background);
    SDL_Surface * renderTextShadedUNICODE(const Uint16 *text, SDL_Color color, SDL_Color background);
    SDL_Surface * renderGlyphShaded(Uint16 glyph, SDL_Color color, SDL_Color background);
    SDL_Surface * renderTextBlended(const char *text, SDL_Color color);
    SDL_Surface * renderTextBlendedUTF8(const char *text, SDL_Color color);
    SDL_Surface * renderTextBlendedUNICODE(const Uint16 *text, SDL_Color color);
    SDL_Surface * renderGlyphBlended(Uint16 glyph, SDL_Color color);
};

#endif // FONT_H_INCLUDED
