#ifndef CONFIRMATIONSTATE_H
#define CONFIRMATIONSTATE_H



#include "BCI/state.h"
class ConfirmationState:public State
{
    Q_OBJECT

public:
    ConfirmationState(const QString& name, QState* parent = 0 );
public slots:
    void onExec();
};


#endif // CONFIRMATIONSTATE_H
