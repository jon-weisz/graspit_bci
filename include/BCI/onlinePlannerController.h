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
            void analyzeApproachDir(OnLinePlanner * op);
            void initializeDbInterface();
            void updateObject(GraspableBody * newTarget);
            static OnlinePlannerController * getSingleton();
            EGPlanner * getPlanner();
            OnLinePlanner * getRunningPlanner();


        private:
            OnlinePlannerController(QObject *parent = 0);
            OnlinePlannerController(OnlinePlannerController *);
            db_planner::SqlDatabaseManager * mDbMgr;
            GraspableBody * currentTarget;
            static OnlinePlannerController * mController;
            unsigned int currentGraspIndex;

        signals:
            void createPlannerSignal();
            void targetSelected();

        public slots:
            // Perform any validation or processing that should update
            // the planner or it's visualizations periodically
            void plannerTimedUpdate();
            void initializeTarget(Hand * currentHand,
                                  GraspableBody * targetObject);
            void highlightAllBodies();
            void unhighlightAllBodies();
            void highlightNextBody();
            void runObjectRecognition();
            void rotateHandLat();
            void rotateHandLong();
            void startPlanner();
            void createPlanner();
            void incrementGraspIndex();
            void stopPlanner();
    };

}
#endif // ONLINEPLANNERCONTROLLER_H
