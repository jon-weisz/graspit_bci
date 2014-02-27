#ifndef GRASPSELECTIONSTATE_H
#define GRASPSELECTIONSTATE_H


#include "BCI/states/handRotationState.h"

#include <QSignalTransition>
#include "BCI/worldElementTools.h"
#include "debug.h"
#include "BCI/bciControlWindow.h"

class GraspSelectionState:public HandRotationState
{
    Q_OBJECT

public:
    GraspSelectionState(BCIControlWindow *_bciControlWindow, QState* parent = 0 );
    BCIControlWindow *bciControlWindow;

    virtual void onEntry(QEvent *e);

public slots:
    void onNext();
    void onRotateHandLat();
    void onRotateHandLong();
};


#endif // GRASPSELECTIONSTATE_H
