#include "DummyControl.h"

const SDL_Color gray1 = {127, 127, 127, 255};
const SDL_Color gray2 = {190, 190, 190, 255};
const SDL_Color black = {  0,   0,   0, 255};
const int dim = 16, dim2 = 2 * dim;

DummyControl::DummyControl(ControlsManager& controlsManager)
    : Control(controlsManager),
      checkerboardPattern(dim2, dim2)
{
    checkerboardPattern.fill(gray1);
    checkerboardPattern.fillRect(0, 0, dim, dim, gray2);
    checkerboardPattern.fillRect(dim, dim, dim, dim, gray2);
}

DummyControl::~DummyControl()
{
}

void DummyControl::paint(Surface& s)
{
    s.fill(checkerboardPattern);
    s.drawLine(0, 0, s.getWidth() - 1, s.getHeight() - 1, black);
}

