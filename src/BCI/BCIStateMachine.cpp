
#include "BCI/BCIStateMachine.h"



BCIStateMachine::BCIStateMachine(BCIControlWindow *_bciControlWindow)
{
    bciControlWindow = _bciControlWindow;
}





void BCIStateMachine::start()
{        
    World * currentWorld = bci_experiment::world_element_tools::getWorld();

    ObjectSelectionState *objectSelectionState = new ObjectSelectionState("objectSelectionState");
    GraspSelectionState *initialGraspSelectionState = new GraspSelectionState("initialGraspSelectionState");
    OnlinePlanningState * onlinePlanningState = new OnlinePlanningState("onlinePlanningState");
    //GraspSelectionState *finalGraspSelectionState = new GraspSelectionState("finalGraspSelectionState");
    ConfirmationState *confirmationState = new ConfirmationState("confirmationState");
    ActivateRefinementState *activateRefinementState = new ActivateRefinementState("activateRefinementState");

    //State *placementLocationSelectionState = new PlacementLocationSelectionState("placementLocationSelectionState");


    //Exec goes to next state.
    objectSelectionState->addTransition(currentWorld,SIGNAL(exec()), initialGraspSelectionState);

    //Exec goes to next state
    initialGraspSelectionState->addTransition(currentWorld, SIGNAL(exec()),
                                           activateRefinementState);

    activateRefinementState->addTransition(currentWorld, SIGNAL(exec()),
                                           onlinePlanningState);

    activateRefinementState->addTransition(currentWorld, SIGNAL(next()),
                                           confirmationState);


    //exec goes to next state
    //onlinePlanningState->addTransition(currentWorld, SIGNAL(exec()), finalGraspSelectionState);

    //finalGraspSelectionState->addTransition(currentWorld, SIGNAL(exec()),
       //                                    confirmationState);

    //next returns to prior state
    confirmationState->addTransition(currentWorld, SIGNAL(next()), onlinePlanningState);


    objectSelectionState->assignProperty(bciControlWindow->currentState, "text", "Object Selection State");
    //finalGraspSelectionState->assignProperty(bciControlWindow->currentState, "text", "Grasp Selection State");
    initialGraspSelectionState->assignProperty(bciControlWindow->currentState, "text", "Initial Selection State");
    onlinePlanningState->assignProperty(bciControlWindow->currentState, "text", "Online Planning State");
    //placementLocationSelectionState->assignProperty(bciControlWindow->currentState, "text", "Placement Location Selection State");
    confirmationState->assignProperty(bciControlWindow->currentState, "text", "Confirmation State");

    stateMachine.addState(objectSelectionState);
    //stateMachine.addState(finalGraspSelectionState);
    stateMachine.addState(onlinePlanningState);
    stateMachine.addState(confirmationState);

    stateMachine.setInitialState(objectSelectionState);
    stateMachine.start();
}
