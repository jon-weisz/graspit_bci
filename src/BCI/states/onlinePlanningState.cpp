#include "BCI/states/onlinePlanningState.h"


using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;


OnlinePlanningState::OnlinePlanningState(BCIControlWindow *_bciControlWindow,QState* parent):
    HandRotationState("OnlinePlanningState", _bciControlWindow, parent),
    bciControlWindow(_bciControlWindow)
{

}

void OnlinePlanningState::onEntry(QEvent *e)
{
    //We must have a planner, a selected object, and the planner must be started
    OnlinePlannerController::getInstance()->setPlannerToRunning();
}


void OnlinePlanningState::onExit(QEvent *e)
{
    OnlinePlannerController::getInstance()->setPlannerToStopped();
}
