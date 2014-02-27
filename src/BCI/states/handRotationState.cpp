#include "BCI/states/handRotationState.h"
#include "BCI/onlinePlannerController.h"
#include "BCI/bciService.h"


using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;


HandRotationState::HandRotationState(QString name , BCIControlWindow *_bciControlWindow,QState* parent):
      State(name, parent),bciControlWindow(_bciControlWindow)
{
    addSelfTransition(BCIService::getInstance(),SIGNAL(rotLat()), this, SLOT(onRotateHandLat()));
    addSelfTransition(BCIService::getInstance(),SIGNAL(rotLong()), this, SLOT(onRotateHandLong()));
    DBGA("HandRotationState");
}


void HandRotationState::onRotateHandLong()
{
    DBGA("onRotateHandLong");
    OnlinePlannerController::getInstance()->rotateHandLong();
}

void HandRotationState::onRotateHandLat()
{
    DBGA("onRotateHandLat");
    OnlinePlannerController::getInstance()->rotateHandLat();
}
