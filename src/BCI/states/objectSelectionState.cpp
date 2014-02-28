#include "BCI/states/objectSelectionState.h"
#include "BCI/bciService.h"


using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;


ObjectSelectionState::ObjectSelectionState(BCIControlWindow *_bciControlWindow,QState* parent):
     State("ObjectSelectionState", parent),bciControlWindow(_bciControlWindow)
{
    addSelfTransition(BCIService::getInstance(),SIGNAL(next()), this, SLOT(onNext()));
    addSelfTransition(BCIService::getInstance(),SIGNAL(numElementsChanged()), this, SLOT(onBodyAdded()));
}


void ObjectSelectionState::onEntry(QEvent *e)
{
    objectSelectionView = new ObjectSelectionView(bciControlWindow->currentFrame);
    bciControlWindow->currentFrame->show();

    // Right now, we run recognition on every entry.
    BCIService::getInstance()->emitRunObjectRecognition();
    OnlinePlannerController::getInstance()->highlightAllBodies();
    bciControlWindow->currentState->setText("Object Selection State");
}


void ObjectSelectionState::onExit(QEvent * e)
{
    Q_UNUSED(e);
    OnlinePlannerController::getInstance()->unhighlightAllBodies();
    bciControlWindow->currentFrame->removeChild(objectSelectionView);
}

void ObjectSelectionState::onNext()
{
    OnlinePlannerController::getInstance()->highlightNextBody();
    objectSelectionView->showSelectedObject();
}

void ObjectSelectionState::onBodyAdded()
{
  //stub
}


