#ifndef ONLINEPLANNERCONTROLLER_H
#define ONLINEPLANNERCONTROLLER_H

#include <QObject>

namespace bci_experiment{


class OnLinePlanner * op;
class db_planner::SqlDatabaseManager;
class GraspableBody;

class OnlinePlannerController : public QObject
{
    Q_OBJECT
public:
    void analyzeApproachDir(OnLinePlanner * op);
    void initializeDbInterface();
    void updateObject(GraspableBody * newTarget);
    OnlinePlannerController * getInstance();

private:
    OnlinePlannerController(QObject *parent = 0);
    OnlinePlannerController(OnlinePlannerController);
    db_planner::SqlDatabaseManager * mDbMgr;
    GraspableBody * currentTarget;
    static OnlinePlannerController * mController;

signals:
    void createPlanner();
    void targetSelected();

public slots:
    void plannerTimedUpdate();
    void initializeTarget(Hand * currentHand,
                          GraspableBody * targetObject);
    void highlightAllBodies();
    void unhighlightAllBodies();
    void highlightNextBody();
    void runObjectRecognition();

};

OnlinePlannerController * OnlinePlannerController::mController = NULL;
}
#endif // ONLINEPLANNERCONTROLLER_H
