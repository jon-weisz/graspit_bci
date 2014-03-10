#include "BCI/onlinePlannerController.h"
#include "BCI/bciService.h"
#include "debug.h"
using bci_experiment::world_element_tools::getWorld;

namespace bci_experiment
{

    OnlinePlannerController * OnlinePlannerController::mController = NULL;

    OnlinePlannerController* OnlinePlannerController::getInstance()
    {
        if(!mController)
        {
            mController = new OnlinePlannerController();
        }

        return mController;
    }

    OnlinePlannerController::OnlinePlannerController(QObject *parent) :
        QObject(parent),
        mDbMgr(NULL),
        currentTarget(NULL),
        currentGraspIndex(0),
        currentPlanner(NULL)
    {

    }


    bool OnlinePlannerController::analyzeApproachDir()
    {
        if(!currentPlanner)
            return false;

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
        if(currentPlanner && currentPlanner->getListSize())
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

        if (!mDbMgr)
        {

          if(!currentPlanner || !currentPlanner->getHand())
          {
              return;
          }
          if(!mDbMgr)
          {
            // If it is an online planner
            mDbMgr = new db_planner::SqlDatabaseManager("tonga.cs.columbia.edu", 5432,
                              "postgres","roboticslab","armdb",
			      new GraspitDBModelAllocator(),
                              new GraspitDBGraspAllocator(currentPlanner->getHand()));
          }

          planner_tools::importGraspsFromDBMgr(currentPlanner, mDbMgr);
        }

        if(currentPlanner)
        {
            currentPlanner->updateSolutionList();
        }

    }


    void OnlinePlannerController::updateObject(GraspableBody * newTarget)
    {
        if(currentPlanner)
        {
            if(!currentPlanner->getHand())
                return;
            currentPlanner->getHand()->getGrasp()->setObjectNoUpdate(newTarget);
        }
    }


    void OnlinePlannerController::initializeTarget(Hand * currentHand,
                                                   GraspableBody * targetObject)
    {

        // Set the grasps target to the new object
        updateObject(targetObject);

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
        // If we haven't set up a target and there are graspable bodies in the world
        // target body 0
        if(!currentTarget && getWorld()->getNumGB())
            currentTarget = getWorld()->getGB(0);
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
        if(currentPlanner)
        {
            currentPlanner->stopPlanner();
            return true;
        }
        return false;
    }


    bool OnlinePlannerController::setPlannerToRunning()
    {
        //if(!currentPlanner || !currentPlanner->getTargetState()->getObject())
        //    return false;
        if(currentPlanner && currentPlanner->getState()==READY)
        {
            // might want to connect to idle sensor instead of own thread.
            //currentPlanner->startThread();
            currentPlanner->startPlanner();
            plannerTimedUpdate();
        }
        return true;
    }

    //puts planner in ready state
    bool OnlinePlannerController::setPlannerToReady()
    {

        if(!currentPlanner)
        {
            currentPlanner = planner_tools::createDefaultPlanner();

            // If a valid target exists
            if(currentTarget)
            {
                initializeTarget(currentPlanner->getHand(), currentTarget);
            }
        }

        //currentPlanner->stopPlanner();
        currentPlanner->resetPlanner();
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
        if(currentPlanner->getListSize() > 0)
        {
            return currentPlanner->getGrasp(index);
        }
        return NULL;
    }

}
