#ifndef ONLINEPLANNERCONTROLLER_H
#define ONLINEPLANNERCONTROLLER_H

#include <QObject>

namespace bci_experiment{


class OnLinePlanner * op;

class OnlinePlannerController : public QObject
{
    Q_OBJECT
public:
    explicit OnlinePlannerController(QObject *parent = 0);
    void analyzeApproachDir(OnLinePlanner * op);
    void initializeDbInterface();
    void updateObject(GraspableBody * newTarget);

private:
    db_planner::SqlDatabaseManager * mDbMgr;

signals:
    void createPlanner();
    void targetSelected();

public slots:
    void plannerTimedUpdate();
    void initializeTarget(Hand * currentHand,
                          GraspableBody * targetObject);
};

}
#endif // ONLINEPLANNERCONTROLLER_H
