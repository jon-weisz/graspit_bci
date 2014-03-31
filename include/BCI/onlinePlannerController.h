#ifndef ONLINEPLANNERCONTROLLER_H
#define ONLINEPLANNERCONTROLLER_H

#include <QObject>
#include "BCI/utils/uiTools.h"
#include "BCI/utils/plannerTools.h"
#include "BCI/utils/worldElementTools.h"
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
class GraspPlanningState;

namespace bci_experiment{



    class OnlinePlannerController : public QObject
    {
        Q_OBJECT

        public:

            static OnlinePlannerController * getInstance();

            bool analyzeApproachDir();
            bool hasRecognizedObjects();

            GraspableBody* getCurrentTarget();
            GraspableBody * incrementCurrentTarget();

            Hand * getHand();
            const GraspPlanningState * getGrasp(int index);
            const GraspPlanningState * getCurrentGrasp();


            bool setPlannerToRunning();
            bool setPlannerToStopped();
            bool setPlannerToPaused();
            bool setPlannerToReady();

            void connectToPlannerUpdateSignal();

            // Perform any validation or processing that should update
            // the planner or it's visualizations periodically
            //void plannerTimedUpdate();
            void initializeTarget(Hand * currentHand, GraspableBody * targetObject);

            void incrementGraspIndex();



        private:

            static OnlinePlannerController * onlinePlannerController;

            OnlinePlannerController(QObject *parent = 0);
            void initializeDbInterface();



            db_planner::SqlDatabaseManager * mDbMgr;
            GraspableBody * currentTarget;
            unsigned int currentGraspIndex;
            OnLinePlanner * currentPlanner;



    private slots:
            void plannerTimedUpdate();

    };

}
#endif // ONLINEPLANNERCONTROLLER_H
