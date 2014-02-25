#ifndef GRASPSELECTIONSTATE_H
#define GRASPSELECTIONSTATE_H


#include "BCI/states/handRotationState.h"

#include <QSignalTransition>
#include "BCI/worldElementTools.h"
#include "debug.h"

class GraspSelectionState:public HandRotationState
{
    Q_OBJECT

public:
    GraspSelectionState(const QString& name, QState* parent = 0 );

    virtual void onEntry(QEvent *e);

public slots:
    void onNext();
};


#endif // GRASPSELECTIONSTATE_H
