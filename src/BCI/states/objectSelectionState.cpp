#include "BCI/states/objectSelectionState.h"
#include "BCI/worldElementTools.h"
#include "world.h"
#include <QSignalTransition>
#include "BCI/onlinePlannerController.h"
#include "BCI/plannerTools.h"

using bci_experiment::world_element_tools::getWorld;

ObjectSelectionState::ObjectSelectionState(const QString& name,
                                           QState* parent = 0 ) :
    State(name, parent){

    QSignalTransition * nextTransition =
            new QSignalTransition(getWorld(), SIGNAL(exec()));
    connect(nextTransition, SIGNAL(triggered()),
            onlinePlannerController, SLOT(highlightNextBody()));

    QSignalTransition * bodyAddedTransition =
            new QSignalTransition(getWorld(), SIGNAL(numElementsChanged()));
    connect(bodyAddedTransition, SIGNAL(triggered()),
            OnlinePlannerController::getInstance(), SLOT(highlightAllBodies()));

}


void ObjectSelectionState::onEntry(QEvent *e)
{
    // First time we should run the object recognition
    OnlinePlannerController::getInstance()->runObjectRecognition();

}

void ObjectSelectionState::onExit(QEvent * e)
{
    Q_UNUSED(e);
    OnlinePlannerController::getInstance()->unhighlightAllObjects();
}

