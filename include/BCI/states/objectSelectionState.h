#ifndef OBJECTSELECTIONSTATE_H
#define OBJECTSELECTIONSTATE_H

#include <QObject>
#include <QSignalTransition>
#include "world.h"
#include "BCI/state.h"
#include "BCI/onlinePlannerController.h"
#include "BCI/plannerTools.h"
#include "BCI/worldElementTools.h"
#include "BCI/bciControlWindow.h"

class ObjectSelectionState:public State
{
    Q_OBJECT

public:
    ObjectSelectionState(BCIControlWindow *_bciControlWindow, QState* parent = 0 );
    virtual void onEntry(QEvent *e);
    virtual void onExit(QEvent *e);

    BCIControlWindow *bciControlWindow;


public slots:

    void onNext();
    void onBodyAdded();


};

#endif // OBJECTSELECTIONSTATE_H
