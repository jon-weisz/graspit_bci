#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "BCI/state.h"
#include "BCI/bciControlWindow.h"

class ActivateRefinementState: public State
{
public:
    ActivateRefinementState(BCIControlWindow *_bciControlWindow, QState* parent = 0);

    BCIControlWindow *bciControlWindow;
};

#endif // STARTSTATE_H
