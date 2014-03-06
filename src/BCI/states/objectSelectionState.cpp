#include "BCI/states/objectSelectionState.h"
#include "BCI/bciService.h"


using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;


ObjectSelectionState::ObjectSelectionState(BCIControlWindow *_bciControlWindow,QState* parent):
     State("ObjectSelectionState", parent),bciControlWindow(_bciControlWindow)
{
    addSelfTransition(BCIService::getInstance(),SIGNAL(next()), this, SLOT(onNext()));

    objectSelectionView = new ObjectSelectionView(bciControlWindow->currentFrame);
}


void ObjectSelectionState::onEntry(QEvent *e)
{

    objectSelectionView->show();
    bciControlWindow->currentFrame->show();

    OnlinePlannerController::getInstance()->highlightAllBodies();
    bciControlWindow->currentState->setText("Object Selection State");
}


void ObjectSelectionState::onExit(QEvent * e)
{
    Q_UNUSED(e);
    OnlinePlannerController::getInstance()->unhighlightAllBodies();
    objectSelectionView->hide();
}

void ObjectSelectionState::onNext()
{
    OnlinePlannerController::getInstance()->highlightNextBody();
}



