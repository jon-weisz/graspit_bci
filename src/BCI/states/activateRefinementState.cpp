#include "BCI/states/activateRefinementState.h"


ActivateRefinementState::ActivateRefinementState(BCIControlWindow *_bciControlWindow,QState* parent):
    State("ActivateRefinementState", parent),bciControlWindow(_bciControlWindow)
{

}

