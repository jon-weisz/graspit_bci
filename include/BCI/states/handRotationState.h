#ifndef HANDROTATIONSTATE_H
#define HANDROTATIONSTATE_H

#include "BCI/state.h"
#include <QSignalTransition>
#include "BCI/onlinePlannerController.h"



class HandRotationState:public State
{
public:
    HandRotationState(const QString& name,QState* parent = 0);
};

#endif // HANDROTATIONSTATE_H
