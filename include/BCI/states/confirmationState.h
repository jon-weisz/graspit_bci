#ifndef CONFIRMATIONSTATE_H
#define CONFIRMATIONSTATE_H


#include "BCI/bciControlWindow.h"
#include "BCI/state.h"
class ConfirmationState:public State
{
    Q_OBJECT

public:
    ConfirmationState(BCIControlWindow *_bciControlWindow, QState* parent = 0 );
    BCIControlWindow *bciControlWindow;
public slots:
    void onExec();
};


#endif // CONFIRMATIONSTATE_H
