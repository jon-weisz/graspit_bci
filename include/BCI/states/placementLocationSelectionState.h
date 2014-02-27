#ifndef PLACEMENTLOCATIONSELECTIONSTATE_H
#define PLACEMENTLOCATIONSELECTIONSTATE_H

#include "BCI/state.h"
#include "BCI/bciControlWindow.h"

class PlacementLocationSelectionState:public State
{
public:
    PlacementLocationSelectionState(BCIControlWindow *_bciControlWindow, QState* parent = 0 )
        :State("PlacementLocationSelectionState", parent), bciControlWindow(_bciControlWindow){}

    BCIControlWindow *bciControlWindow;

};

#endif // PLACEMENTLOCATIONSELECTIONSTATE_H
