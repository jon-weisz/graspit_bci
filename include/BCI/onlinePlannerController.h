#ifndef ONLINEPLANNERCONTROLLER_H
#define ONLINEPLANNERCONTROLLER_H

#include <QObject>

class OnLinePlanner * op;

class OnlinePlannerController : public QObject
{
    Q_OBJECT
public:
    explicit OnlinePlannerController(QObject *parent = 0);
    void analyzeApproachDir(OnLinePlanner * op);


signals:

public slots:
    void plannerTimedUpdate();

};

#endif // ONLINEPLANNERCONTROLLER_H
