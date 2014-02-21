#include "onlinePlannerController.h"
#include "uiTools.h"
#include <onLinePlanner.h>


OnlinePlannerController::OnlinePlannerController(QObject *parent) :
    QObject(parent)
{
}


void
OnlinePlannerController::analyzeApproachDir(OnLinePlanner * op)
{
    if(!op)
        return;

    Hand & refHand(*op->getRefHand());
    GraspPlanningState * gs = new GraspPlanningState(refHand);

    gs->setPostureType(POSE_DOF, false);
    gs->saveCurrentHandState();
    graspItGUI->getIVmgr()->emitAnalyzeApproachDir(gs);
}


void
OnlinePlannerController::plannerTimedUpdate()
{
    OnLinePlanner * op =
            dynamic_cast<OnlinePlanner>(bci_experiment::getCurrentPlanner());

    /* If there is a planner and the planner has found some solutions
    * do some tests.
    */
    if(op && op->getListSize())
    {
        // Notify someone to analyze the current approach direction
        analyzeApproachDir(op);

        // If the planner is itself not updating the order of the solution list
        if(graspItGUI->getIVmgr()->bciPlanningState == INITIAL_REVIEW_PHASE)
        {
            dynamic_cast<OnLinePlanner *>(mPlanner)->updateSolutionList();
            op->showGrasp(0);

            updateResults(true, false);
        }
    }
    QTimer::singleShot(1000, this, SLOT(plannerTimedUpdate()));
}
