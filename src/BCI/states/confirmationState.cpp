
#include "BCI/states/confirmationState.h"
#include  <QSignalTransition>
#include "BCI/worldElementTools.h"
#include "world.h"
#include "BCI/onlinePlannerController.h"

using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;

ConfirmationState::ConfirmationState(const QString &name, QState *parent)
    :State(name, parent)
{

    QSignalTransition * execSelfTransition = new QSignalTransition(getWorld(), SIGNAL(exec()));
    QObject::connect(execSelfTransition, SIGNAL(triggered()), this, SLOT(onExec()));
    addTransition(execSelfTransition);

}



void ConfirmationState::onExec()
{
    //OnlinePlannerController::getSingleton()->executeCurrentGrasp();
}
