#ifndef ONLINEPLANNERCONTROLLER_H
#define ONLINEPLANNERCONTROLLER_H

#include <QObject>
#include "BCI/uiTools.h"
#include "BCI/plannerTools.h"
#include "BCI/worldElementTools.h"
#include "robot.h"
#include "searchState.h"
#include "grasp.h"
#include "graspitGUI.h"
#include "ivmgr.h"
#include "onLinePlanner.h"
#include "DBase/DBPlanner/sql_database_manager.h"

#include "db_manager.h"
#include "database.h"
#include "DBase/graspit_db_model.h"
#include "DBase/graspit_db_grasp.h"

//class OnLinePlanner * op;
class GraspableBody;

namespace bci_experiment{



    class OnlinePlannerController : public QObject
    {
        Q_OBJECT

        public:

            static OnlinePlannerController * getInstance();

            bool analyzeApproachDir();
            void initializeDbInterface();
            void updateObject(GraspableBody * newTarget);
            void runObjectRecognition();
            bool hasRecognizedObjects();

            // Needs the align method to move here
            // Needs the align method broken in to the GUI part and the
            // actual moving the hand part

            void rotateHandLat();
            void rotateHandLong();

            // Highlighting functionality should move to the view controller
            // The method here should only care about setting the next target
            // and possibly emitting a signal that the target has been emitted.
            void highlightAllBodies();
            void unhighlightAllBodies();
            void highlightNextBody();

            GraspableBody* getCurrentBody();

            bool setPlannerToRunning();
            bool setPlannerToStopped();
            bool setPlannerToReady();

            // Perform any validation or processing that should update
            // the planner or it's visualizations periodically
            void plannerTimedUpdate();
            void initializeTarget(Hand * currentHand, GraspableBody * targetObject);

            void incrementGraspIndex();


        private:

            OnlinePlannerController(QObject *parent = 0);
            OnlinePlannerController(OnlinePlannerController *);
            static OnlinePlannerController * mController;

            db_planner::SqlDatabaseManager * mDbMgr;

            GraspableBody * currentTarget;
            unsigned int currentGraspIndex;
            OnLinePlanner * currentPlanner;

            void startPlanner();
            void createPlanner();
            void stopPlanner();
            OnLinePlanner * getPlanner();

    };

}
#endif // ONLINEPLANNERCONTROLLER_H
