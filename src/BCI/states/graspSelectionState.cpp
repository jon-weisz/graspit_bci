#include "BCI/states/graspSelectionState.h"
#include "BCI/bciService.h"
#include "BCI/onlinePlannerController.h"

using bci_experiment::OnlinePlannerController;


GraspSelectionState::GraspSelectionState(BCIControlWindow *_bciControlWindow,QState* parent):
    State("GraspSelectionState", parent),bciControlWindow(_bciControlWindow)
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


}


void GraspSelectionState::onEntry(QEvent *e)
{
    OnlinePlannerController::getInstance()->setPlannerToReady();
    OnlinePlannerController::getInstance()->setPlannerToRunning();
    graspSelectionView = new GraspSelectionView(bciControlWindow->currentFrame);
    bciControlWindow->currentFrame->show();
    graspSelectionView->show();
    bciControlWindow->currentState->setText("Grasp Selection State");

}


void GraspSelectionState::onExit(QEvent *e)
{
    bciControlWindow->currentFrame->removeChild(graspSelectionView);
}

void GraspSelectionState::onNext()
{
    OnlinePlannerController::getInstance()->incrementGraspIndex();
}



