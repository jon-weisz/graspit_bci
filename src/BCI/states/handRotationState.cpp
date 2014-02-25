#include "BCI/states/handRotationState.h"


using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;

HandRotationState::HandRotationState(const QString& name,QState* parent):
    State(name,parent)
{
    QSignalTransition *rotateLatTransition = new QSignalTransition(getWorld(),SIGNAL(rotLat()));
    connect(rotateLatTransition,SIGNAL(triggered()), OnlinePlannerController::getSingleton(), SLOT(rotateHandLat()));

    QSignalTransition *rotateLongTransition = new QSignalTransition(getWorld(),SIGNAL(rotLong()));
    connect(rotateLongTransition,SIGNAL(triggered()), OnlinePlannerController::getSingleton(), SLOT(rotateHandLong()));
    addTransition(rotateLatTransition);
    addTransition(rotateLongTransition);

}
