#include "BCI/onlinePlannerController.h"


using bci_experiment::world_element_tools::getWorld;
//using bci_experiment::planner_tools::getCurrentPlanner;

namespace bci_experiment{
OnlinePlannerController * OnlinePlannerController::mController = NULL;

    OnlinePlannerController* OnlinePlannerController::getSingleton()
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
        currentGraspIndex(0)
    {

    }


    void
    OnlinePlannerController::analyzeApproachDir(OnLinePlanner * planner)
    {
        if(!planner)
            return;

        Hand * refHand(planner->getRefHand());
        GraspPlanningState * graspPlanningState = new GraspPlanningState(refHand);

        graspPlanningState->setPostureType(POSE_DOF, false);
        graspPlanningState->saveCurrentHandState();
        graspItGUI->getIVmgr()->emitAnalyzeApproachDir(graspPlanningState);
    }


    void
    OnlinePlannerController::plannerTimedUpdate()
    {
        OnLinePlanner * planner = dynamic_cast<OnLinePlanner*>(planner_tools::getCurrentPlanner());

        /* If there is a planner and the planner has found some solutions
        * do some tests.
        */
        if(planner && planner->getListSize())
        {
            // Notify someone to analyze the current approach direction
            analyzeApproachDir(planner);

            // If the planner is itself not updating the order of the solution list
            if(!planner->isRunning())
            {
                dynamic_cast<OnLinePlanner *>(planner)->updateSolutionList();
                planner->showGrasp(0);
                // We should trigger a redraw here somehow of the grasp views
                //updateResults(true, false);
            }
        }
        QTimer::singleShot(1000, this, SLOT(plannerTimedUpdate()));
    }




    void OnlinePlannerController::initializeDbInterface()
    {
        EGPlanner * planner = planner_tools::getCurrentPlanner();

        if (!mDbMgr)
        {

          if(!planner || !planner->getHand())
          {
              return;
          }
          if(!mDbMgr)
          {
            // If it is an online planner
            mDbMgr = new db_planner::SqlDatabaseManager("tonga.cs.columbia.edu", 5432,
                              "postgres","roboticslab","armdb",
                              new GraspitDBModelAllocator,
                              new GraspitDBGraspAllocator(planner->getHand()));
          }

          planner_tools::importGraspsFromDBMgr(planner, mDbMgr);
        }

        // If this planner is an online planner, reorder the solution list
        OnLinePlanner * op = dynamic_cast<OnLinePlanner *>(planner);
        if(op)
        {
            op->updateSolutionList();
        }

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
        graspItGUI->getIVmgr()->emitRunObjectRecognition();
    }


    void OnlinePlannerController::createPlanner()
    {
        OnLinePlanner * op = planner_tools::createDefaultPlanner();

        // If we haven't set up a target and there are graspable bodies in the world
        // target body 0
        if(!currentTarget && getWorld()->getNumGB())
            currentTarget = getWorld()->getGB(0);

        // If a valid target exists
        if(currentTarget){
            initializeTarget(op->getHand(), currentTarget);
            initializeDbInterface();
        }

    }

    EGPlanner * OnlinePlannerController::getPlanner()
    {
        if(!planner_tools::getCurrentPlanner())
            createPlanner();
        return planner_tools::getCurrentPlanner();
    }

    void OnlinePlannerController::startPlanner()
    {
        OnLinePlanner * op = dynamic_cast<OnLinePlanner * >(getPlanner());
        if(!op || !op->getTargetState()->getObject())
        {
            // emit error transition

        }
        op->startThread();
        op->startPlanner();
    }

    void OnlinePlannerController::stopPlanner()
    {
        OnLinePlanner * op = dynamic_cast<OnLinePlanner * >(getPlanner());
        if(op)
            op->stopPlanner();
    }


    OnLinePlanner * OnlinePlannerController::getRunningPlanner()
    {
        OnLinePlanner * op = dynamic_cast<OnLinePlanner * >(getPlanner());
        if(!op || !op->getTargetState()->getObject())
            return NULL;
        if(op && op->getState()==READY)
        {
            // might want to connect to idle sensor instead of own thread.
            op->startThread();
            op->startPlanner();
        }
        return op;
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
        currentGraspIndex = (currentGraspIndex + 1)%(bci_experiment::planner_tools::getCurrentPlanner()->getListSize());
    }

}
