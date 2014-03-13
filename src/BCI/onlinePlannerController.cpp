#include "BCI/onlinePlannerController.h"
#include "BCI/bciService.h"
#include "debug.h"
using bci_experiment::world_element_tools::getWorld;

namespace bci_experiment
{

    OnlinePlannerController * OnlinePlannerController::onlinePlannerController = NULL;

    OnlinePlannerController* OnlinePlannerController::getInstance()
    {
        if(!onlinePlannerController)
        {
            onlinePlannerController = new OnlinePlannerController();
        }

        return onlinePlannerController;
    }

    OnlinePlannerController::OnlinePlannerController(QObject *parent) :
        QObject(parent),
        mDbMgr(NULL),
        currentTarget(NULL),
        currentGraspIndex(0)
    {
        currentPlanner = planner_tools::createDefaultPlanner();
    }


    bool OnlinePlannerController::analyzeApproachDir()
    {
        Hand * refHand(currentPlanner->getRefHand());
        GraspPlanningState * graspPlanningState = new GraspPlanningState(refHand);

        graspPlanningState->setPostureType(POSE_DOF, false);
        graspPlanningState->saveCurrentHandState();
        //graspItGUI->getIVmgr()->emitAnalyzeApproachDir(graspPlanningState);
        return true;
    }


    void
    OnlinePlannerController::plannerTimedUpdate()
    {

        /* If there is a planner and the planner has found some solutions
        * do some tests.
        */
        if(currentPlanner->getListSize())
        {
            // Notify someone to analyze the current approach direction
            analyzeApproachDir();

            // If the planner is itself not updating the order of the solution list
            if(!currentPlanner->isRunning())
            {
                currentPlanner->showGrasp(0);
                // We should trigger a redraw here somehow of the grasp views
                //updateResults(true, false);
            }
        }

        BCIService::getInstance()->onPlannerUpdated();
        QTimer::singleShot(1000, this, SLOT(plannerTimedUpdate()));
    }




    void OnlinePlannerController::initializeDbInterface()
    {

        if (!mDbMgr && currentPlanner->getHand())
        {
            GraspitDBModelAllocator *graspitDBModelAllocator = new GraspitDBModelAllocator();
            GraspitDBGraspAllocator *graspitDBGraspAllocator = new GraspitDBGraspAllocator(currentPlanner->getRefHand());

            mDbMgr = new db_planner::SqlDatabaseManager("tonga.cs.columbia.edu", 5432,
                              "postgres","roboticslab","armdb",graspitDBModelAllocator,graspitDBGraspAllocator);

          planner_tools::importGraspsFromDBMgr(currentPlanner, mDbMgr);
        }
    }




    void OnlinePlannerController::initializeTarget(Hand * currentHand,
                                                   GraspableBody * targetObject)
    {

        // Set the grasps target to the new object
        currentPlanner->getHand()->getGrasp()->setObjectNoUpdate(targetObject);

        // Disable collisions between any nontarget objects and the hand
        world_element_tools::disableNontargetCollisions(currentHand, targetObject);
        world_element_tools::disableTableObjectCollisions();

        //start planner
        currentPlanner->resetPlanner();

        // Download grasps from database and load them in to the planner
        initializeDbInterface();

        // Set the hand to it's highest ranked grasp
        if(currentPlanner->getListSize())
        {
            currentPlanner->getGrasp(0)->execute(currentHand);
        }

        // Realign the hand with respect to the object, moving the hand back to its
        // pregrasp pose
        world_element_tools::realignHand(currentHand);

    }

    void OnlinePlannerController::highlightAllBodies()
    {
        ui_tools::highlightAll();
        //highlight the first body in a special color and set it as our current body
        currentTarget = ui_tools::highlightNextGraspableBody(NULL);
        currentPlanner->getHand()->getGrasp()->setObjectNoUpdate(currentTarget);
    }

    void OnlinePlannerController::unhighlightAllBodies()
    {
        ui_tools::unhighlightAll();
    }

    void OnlinePlannerController::highlightNextBody()
    {
        currentTarget = ui_tools::highlightNextGraspableBody(currentTarget);
    }

    void OnlinePlannerController::runObjectRecognition()
    {
        if(!currentTarget && getWorld()->getNumGB())
        {
            currentTarget = getWorld()->getGB(0);
        }
    }

    bool OnlinePlannerController::hasRecognizedObjects()
    {
       return world_element_tools::getWorld()->getNumGB();
    }

    GraspableBody* OnlinePlannerController::getCurrentTarget()
    {
        return currentTarget;
    }





    bool OnlinePlannerController::setPlannerToStopped()
    {
        currentPlanner->stopPlanner();
        return true;
    }

    bool OnlinePlannerController::setPlannerToPaused()
    {
        currentPlanner->pausePlanner();
        return true;
    }


    bool OnlinePlannerController::setPlannerToRunning()
    {

        if(currentPlanner->getState()==READY)
        {
            currentPlanner->startPlanner();
            plannerTimedUpdate();
        }
        return true;
    }

    //puts planner in ready state
    bool OnlinePlannerController::setPlannerToReady()
    {

        if(currentTarget)
        {
            initializeTarget(currentPlanner->getHand(), currentTarget);
        }

        return true;
    }

    void OnlinePlannerController::rotateHandLong()
    {
        graspItGUI->getIVmgr()->rotateLong();
    }

    void OnlinePlannerController::rotateHandLat()
    {
        graspItGUI->getIVmgr()->rotateLat();
    }

    void OnlinePlannerController::incrementGraspIndex()
    {
        currentGraspIndex = (currentGraspIndex + 1)%(currentPlanner->getListSize());
    }

    Hand * OnlinePlannerController::getHand()
    {
        return currentPlanner->getHand();
    }

    const GraspPlanningState * OnlinePlannerController::getGrasp(int index)
    {
        assert(currentPlanner->getListSize() > 0);
        return currentPlanner->getGrasp(index);
    }

    const GraspPlanningState * OnlinePlannerController::getCurrentGrasp()
    {
        return getGrasp(currentGraspIndex);
    }

}
