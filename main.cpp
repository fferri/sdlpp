#include "System.h"
#include "Surface.h"
#include "Logger.h"
#include "PartView.h"

#include <cmath>
#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Color white {255, 255, 255, 255}, red = {255, 0, 0, 255}, green = {0, 255, 0, 255}, blue = {0, 0, 255, 255}, black = {0, 0, 0, 255};
SDL_Color gray1 = {127, 127, 127, 255}, gray2 = {190, 190, 190, 255};

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
        text(font, "Hello, SDL world!", black),
        x1(0), y1(0), x2(0), y2(0)
{
    // draw checkerboard:
    Surface pattern(32, 32);
    pattern.fill(gray1);
    pattern.fillRect(0, 0, 16, 16, gray2);
    pattern.fillRect(16, 16, 16, 16, gray2);
    bg.fill(pattern);

    // draw radial lines:
    int cx = 320, cy = 240, r = 200;
    for(double a = 0; a < 6.283185307179586; a += 6.283185307179586/20.0)
        bg.drawLine(cx, cy, (int)(cx + cos(a) * r), (int)(cy + sin(a) * r), red);

    // draw rectangle:
    bg.fillRect(300, 100, 50, 50, green);
    bg.drawRect(300, 100, 50, 50, black);

    // draw triangle:
    bg.fillTriangle(50, 50, 150, 400, 400, 150, blue);
    bg.drawTriangle(50, 50, 150, 400, 400, 150, black);

    // draw circle:
    bg.drawCircle(400, 210, 200, green, 32);

    // fill circle:
    bg.fillCircle(400, 210, 50, red, 32);
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

PartView *pview;

void App::draw()
{
    bg.render(window, 0, 0);

    x1 = 40 + sin(ticks() * 0.0018) * 40;
    y1 = 40 + sin(ticks() * 0.0013) * 40;
    w1 = 160 + sin(ticks() * 0.0006) * 40;
    h1 = 160 + sin(ticks() * 0.0009) * 40;
    img.render(window, x1, y1, w1, h1);

    text.render(window, x2, y2);

    pview->draw(window);
}

int main(int argc, char **argv)
{
    SET_LOG_LEVEL(DEBUG);

    PartModel part("part1", "fi");
    Event e1; e1.add(60.01f); e1.add(127); part.add(0, e1);
    Event e2; e2.add(63.25f); e2.add(120); part.add(3, e2);
    Event e3; e3.add(63.25f); e3.add(120); part.add(0, e3);

    PartView view(part);
    pview = &view;

    App app;
    app.run();
}

