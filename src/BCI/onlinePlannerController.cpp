#include "BCI/onlinePlannerController.h"

#include "BCI/bciService.h"
#include "debug.h"
#include "EGPlanner/graspTesterThread.h"

using bci_experiment::world_element_tools::getWorld;

namespace bci_experiment
{

    bool isMainThread(QObject * obj)
    {
        if(obj->thread() != GraspItGUI::getInstance()->getIVmgr()->thread())
        {
            DBGA("Object not in main thread");
            return false;
        }

        if(QThread::currentThread() != GraspItGUI::getInstance()->getIVmgr()->thread())
        {
            DBGA("Current thread is not main thread");
            return false;
        }
    }

    void disableShowContacts()
    {
        for(int i = 0; i < getWorld()->getNumBodies(); ++i)
        {
            getWorld()->getBody(i)->showFrictionCones(false);
        }
    }


    OnlinePlannerController * OnlinePlannerController::onlinePlannerController = NULL;

    OnlinePlannerController* OnlinePlannerController::getInstance()
    {
        if(!onlinePlannerController)
        {            
            onlinePlannerController = new OnlinePlannerController();
	    //            assert(isMainThread(onlinePlannerController));
        }

        return onlinePlannerController;
    }



    OnlinePlannerController::OnlinePlannerController(QObject *parent) :
        QObject(parent),
        mDbMgr(NULL),
        currentTarget(NULL),
        currentGraspIndex(0),
        graspDemonstrationHand(NULL)
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
            GraspitDBGraspAllocator *graspitDBGraspAllocator = new GraspitDBGraspAllocator(currentPlanner->getHand());

            mDbMgr = new db_planner::SqlDatabaseManager("tonga.cs.columbia.edu", 5432,
                              "postgres","roboticslab","armdb",graspitDBModelAllocator,graspitDBGraspAllocator);

          planner_tools::importGraspsFromDBMgr(currentPlanner, mDbMgr);
        }
    }




    void OnlinePlannerController::initializeTarget(Hand * currentHand,
                                                   GraspableBody * targetObject)
    {

        // Set the grasps target to the new object
        currentPlanner->getRefHand()->getGrasp()->setObjectNoUpdate(targetObject);
        currentPlanner->getHand()->getGrasp()->setObjectNoUpdate(targetObject);
        currentPlanner->getGraspTester()->getHand()->getGrasp()->setObjectNoUpdate(targetObject);
        OnlinePlannerController::getGraspDemoHand()->getGrasp()->setObjectNoUpdate(targetObject);

        // Set the target for the planner state
        currentPlanner->getTargetState()->setObject(targetObject);
        currentPlanner->setModelState(currentPlanner->getTargetState());

        // Disable collisions between any nontarget objects and the hand
        world_element_tools::disableNontargetCollisions(currentHand, targetObject);
        world_element_tools::disableTableObjectCollisions();

        disableShowContacts();
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



    bool OnlinePlannerController::hasRecognizedObjects()
    {
       return world_element_tools::getWorld()->getNumGB();
    }


    GraspableBody* OnlinePlannerController::getCurrentTarget()
    {
        if(!currentTarget && getWorld()->getNumGB())
        {
            currentTarget = getWorld()->getGB(0);
        }
        return currentTarget;
    }

    GraspableBody* OnlinePlannerController::incrementCurrentTarget()
    {
        currentTarget = world_element_tools::getNextGraspableBody(currentTarget);
        return currentTarget;
    }


    void OnlinePlannerController::drawGuides()
    {
        if(!getHand() || !getCurrentTarget())
            DBGA("OnlinePlannerController::drawGuides::Error - Tried to draw guides with no hand or no target");

        ui_tools::updateCircularGuides(currentPlanner->getRefHand(), getCurrentTarget());
    }

    void OnlinePlannerController::destroyGuides()
    {
        ui_tools::destroyGuideSeparator();
    }

    void OnlinePlannerController::alignHand()
    {
        if(!getHand() || !getCurrentTarget())
            DBGA("OnlinePlannerController::alignHand::Error - Tried to align hand with no hand or no target");
        Hand * alignedHand = getHand();
        if(currentPlanner)
            alignedHand = currentPlanner->getRefHand();
        world_element_tools::realignHand(alignedHand);
        drawGuides();
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


    bool OnlinePlannerController::setAllowedPlanningCollisions()
    {
        currentPlanner->getRefHand()->getGrasp()->setObjectNoUpdate(currentTarget);
        currentPlanner->getHand()->getGrasp()->setObjectNoUpdate(currentTarget);
        OnlinePlannerController::getGraspDemoHand()->getGrasp()->setObjectNoUpdate(currentTarget);
        currentPlanner->getRefHand()->getGrasp()->setObjectNoUpdate(currentTarget);

        world_element_tools::disableNontargetCollisions(currentPlanner->getRefHand(), currentTarget);
        world_element_tools::setNonLinkCollisions(currentPlanner->getHand(), true);
        world_element_tools::setNonLinkCollisions(getGraspDemoHand(), true);
    }


    bool OnlinePlannerController::setPlannerToRunning()
    {
        if(currentTarget != currentPlanner->getTargetState()->getObject() ||
                currentPlanner->getState() == INIT)
            setPlannerToReady();

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
            initializeTarget(currentPlanner->getRefHand(), currentTarget);
        }

        return true;
    }




    void OnlinePlannerController::rotateHandLong()
    {

        float stepSize = M_PI/100.0;
        transf robotTran = currentPlanner->getRefHand()->getTran();
        transf objectTran = currentTarget->getTran();


        transf rotationTrans = (robotTran * objectTran.inverse()) * transf(Quaternion(stepSize, vec3::Z), vec3(0,0,0));
        transf newTran = rotationTrans *  objectTran;
        currentPlanner->getRefHand()->moveTo(newTran, WorldElement::ONE_STEP, WorldElement::ONE_STEP);
        drawGuides();
    }

    void OnlinePlannerController::rotateHandLat()
    {
        float stepSize = M_PI/100.0;

        transf robotTran = currentPlanner->getRefHand()->getTran();
        transf objectTran = currentTarget->getTran();


        transf rotationTrans = (robotTran * objectTran.inverse()) * transf(Quaternion(stepSize, vec3::X), vec3(0,0,0));
        transf newTran = rotationTrans *  objectTran;
        currentPlanner->getRefHand()->moveTo(newTran, WorldElement::ONE_STEP, WorldElement::ONE_STEP);
        drawGuides();
    }

    void OnlinePlannerController::incrementGraspIndex()
    {
        currentGraspIndex = (currentGraspIndex + 1)%(currentPlanner->getListSize());
    }


    Hand * OnlinePlannerController::getHand()
    {
        return currentPlanner->getHand();
    }

    bool isCloneOf(Robot * r1, Robot * r2)
    {
        return r1->getBase()->getIVGeomRoot()->getChild(0) == r2->getBase()->getIVGeomRoot()->getChild(0);
    }

    Hand * OnlinePlannerController::getGraspDemoHand()
    {
        if (!currentPlanner)
        {
            DBGA("OnlinePlannerController::getGraspDemoHand:Attempted to get demonstration hand with no planner set");
            return NULL;
        }
        /*if(graspDemonstrationHand && !(isCloneOf(currentPlanner->getRefHand(), graspDemonstrationHand)))
        {
            getWorld()->destroyElement(graspDemonstrationHand);
            graspDemonstrationHand = NULL;
        }
        if(!graspDemonstrationHand)
        {
            graspDemonstrationHand = new Hand(getWorld(),currentPlanner->getRefHand()->getName() + "grasp_demo_hand");
            graspDemonstrationHand->cloneFrom(currentPlanner->getRefHand());
            getWorld()->removeElementFromSceneGraph(graspDemonstrationHand);
        }*/
        graspDemonstrationHand = static_cast<OnLinePlanner *>(currentPlanner)->getSolutionClone();
        return graspDemonstrationHand;

    }

    const GraspPlanningState * OnlinePlannerController::getGrasp(int index)
    {
        if(currentPlanner->getListSize() > 0 && index < currentPlanner->getListSize())
        {
            return currentPlanner->getGrasp(index);
        }
        return NULL;

    }

    const GraspPlanningState * OnlinePlannerController::getCurrentGrasp()
    {
        return getGrasp(currentGraspIndex);
    }


}
