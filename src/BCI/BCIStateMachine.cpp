
#include "BCI/BCIStateMachine.h"
#include "ivmgr.h"
#include "BCI/worldElementTools.h"
#include "BCI/uiTools.h"
#include <QSignalTransition>

BCIStateMachine::BCIStateMachine(BCIControlWindow *_bciControlWindow)
{
    bciControlWindow = _bciControlWindow;
}





void BCIStateMachine::start()
{        
    World * currentWorld = bci_experiment::world_element_tools::getWorld();

    State *objectSelectionState = new ObjectSelectionState("objectSelectionState");
    State *initialGraspSelectionState = new GraspSelectionState("initialGraspSelectionState");
    State * onlinePlanningState = new OnlinePlanningState("onlinePlanningState");
    State *finalGraspSelectionState = new GraspSelectionState("finalGraspSelectionState");
    State *confirmationState = new ConfirmationState("confirmationState");

    //State *placementLocationSelectionState = new PlacementLocationSelectionState("placementLocationSelectionState");


    //Exec goes to next state.
    objectSelectionState->addTransition(currentWorld,SIGNAL(exec), initialGraspSelectionState);

    //Exec goes to next state
    initialGraspSelectionState->addTransition(currentWorld, SIGNAL(exec),
                                           onlinePlanningState);


    //exec goes to next state
    onlinePlanningState->addTransition(currentWorld, SIGNAL(exec), confirmationState);

    //next returns to prior state
    confirmationState->addTransition(currentWorld, SIGNAL(next), onlinePlanningState);


    objectSelectionState->assignProperty(bciControlWindow->currentState, "text", "Object Selection State");
    finalGraspSelectionState->assignProperty(bciControlWindow->currentState, "text", "Grasp Selection State");
    initialGraspSelectionState->assignProperty(bciControlWindow->currentState, "text", "Initial Selection State");
    onlinePlanningSelectionState->assignProperty(bciControlWindow->currentState, "text", "Online Planning State");
    //placementLocationSelectionState->assignProperty(bciControlWindow->currentState, "text", "Placement Location Selection State");
    confirmationState->assignProperty(bciControlWindow->currentState, "text", "Confirmation State");

        stateMachine.addState(objectSelectionState);
        stateMachine.addState(finalGraspSelectionState);
        stateMachine.addState(onlinePlanningState);
        stateMachine.addState(finalGraspSelectionState);
        //stateMachine.addState(placementLocationSelectionState);
        stateMachine.addState(confirmationState);

        stateMachine.setInitialState(objectSelectionState);
        stateMachine.start();
}
