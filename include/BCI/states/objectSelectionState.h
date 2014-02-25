#ifndef OBJECTSELECTIONSTATE_H
#define OBJECTSELECTIONSTATE_H

#include <QObject>
#include <QSignalTransition>
#include "world.h"
#include "BCI/state.h"
#include "BCI/onlinePlannerController.h"
#include "BCI/plannerTools.h"
#include "BCI/worldElementTools.h"

class ObjectSelectionState:public State
{
    Q_OBJECT

public:
    ObjectSelectionState(const QString& name, QState* parent = 0 );
    virtual void onEntry(QEvent *e);
    virtual void onExit(QEvent *e);

public slots:

    void onNext();
    void onBodyAdded();

};

#endif // OBJECTSELECTIONSTATE_H
