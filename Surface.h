#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

#include "Font.h"
#include "Window.h"

class Surface
{
private:
    SDL_Surface *surface;
    SDL_Texture *texture;
    void invalidateTexture();
    unsigned long version;
public:
    Surface(int width, int height);
    Surface(const char *imgFile);
    Surface(const Font& font, const char *text, SDL_Color color);
    virtual ~Surface();
    unsigned long getVersion() const;
    SDL_Texture * getTexture(const Window& window);
    void render(const Window& window, const SDL_Rect *srcRect, const SDL_Rect *dstRect);
    void render(const Window& window, int dstX, int dstY, int dstW, int dstH);
    void render(const Window& window, int dstX, int dstY);
    void render(const Window& window, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH);
    void render(const Window& window, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY);
    void saveBMP(const char *bmpFile);
    int getWidth() const;
    int getHeight() const;
    bool setClipRect(SDL_Rect *rect);
    void clearClipRect();
    SDL_Rect getClipRect() const;
    SDL_PixelFormat * getPixelFormat() const;
    Uint32 rawColor(Uint8 r, Uint8 g, Uint8 b) const;
    Uint32 rawColor(SDL_Color color) const;
    void fill(Uint32 color);
    void drawRect(int x, int y, int w, int h, SDL_Color color);
    void drawRect(const SDL_Rect *rect, Uint32 color);
    void fillRect(int x, int y, int w, int h, SDL_Color color);
    void fillRect(const SDL_Rect *rect, Uint32 color);
    void fillRect(int x, int y, int w, int h, Uint32 color);
    void blit(const Surface& src, const SDL_Rect *srcRect, SDL_Rect *dstPos);
    void blit(const Surface& src, int dstX, int dstY);
    void blit(const Surface& src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY);
    void blitScaled(const Surface& src, const SDL_Rect *srcRect, SDL_Rect *dstRect);
    void blitScaled(const Surface& src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH);
    void drawText(const char *text, int x, int y, const Font& font, SDL_Color color);
    void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);
    void drawLineNoLock(int x1, int y1, int x2, int y2, Uint32 color);
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
    void drawTriangleNoLock(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color);
    void fillTriangleNoLock(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color);
    void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color);
    void drawCircleNoLock(int x, int y, int radius, Uint32 color, int resolution);
    void drawCircle(int x, int y, int radius, SDL_Color color, int resolution);
    void fillCircleNoLock(int x, int y, int radius, Uint32 color, int resolution);
    void fillCircle(int x, int y, int radius, SDL_Color color, int resolution);
};

#endif // SURFACE_H_INCLUDED
