#include "BCI/onlinePlannerController.h"
#include "BCI/uiTools.h"
#include "BCI/plannerTools.h"
#include "BCI/worldElementTools.h"
#include <onLinePlanner.h>
#include "robot.h"
#include "searchState.h"
#include "grasp.h"

namespace bci_experiment{

OnlinePlannerController::OnlinePlannerController(QObject *parent) :
    QObject(parent),
    mDBMgr(NULL)
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


void OnlinePlannerController::initializeDbInterface()
{
    if (!mDbMgr)
    {
      EGPlanner * planner = planner_tools::getCurrentPlanner();
      if(!planner || !planner->getHand())
          return;

      // If it is an online planner
      mDbMgr = new db_planner::SqlDatabaseManager("tonga.cs.columbia.edu", 5432,
                          "postgres","roboticslab","armdb",
                          new GraspitDBModelAllocator,
                          new GraspitDBGraspAllocator(planner->getHand()));

      planner_tools::importGraspsFromDBMgr(planner, mDbMgr);
    }

    // If this planner is an online planner, reorder the solution list
    OnlinePlanner * op = dynamic_cast<OnLinePlanner *>(mPlanner);
    if(op)
        op->updateSolutionList();

}


void OnlinePlannerController::updateObject(GraspableBody * newTarget)
{
    EGPlanner * planner = planner_tools::getCurrentPlanner();
    if(planner)
    {
        if(!planner->getHand())
            return;
        planner->getHand()->getGrasp()->setObjectNoUpdate(newTarget);
    }
}


void OnlinePlannerController::initializeTarget(Hand * currentHand,
                                               GraspableBody * targetObject)
{
    OnLinePlanner * op =
            dynamic_cast<OnLinePlanner *>(planner_tools::getCurrentPlanner());

    // Ask someone to create a planner for us
    if(!op)
        return;

    // Set the grasps target to the new object
    updateObject(targetObject);

    // Disable collisions between any nontarget objects and the hand
    world_element_tools::disableNontargetCollisions(currentHand, targetObject);
    world_element_tools::disableTableObjectCollisions();

    //start planner
    op->resetPlanner();

    // Download grasps from database and load them in to the planner
    initializeDbInterface();

    // Set the hand to it's highest ranked grasp
    if(op->getListSize())
        op->getGrasp(0)->execute(currentHand);

    // Realign the hand with respect to the object, moving the hand back to its
    // pregrasp pose
    world_element_tools::realignHand(currentHand);

    emit targetSelected();
}


}

