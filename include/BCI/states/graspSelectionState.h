#ifndef GRASPSELECTIONSTATE_H
#define GRASPSELECTIONSTATE_H


#include "BCI/state.h"
class GraspSelectionState:public State
{
public:
    GraspSelectionState(const QString& name, QState* parent = 0 )
        :State(name, parent){}
};


#endif // GRASPSELECTIONSTATE_H
