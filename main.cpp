#include "Application.h"
#include "Timer.h"
#include "Surface.h"
#include "Logger.h"
#include "Scrollbar.h"
#include "Scrollbar2.h"
#include "Viewport.h"
#include "DummyControl.h"
#include "Button.h"
#include "Event.h"
#include "PartModel.h"
#include "PartView.h"

#include <cmath>
#include <string>
#include <vector>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class MainWindow : public Window
{
private:
    Font font;
    Scrollbar scrollh, scrollv;
    Scrollbar2 scroll2;
    Control root;
    Button button;
    DummyControl dummy;
    Viewport viewport;
    SDL_UserEvent timerEvent;
    EventTimer timer;
    PartModel partModel;
    PartView partView;

    void buttonCallback();

public:
    MainWindow();
    virtual ~MainWindow();

    void draw();

    void onKeyboardEvent(SDL_KeyboardEvent event);
    void onMouseMotionEvent(SDL_MouseMotionEvent event);
    void onMouseButtonEvent(SDL_MouseButtonEvent event);
    void onMouseWheelEvent(SDL_MouseWheelEvent event);
    void onWindowEvent(SDL_WindowEvent event);
    void onUserEvent(SDL_UserEvent event);
};

class TheApplication : public Application
{
private:
    MainWindow window;
public:
    void loop() { window.draw(); }
};

TheApplication application;

MainWindow::MainWindow()
    : Window("Hello, SDL world!", 640, 480),
      font("res/slkscr.ttf", 8),
      root({0, 0, 640, 480}),
      scrollh({0, 460, 620, 20}),
      scrollv({620, 0, 20, 460}),
      scroll2({40, 383, 400, 20}),
      dummy({0, 0, 1000, 1000}),
      button({40, 40, 100, 30}, "Click me", font),
      viewport({0, 0, 620, 460}, dummy),
      timerEvent({.type=SDL_USEREVENT, .windowID=getID(), .code=1}),
      timer(application, timerEvent),
      partModel("name", "type"),
      partView({40, 80, 400, 300}, partModel)
{
    scroll2.setPos(0.1, 0.5);

    root.addChild(&viewport);
    root.addChild(&scrollh);
    root.addChild(&scrollv);
    root.addChild(&button);
    root.addChild(&partView);

    root.addChild(&scroll2);

    partModel.add(40, Event::Note(20, 0, 40, 100));
    partModel.add(80, Event::Note(30, 0, 20, 100));
    partModel.add(100, Event::Note(35, 0, 10, 100));
    partModel.add(120, Event::Note(20, 0, 40, 100));
    partView.repaint();

    //timer.start(50);

    button.setCallback(boost::bind(&MainWindow::buttonCallback, this));

    scrollh.setContentSize(dummy.getRect().w);
    scrollv.setContentSize(dummy.getRect().h);

    scrollh.setCallback(boost::bind(&Viewport::setX, &viewport, _1));
    scrollv.setCallback(boost::bind(&Viewport::setY, &viewport, _1));
}

MainWindow::~MainWindow()
{
}

void MainWindow::buttonCallback()
{
    root.removeChild(&button);
}

void MainWindow::draw()
{
    if(root.shouldRerender()) {
        clear();
        root.render(*this);
        swapBuffer();
    }
}

void MainWindow::onKeyboardEvent(SDL_KeyboardEvent event)
{
    Window::onKeyboardEvent(event);

    root.onKeyboardEvent(event);

    if(event.type == SDL_KEYDOWN)
    {
        switch(event.keysym.sym)
        {
        case SDLK_ESCAPE:
            application.requestShutdown();
            break;
        }
    }
}

void MainWindow::onMouseMotionEvent(SDL_MouseMotionEvent event)
{
    Window::onMouseMotionEvent(event);

    root.onMouseMotionEvent(event);
}

void MainWindow::onMouseButtonEvent(SDL_MouseButtonEvent event)
{
    Window::onMouseButtonEvent(event);

    root.onMouseButtonEvent(event);
}

void MainWindow::onMouseWheelEvent(SDL_MouseWheelEvent event)
{
    Window::onMouseWheelEvent(event);

    root.onMouseWheelEvent(event);
}

void MainWindow::onWindowEvent(SDL_WindowEvent event)
{
    Window::onWindowEvent(event);

    switch(event.event)
    {
    case SDL_WINDOWEVENT_SHOWN:
    case SDL_WINDOWEVENT_HIDDEN:
    case SDL_WINDOWEVENT_EXPOSED:
    case SDL_WINDOWEVENT_MOVED:
    case SDL_WINDOWEVENT_RESIZED:
    case SDL_WINDOWEVENT_MINIMIZED:
    case SDL_WINDOWEVENT_MAXIMIZED:
    case SDL_WINDOWEVENT_RESTORED:
    case SDL_WINDOWEVENT_FOCUS_GAINED:
    case SDL_WINDOWEVENT_FOCUS_LOST:
    case SDL_WINDOWEVENT_CLOSE:
        break;
    case SDL_WINDOWEVENT_ENTER:
    case SDL_WINDOWEVENT_LEAVE:
        root.onWindowEvent(event);
        break;
    }
    //LOG(INFO) << "WindowEvent: " << eventName << ", windowID=" << (int)event.windowID << ", data1=" << (int)event.data1 << ", data2=" << (int)event.data2 << "\n";
}

void MainWindow::onUserEvent(SDL_UserEvent event)
{
    if(event.code == timerEvent.code)
    {
        scrollh.setPos(0.5 + 0.5 * sin(application.ticks() * 0.001));
    }
}

int main(int argc, char **argv)
{
    application.run();
}

