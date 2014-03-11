#include "BCI/states/activateRefinementState.h"
#include "BCI/bciService.h"

using bci_experiment::OnlinePlannerController;
using bci_experiment::world_element_tools::getWorld;


ActivateRefinementState::ActivateRefinementState(BCIControlWindow *_bciControlWindow,QState* parent):
    HandRotationState("ActivateRefinementState",_bciControlWindow, parent),bciControlWindow(_bciControlWindow)
{
    addSelfTransition(BCIService::getInstance(),SIGNAL(rotLat()), this, SLOT(onRotateHandLat()));
    addSelfTransition(BCIService::getInstance(),SIGNAL(rotLong()), this, SLOT(onRotateHandLong()));
    addSelfTransition(BCIService::getInstance(),SIGNAL(plannerUpdated()), this, SLOT(onPlannerUpdated()));

}


void ActivateRefinementState::onEntry(QEvent *e)
{
    OnlinePlannerController::getInstance()->setPlannerToRunning();
    activeRefinementView = new ActiveRefinementView(bciControlWindow->currentFrame);
    activeRefinementView->show();
    bciControlWindow->currentState->setText("Active Refinement State");
}


void ActivateRefinementState::onExit(QEvent *e)
{
    OnlinePlannerController::getInstance()->setPlannerToPaused();
    bciControlWindow->currentFrame->removeChild(activeRefinementView);
}


void ActivateRefinementState::onRotateHandLong()
{
    OnlinePlannerController::getInstance()->rotateHandLong();
}

void ActivateRefinementState::onRotateHandLat()
{
    OnlinePlannerController::getInstance()->rotateHandLat();
}

void ActivateRefinementState::onPlannerUpdated()
{
    const GraspPlanningState *bestGrasp = OnlinePlannerController::getInstance()->getGrasp(0);

    if(bestGrasp)
    {
        activeRefinementView->showSelectedGrasp(bestGrasp);
        bciControlWindow->currentState->setText("Planner Updated");
    }

}

