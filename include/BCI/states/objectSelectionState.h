#ifndef OBJECTSELECTIONSTATE_H
#define OBJECTSELECTIONSTATE_H

#include <QObject>
#include <QSignalTransition>
#include "world.h"
#include "BCI/state.h"
#include "BCI/onlinePlannerController.h"
#include "BCI/bciControlWindow.h"
#include "BCI/state_views/objectSelectionView.h"

class ObjectSelectionState:public State
{
    Q_OBJECT

public:
    ObjectSelectionState(BCIControlWindow *_bciControlWindow, QState* parent = 0 );
    virtual void onEntry(QEvent *e);
    virtual void onExit(QEvent *e);

private:
    BCIControlWindow *bciControlWindow;
    ObjectSelectionView *objectSelectionView;


public slots:

    void onNext();
    void onBodyAdded();


};

#endif // OBJECTSELECTIONSTATE_H
