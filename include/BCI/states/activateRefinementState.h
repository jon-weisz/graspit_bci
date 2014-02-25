#ifndef STARTSTATE_H
#define STARTSTATE_H

#include "BCI/state.h"

class ActivateRefinementState: public State
{
public:
    ActivateRefinementState(const QString& name, QState* parent = 0);


};

#endif // STARTSTATE_H
