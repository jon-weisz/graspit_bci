#ifndef PLACEMENTLOCATIONSELECTIONSTATE_H
#define PLACEMENTLOCATIONSELECTIONSTATE_H

#include "BCI/state.h"

class PlacementLocationSelectionState:public State
{
public:
    PlacementLocationSelectionState(const QString& name, QState* parent = 0 )
        :State(name, parent){}
};

#endif // PLACEMENTLOCATIONSELECTIONSTATE_H
