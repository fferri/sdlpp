#ifndef DUMMYCONTROL_H_INCLUDED
#define DUMMYCONTROL_H_INCLUDED

#include "Control.h"
#include "ControlsManager.h"

class DummyControl : public Control
{
protected:
    Surface checkerboardPattern;

public:
    DummyControl(ControlsManager& controlsManager);
    virtual ~DummyControl();

    void paint(Surface& s);
};

#endif // DUMMYCONTROL_H_INCLUDED
