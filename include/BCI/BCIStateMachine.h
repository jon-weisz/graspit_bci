#ifndef BCISTATEMACHINE_H
#define BCISTATEMACHINE_H

#include <QState>
#include <QStateMachine>
#include "state.h"
#include "BCI/bciControlWindow.h"
#include "BCI/states/objectSelectionState.h"
#include "BCI/states/graspSelectionState.h"
#include "BCI/states/placementLocationSelectionState.h"
#include "BCI/states/confirmationState.h"
#include "BCI/states/onlinePlanningState.h"


class BCIStateMachine
{
public:
    BCIStateMachine(BCIControlWindow *_bciControlWindow);
    void start();

private:
    BCIControlWindow *bciControlWindow;
    QStateMachine stateMachine;
};

#endif // BCISTATEMACHINE_H
