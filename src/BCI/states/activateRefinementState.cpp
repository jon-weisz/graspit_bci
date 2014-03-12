#include "BCI/states/activateRefinementState.h"
#include "BCI/bciService.h"

using bci_experiment::OnlinePlannerController;
using bci_experiment::world_element_tools::getWorld;


ActivateRefinementState::ActivateRefinementState(BCIControlWindow *_bciControlWindow,QState* parent):
    HandRotationState("ActivateRefinementState",_bciControlWindow, parent)
{
//    addSelfTransition(BCIService::getInstance(),SIGNAL(rotLat()), this, SLOT(onRotateHandLat()));
//    addSelfTransition(BCIService::getInstance(),SIGNAL(rotLong()), this, SLOT(onRotateHandLong()));
}


void ActivateRefinementState::onEntry(QEvent *e)
{
    activeRefinementView = new ActiveRefinementView(bciControlWindow->currentFrame);
    activeRefinementView->show();
    bciControlWindow->currentState->setText("Active Refinement State");
}


void ActivateRefinementState::onExit(QEvent *e)
{
    bciControlWindow->currentFrame->removeChild(activeRefinementView);
}


//void ActivateRefinementState::onRotateHandLong()
//{
//    OnlinePlannerController::getInstance()->rotateHandLong();
//}

//void ActivateRefinementState::onRotateHandLat()
//{
//    OnlinePlannerController::getInstance()->rotateHandLat();
//}

