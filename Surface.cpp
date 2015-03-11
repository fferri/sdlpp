#include "Surface.h"
#include "Logger.h"

Surface::Surface(int width, int height)
{
    LOG(TRACE) << "Surface: empty constructor\n";

    version = 0L;
    surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0x000000FF);
    texture = NULL;

    if(!surface)
    {
        LOG(FATAL) << "SDL_CreateRGBSurface: " << SDL_GetError() << "\n";
        exit(1);
    }
}

Surface::Surface(const char *imgFile)
{
    LOG(TRACE) << "Surface: image constructor\n";

    version = 0L;
    surface = IMG_Load(imgFile);
    texture = NULL;

    if(!surface)
    {
        LOG(FATAL) << "IMG_Load: " << IMG_GetError() << "\n";
        exit(1);
    }
}

Surface::Surface(const Font& font, const char *text, SDL_Color color)
{
    LOG(TRACE) << "Surface: text constructor\n";

    version = 0L;
    surface = TTF_RenderText_Solid(font.getFont(), text, color);
    texture = NULL;

    if(!surface)
    {
        LOG(FATAL) << "TTF_RenderText_Solid: " << TTF_GetError() << "\n";
        exit(1);
    }

    LOG(DEBUG) << "created surface from text of size " << getWidth() << "x" << getHeight() << "\n";
}

Surface::~Surface()
{
    invalidateTexture();
    SDL_FreeSurface(surface);
}

unsigned long Surface::getVersion() const
{
    return version;
}

void Surface::invalidateTexture()
{
    if(texture)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    version++;
}

SDL_Texture * Surface::getTexture(const Window& window)
{
    if(!texture)
    {
        texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);

        if(!texture)
        {
            LOG(FATAL) << "SDL_CreateTextureFromSurface: " << SDL_GetError() << "\n";
            exit(1);
        }
    }

    return texture;
}

void Surface::render(const Window& window, const SDL_Rect *srcRect, const SDL_Rect *dstRect)
{
    getTexture(window);

    if(SDL_RenderCopy(window.getRenderer(), texture, srcRect, dstRect) != 0)
    {
        LOG(FATAL) << "SDL_RenderCopy: " << SDL_GetError() << "\n";
        exit(1);
    }
}

void Surface::render(const Window& window, int dstX, int dstY, int dstW, int dstH)
{
    SDL_Rect dstRect = {dstX, dstY, dstW, dstH};
    render(window, NULL, &dstRect);
}

void Surface::render(const Window& window, int dstX, int dstY)
{
    render(window, dstX, dstY, getWidth(), getHeight());
}

void Surface::render(const Window& window, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH)
{
    SDL_Rect srcRect = {srcX, srcY, srcW, srcH};
    SDL_Rect dstRect = {dstX, dstY, dstW, dstH};
    render(window, &srcRect, &dstRect);
}

void Surface::render(const Window& window, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY)
{
    render(window, srcX, srcY, srcW, srcH, dstX, dstY, getWidth(), getHeight());
}

void Surface::saveBMP(const char *bmpFile)
{
    if(SDL_SaveBMP(surface, bmpFile) != 0)
    {
        LOG(FATAL) << "SDL_SaveBMP: " << SDL_GetError() << "\n";
        exit(1);
    }

    LOG(TRACE) << "Surface: saved bitmap to " << bmpFile << "\n";
}

int Surface::getWidth() const
{
    return surface->w;
}

int Surface::getHeight() const
{
    return surface->h;
}

bool Surface::setClipRect(SDL_Rect *rect)
{
    return SDL_SetClipRect(surface, rect);
}

void Surface::clearClipRect()
{
    setClipRect(NULL);
}

SDL_Rect Surface::getClipRect() const
{
    return surface->clip_rect;
}

SDL_PixelFormat * Surface::getPixelFormat() const
{
    return surface->format;
}

Uint32 Surface::rawColor(Uint8 r, Uint8 g, Uint8 b) const
{
    return SDL_MapRGB(getPixelFormat(), r, g, b);
}

Uint32 Surface::rawColor(SDL_Color color) const
{
    return SDL_MapRGB(getPixelFormat(), color.r, color.g, color.b);
}

void Surface::fill(Uint32 color)
{
    fillRect(NULL, color);
}

void Surface::drawRect(int x, int y, int w, int h, SDL_Color color)
{
    SDL_Rect rect = {x, y, w, h};
    drawRect(&rect, rawColor(color));
}

void Surface::drawRect(const SDL_Rect *rect, Uint32 color)
{
    fillRect(rect->x, rect->y, rect->w, 1, color);
    fillRect(rect->x, rect->y, 1, rect->h, color);
    fillRect(rect->x, rect->y + rect->h, rect->w, 1, color);
    fillRect(rect->x + rect->w, rect->y, 1, rect->h, color);
}

void Surface::fillRect(int x, int y, int w, int h, SDL_Color color)
{
    SDL_Rect rect = {x, y, w, h};
    fillRect(&rect, rawColor(color));
}

void Surface::fillRect(const SDL_Rect *rect, Uint32 color)
{
    if(SDL_FillRect(surface, rect, color) != 0)
    {
        LOG(FATAL) << "SDL_FillRect: " << SDL_GetError() << "\n";
        exit(1);
    }

    invalidateTexture();
}

void Surface::fillRect(int x, int y, int w, int h, Uint32 color)
{
    SDL_Rect rect = {x, y, w, h};
    fillRect(&rect, color);
}

void Surface::blit(const Surface& src, const SDL_Rect *srcRect, SDL_Rect *dstPos)
{
    if(SDL_BlitSurface(src.surface, srcRect, surface, dstPos) != 0)
    {
        LOG(FATAL) << "SDL_BlitSurface: " << SDL_GetError() << "\n";
        exit(1);
    }

    invalidateTexture();
}

void Surface::blit(const Surface& src, int dstX, int dstY)
{
    SDL_Rect dstRect = {dstX, dstY, 0, 0};
    blit(src, NULL, &dstRect);
}

void Surface::blit(const Surface& src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY)
{
    SDL_Rect srcRect = {srcX, srcY, srcW, srcH};
    SDL_Rect dstPos = {dstX, dstY, 0, 0};
    blit(src, &srcRect, &dstPos);
}

void Surface::blitScaled(const Surface& src, const SDL_Rect *srcRect, SDL_Rect *dstRect)
{
    if(SDL_BlitScaled(src.surface, srcRect, surface, dstRect) != 0)
    {
        LOG(FATAL) << "SDL_BlitScaled: " << SDL_GetError() << "\n";
        exit(1);
    }

    invalidateTexture();
}

void Surface::blitScaled(const Surface& src, int srcX, int srcY, int srcW, int srcH, int dstX, int dstY, int dstW, int dstH)
{
    SDL_Rect srcRect = {srcX, srcY, srcW, srcH};
    SDL_Rect dstRect = {dstX, dstY, dstW, dstH};
    blitScaled(src, &srcRect, &dstRect);
}

void Surface::drawText(const char *text, int x, int y, const Font& font, SDL_Color color)
{
    Surface s(font, text, color);
    blit(s, x, y);
}

void Surface::drawLine(int x1, int y1, int x2, int y2, SDL_Color color)
{
    if(SDL_MUSTLOCK(surface))
    {
        if(SDL_LockSurface(surface) != 0)
        {
            LOG(FATAL) << "SDL_LockSurface: " << SDL_GetError() << "\n";
            exit(1);
        }
    }

    drawLineNoLock(x1, y1, x2, y2, rawColor(color));

    if(SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }
}

void Surface::drawLineNoLock(int x1, int y1, int x2, int y2, Uint32 color)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
    if(steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }
    if(x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    const float dx = x2 - x1;
    const float dy = fabs(y2 - y1);
    float err = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;
    const int maxX = x2;
    for(int x = x1; x < maxX; x++)
    {
        if(steep)
        {
            pixels[(x * surface->w) + y] = color;
        }
        else
        {
            pixels[(y * surface->w) + x] = color;
        }
        err -= dy;
        if(err < 0)
        {
            y += ystep;
            err += dx;
        }
    }
}

void Surface::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color)
{
    if(SDL_MUSTLOCK(surface))
    {
        if(SDL_LockSurface(surface) != 0)
        {
            LOG(FATAL) << "SDL_LockSurface: " << SDL_GetError() << "\n";
            exit(1);
        }
    }

    drawTriangleNoLock(x1, y1, x2, y2, rawColor(color));

    if(SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }
}

void Surface::drawTriangleNoLock(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color)
{
    drawLineNoLock(x1, y1, x2, y2, color);
    drawLineNoLock(x2, y2, x3, y3, color);
    drawLineNoLock(x3, y3, x1, y1, color);
}

void Surface::fillTriangleNoLock(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int xmin = std::min(std::min(x1, x2), x3);
    int ymin = std::min(std::min(y1, y2), y3);
    int xmax = std::max(std::max(x1, x2), x3);
    int ymax = std::max(std::max(y1, y2), y3);
    int a12 = y1 - y2, b12 = x2 - x1, c12 = x1 * y2 - x2 * y1;
    int a23 = y2 - y3, b23 = x3 - x2, c23 = x2 * y3 - x3 * y2;
    int a31 = y3 - y1, b31 = x1 - x3, c31 = x3 * y1 - x1 * y3;
    for(int x = xmin; x <= xmax; x++)
    {
        for(int y = ymin; y <= ymax; y++)
        {
            int d12 = a12 * x + b12 * y + c12;
            int d23 = a23 * x + b23 * y + c23;
            int d31 = a31 * x + b31 * y + c31;
            if(d12 < 0 && d23 < 0 && d31 < 0)
                pixels[(y * surface->w) + x] = color;
        }
    }
}

void Surface::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, SDL_Color color)
{
    if(SDL_MUSTLOCK(surface))
    {
        if(SDL_LockSurface(surface) != 0)
        {
            LOG(FATAL) << "SDL_LockSurface: " << SDL_GetError() << "\n";
            exit(1);
        }
    }

    fillTriangleNoLock(x1, y1, x2, y2, x3, y3, rawColor(color));

    if(SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }
}

void Surface::drawCircleNoLock(int x, int y, int radius, Uint32 color, int resolution)
{
    for(int i = 0; i < resolution; i++)
    {
        double a1 = M_PI * 2 * i / (double)resolution;
        double a2 = M_PI * 2 * (i + 1) / (double)resolution;
        int x1 = int(x + radius * cos(a1));
        int y1 = int(y + radius * sin(a1));
        int x2 = int(x + radius * cos(a2));
        int y2 = int(y + radius * sin(a2));
        drawLineNoLock(x1, y1, x2, y2, color);
    }
}

void Surface::drawCircle(int x, int y, int radius, SDL_Color color, int resolution)
{
    if(SDL_MUSTLOCK(surface))
    {
        if(SDL_LockSurface(surface) != 0)
        {
            LOG(FATAL) << "SDL_LockSurface: " << SDL_GetError() << "\n";
            exit(1);
        }
    }

    drawCircleNoLock(x, y, radius, rawColor(color), resolution);

    if(SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }
}

void Surface::fillCircleNoLock(int x, int y, int radius, Uint32 color, int resolution)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int rr = radius * radius;
    for(int xx = x - radius; xx <= x + radius; xx++)
    {
        for(int yy = y - radius; yy <= y + radius; yy++)
        {
            int s = (xx - x) * (xx - x) + (yy - y) * (yy - y);
            if(s <= rr)
                pixels[(yy * surface->w) + xx] = color;
        }
    }
}

void Surface::fillCircle(int x, int y, int radius, SDL_Color color, int resolution)
{
    if(SDL_MUSTLOCK(surface))
    {
        if(SDL_LockSurface(surface) != 0)
        {
            LOG(FATAL) << "SDL_LockSurface: " << SDL_GetError() << "\n";
            exit(1);
        }
    }

    fillCircleNoLock(x, y, radius, rawColor(color), resolution);

    if(SDL_MUSTLOCK(surface))
    {
        SDL_UnlockSurface(surface);
    }
}

