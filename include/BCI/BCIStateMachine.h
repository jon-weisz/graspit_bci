#ifndef BCISTATEMACHINE_H
#define BCISTATEMACHINE_H

#include <QState>
#include <QStateMachine>
#include <QSignalTransition>

#include "state.h"
#include "BCI/bciControlWindow.h"


#include "ivmgr.h"


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
