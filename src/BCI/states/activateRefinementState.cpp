#include "BCI/states/activateRefinementState.h"
#include "BCI/bciService.h"

using bci_experiment::OnlinePlannerController;
using bci_experiment::world_element_tools::getWorld;
using bci_experiment::WorldController;

ActivateRefinementState::ActivateRefinementState(BCIControlWindow *_bciControlWindow,QState* parent):
    HandRotationState("ActivateRefinementState",_bciControlWindow, parent)
{
    addSelfTransition(BCIService::getInstance(),SIGNAL(plannerUpdated()), this, SLOT(onPlannerUpdated()));

    activeRefinementView = new ActiveRefinementView(bciControlWindow->currentFrame);
    activeRefinementView->hide();
}


void ActivateRefinementState::onEntry(QEvent *e)
{
    activeRefinementView->show();
    bciControlWindow->currentState->setText("Active Refinement State");

    OnlinePlannerController::getInstance()->setPlannerToRunning();
}


void ActivateRefinementState::onExit(QEvent *e)
{
    OnlinePlannerController::getInstance()->setPlannerToPaused();
    activeRefinementView->hide();
}




void ActivateRefinementState::onPlannerUpdated(QEvent * e)
{
    return;
    const GraspPlanningState *bestGrasp = OnlinePlannerController::getInstance()->getGrasp(0);

    if(bestGrasp)
    {
        activeRefinementView->showSelectedGrasp(bestGrasp);
        bciControlWindow->currentState->setText("Planner Updated");
    }

}


