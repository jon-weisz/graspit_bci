
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
}


void ConfirmationState::onEntry(QEvent *e)
{
    confirmationView = new ConfirmationView(bciControlWindow->currentFrame);
    confirmationView->show();

    bciControlWindow->currentState->setText("Confirmation State");

}


void ConfirmationState::onExit(QEvent * e)
{
    Q_UNUSED(e);
    bciControlWindow->currentFrame->removeChild(confirmationView);
}


