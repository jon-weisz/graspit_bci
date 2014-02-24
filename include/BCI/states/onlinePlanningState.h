#ifndef ONLINESELECTIONSTATE_H
#define ONLINESELECTIONSTATE_H

class OnlinePlanningState : public State
{
public:
    OnlinePlanningState(const QString& name, QState* parent = 0 )
        :State(name, parent){}
};

#endif // ONLINESELECTIONSTATE_H
