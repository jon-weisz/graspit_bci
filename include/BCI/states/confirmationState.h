#ifndef CONFIRMATIONSTATE_H
#define CONFIRMATIONSTATE_H



#include "BCI/state.h"
class ConfirmationState:public State
{
public:
    ConfirmationState(const QString& name, QState* parent = 0 )
        :State(name, parent){}
};


#endif // CONFIRMATIONSTATE_H
