#ifndef DUMMYCONTROL_H_INCLUDED
#define DUMMYCONTROL_H_INCLUDED

#include "Control.h"

class DummyControl : public Control
{
protected:
    Surface checkerboardPattern;

public:
    DummyControl(SDL_Rect rect);
    virtual ~DummyControl();

    void paint();
};

#endif // DUMMYCONTROL_H_INCLUDED
