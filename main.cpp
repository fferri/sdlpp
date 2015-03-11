#include "System.h"
#include "Surface.h"
#include "Logger.h"

#include <cmath>
#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Color text_color = {0,0,0};

class App : public System
{
private:
    Window window;
    int x1, y1, w1, h1, x2, y2;
    Font font;
    Surface bg, img, text;
public:
    App();
    virtual ~App();
    void onKeyUp(const SDL_Event& event);
    void loop();
    void draw();
};

App::App()
    :
        window("Hello, SDL world!", 640, 480),
        font("res/slkscr.ttf", 8),
        bg(640, 480),
        img("res/hello.png"),
        text(font, "Hello, SDL world!", text_color),
        x1(0), y1(0), x2(0), y2(0)
{
    // draw checkerboard:
    Uint32 bgCol[] = {bg.rawColor(127, 127, 127), bg.rawColor(180, 180, 180)};
    const int q = 16;
    for(int y = 0; y < 480/q; y++)
        for(int x = 0; x < 640/q; x++)
            bg.fillRect(x * q, y * q, q, q, bgCol[(x % 2) ^ (y % 2)]);

    // draw radial lines:
    int cx = 320, cy = 240, r = 200;
    SDL_Color line_color = {255, 0, 0};
    for(double a = 0; a < 6.283185307179586; a += 6.283185307179586/20.0)
        bg.drawLine(cx, cy, (int)(cx + cos(a) * r), (int)(cy + sin(a) * r), line_color);

    SDL_Color col0 = {0, 0, 0};
    SDL_Color col1 = {255, 0, 0}, col2 = {0, 255, 0}, col3 = {0, 0, 255};

    // draw rectangle:
    bg.fillRect(300, 100, 50, 50, col2);
    bg.drawRect(300, 100, 50, 50, col0);

    // draw triangle:
    bg.fillTriangle(50, 50, 150, 400, 400, 150, col3);
    bg.drawTriangle(50, 50, 150, 400, 400, 150, col0);

    // draw circle:
    bg.drawCircle(400, 210, 200, col2, 32);

    // fill circle:
    bg.fillCircle(400, 210, 50, col1, 32);
}

App::~App()
{
}

void App::onKeyUp(const SDL_Event& event)
{
    switch(event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
        requestShutdown();
        break;
    case SDLK_BACKSPACE:
        break;
    case SDLK_COMMA:
        break;
    case SDLK_UP:
        y2 -= 10;
        break;
    case SDLK_DOWN:
        y2 += 10;
        break;
    case SDLK_LEFT:
        x2 -= 10;
        break;
    case SDLK_RIGHT:
        x2 += 10;
        break;
    case SDLK_RALT:
        LOG(INFO) << "RAlt up\n";
        break;
    }
}

void App::loop()
{
    window.clear();
    draw();
    window.swapBuffer();
}

void App::draw()
{
    bg.render(window, 0, 0);

    x1 = 40 + sin(ticks() * 0.0018) * 40;
    y1 = 40 + sin(ticks() * 0.0013) * 40;
    w1 = 160 + sin(ticks() * 0.0006) * 40;
    h1 = 160 + sin(ticks() * 0.0009) * 40;
    img.render(window, x1, y1, w1, h1);

    text.render(window, x2, y2);
}

int main(int argc, char **argv)
{
    SET_LOG_LEVEL(TRACE);
    LOG(INFO) << "started " << 0 << "\n";
    App app;
    app.run();
}

