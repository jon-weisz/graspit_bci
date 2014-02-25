#include "BCI/states/graspSelectionState.h"


using bci_experiment::OnlinePlannerController;
using bci_experiment::world_element_tools::getWorld;

GraspSelectionState::GraspSelectionState(const QString &name, QState *parent)
    :HandRotationState(name, parent)
{
    /* What should next do?

      It should update the online planner controller's idea of the *CURRENT* grasp

      This has two control consequences - If the grasp is sent to the robot, this is the
      grasp that is sent. If the planner is started, this grasp is used as approach
      direction of the seed.

      It also affects the visualization - This should change which grasp is shown by the demonstration hand
      and which grasp is shown most prominantly in any grasp preview pane.


    */
    QSignalTransition * incrementGraspIndexTransition =
            new QSignalTransition(getWorld(), SIGNAL(next()));

    connect(incrementGraspIndexTransition, SIGNAL(triggered()),
            this, SLOT(onNext()));

}

void GraspSelectionState::onEntry(QEvent *e)
{
/* On entry, we must have a valid planner that is NOT running
 */
    if(!OnlinePlannerController::getSingleton()->getPlanner())
    {
    //! Fixme change to error transition
        DBGA("GraspSelectionState::onEntry::Failed to create planner");
    }
    OnlinePlannerController::getSingleton()->stopPlanner();
}

void GraspSelectionState::onNext()
{
    OnlinePlannerController::getSingleton()->incrementGraspIndex();
}
