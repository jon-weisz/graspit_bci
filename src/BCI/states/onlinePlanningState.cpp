#include "BCI/states/onlinePlanningState.h"


using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;

OnlinePlanningState::OnlinePlanningState(const QString& name,QState* parent)
    :HandRotationState(name, parent)
{

}

void OnlinePlanningState::onEntry(QEvent *e)
{
    //We must have a planner, a selected object, and the planner must be started
    if(!OnlinePlannerController::getSingleton()->getRunningPlanner())
    {
        //Go to the error state here, since we couldn't get or start a planner

    }
}


void OnlinePlanningState::onExit(QEvent *e)
{
    OnlinePlannerController::getSingleton()->stopPlanner();
}
