#ifndef ONLINESELECTIONSTATE_H
#define ONLINESELECTIONSTATE_H


#include "BCI/states/handRotationState.h"
#include "BCI/worldElementTools.h"

class OnlinePlanningState : public HandRotationState
{
public:
    OnlinePlanningState(const QString& name, QState* parent = 0);
    virtual void onEntry(QEvent * e);
    virtual void onExit(QEvent * e);


};

#endif // ONLINESELECTIONSTATE_H
