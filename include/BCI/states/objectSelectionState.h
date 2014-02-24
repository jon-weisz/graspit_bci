#ifndef OBJECTSELECTIONSTATE_H
#define OBJECTSELECTIONSTATE_H

#include "BCI/state.h"

class ObjectSelectionState:public State
{
public:
    ObjectSelectionState(const QString& name, QState* parent = 0 );
    virtual void onEntry(QEvent *e);
    virtual void onExit(QEvent *e);

};

#endif // OBJECTSELECTIONSTATE_H
