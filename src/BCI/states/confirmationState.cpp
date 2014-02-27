
#include "BCI/states/confirmationState.h"
#include  <QSignalTransition>
#include "BCI/worldElementTools.h"
#include "world.h"
#include "BCI/onlinePlannerController.h"
#include "BCI/bciService.h"

using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;

ConfirmationState::ConfirmationState(BCIControlWindow *_bciControlWindow,QState* parent):
        State("ConfirmationState", parent),bciControlWindow(_bciControlWindow)
{    
    addSelfTransition(BCIService::getInstance(),SIGNAL(exec()), this, SLOT(onExec()));
}



void ConfirmationState::onExec()
{
    //OnlinePlannerController::getSingleton()->executeCurrentGrasp();
}
