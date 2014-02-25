#include "BCI/states/objectSelectionState.h"


using bci_experiment::world_element_tools::getWorld;
using bci_experiment::OnlinePlannerController;

ObjectSelectionState::ObjectSelectionState(const QString& name,QState* parent) :
    State(name, parent)
{

    //Create responder for next signals that highlights the next available body
    QSignalTransition * nextTransition =
            new QSignalTransition(getWorld(), SIGNAL(next()));

    connect(nextTransition, SIGNAL(triggered()),this, SLOT(onNext()));

    addTransition(nextTransition);


    //Respond to bodies getting added or removed from the world by updating the selected
    //object and highlighting it if needed.
    QSignalTransition * bodyAddedTransition =
            new QSignalTransition(getWorld(), SIGNAL(numElementsChanged()));

    connect(bodyAddedTransition, SIGNAL(triggered()),        
            this, SLOT(onBodyAdded()));

    addTransition(bodyAddedTransition);

}


void ObjectSelectionState::onEntry(QEvent *e)
{
    // Right now, we run recognition on every entry.
    OnlinePlannerController::getSingleton()->runObjectRecognition();
}


void ObjectSelectionState::onExit(QEvent * e)
{
    Q_UNUSED(e);
    OnlinePlannerController::getSingleton()->getSingleton()->unhighlightAllBodies();
}

void ObjectSelectionState::onNext()
{
    OnlinePlannerController::getSingleton()->highlightNextBody();
}

void ObjectSelectionState::onBodyAdded()
{
  //stub
}

