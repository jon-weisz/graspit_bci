#include "BCI/states/graspSelectionState.h"
#include "BCI/bciService.h"

using bci_experiment::OnlinePlannerController;
using bci_experiment::world_element_tools::getWorld;


GraspSelectionState::GraspSelectionState(BCIControlWindow *_bciControlWindow,QState* parent):
    HandRotationState("GraspSelectionState",_bciControlWindow, parent),bciControlWindow(_bciControlWindow)
{
    /* What should next do?

      It should update the online planner controller's idea of the *CURRENT* grasp

      This has two control consequences - If the grasp is sent to the robot, this is the
      grasp that is sent. If the planner is started, this grasp is used as approach
      direction of the seed.

      It also affects the visualization - This should change which grasp is shown by the demonstration hand
      and which grasp is shown most prominantly in any grasp preview pane.


    */

    addSelfTransition(BCIService::getInstance(),SIGNAL(next()), this, SLOT(onNext()));
    addSelfTransition(BCIService::getInstance(),SIGNAL(rotLat()), this, SLOT(onRotateHandLat()));
    addSelfTransition(BCIService::getInstance(),SIGNAL(rotLong()), this, SLOT(onRotateHandLong()));
}


void GraspSelectionState::onEntry(QEvent *e)
{

    graspSelectionView = new GraspSelectionView(bciControlWindow->currentFrame);
    graspSelectionView->show();
    bciControlWindow->currentState->setText("Grasp Selection State");
    OnlinePlannerController::getInstance()->setPlannerToReady();
}


void GraspSelectionState::onExit(QEvent *e)
{
    bciControlWindow->currentFrame->removeChild(graspSelectionView);
}

void GraspSelectionState::onNext()
{
    OnlinePlannerController::getInstance()->incrementGraspIndex();
}

void GraspSelectionState::onRotateHandLong()
{
    OnlinePlannerController::getInstance()->rotateHandLong();
}

void GraspSelectionState::onRotateHandLat()
{
    OnlinePlannerController::getInstance()->rotateHandLat();
}



