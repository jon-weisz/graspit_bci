
#include "BCI/BCIStateMachine.h"

#include "BCI/states/objectSelectionState.h"
#include "BCI/states/graspSelectionState.h"
#include "BCI/states/placementLocationSelectionState.h"
#include "BCI/states/confirmationState.h"
#include "BCI/states/onlinePlanningState.h"
#include "BCI/states/activateRefinementState.h"
#include "BCI/states/objectRecognitionState.h"
#include "BCI/states/executionState.h"
#include "BCI/states/stoppedExecutionState.h"

#include "BCI/bciService.h"

BCIStateMachine::BCIStateMachine(BCIControlWindow *_bciControlWindow)
{
    bciControlWindow = _bciControlWindow;
}

void BCIStateMachine::start()
{        
    BCIService * bciService = BCIService::getInstance();

    ObjectRecognitionState *objectRecognitionState = new ObjectRecognitionState(bciControlWindow);
    ObjectSelectionState *objectSelectionState = new ObjectSelectionState(bciControlWindow);
    GraspSelectionState *initialGraspSelectionState = new GraspSelectionState(bciControlWindow);
    OnlinePlanningState * onlinePlanningState = new OnlinePlanningState(bciControlWindow);
    ActivateRefinementState *activateRefinementState = new ActivateRefinementState(bciControlWindow);
    GraspSelectionState *finalGraspSelectionState = new GraspSelectionState(bciControlWindow);
    ConfirmationState *confirmationState = new ConfirmationState(bciControlWindow);
    ExecutionState *executionState = new ExecutionState(bciControlWindow);
    StoppedExecutionState *stoppedExecutionState = new StoppedExecutionState(bciControlWindow);

    //Add all state transistions that are not self transitions----------------------------

    //exec always goes to the next state
    objectRecognitionState->addTransition(bciService,SIGNAL(exec()), objectSelectionState);
    objectSelectionState->addTransition(bciService,SIGNAL(exec()), initialGraspSelectionState);
    initialGraspSelectionState->addTransition(bciService, SIGNAL(goToNextState2()), activateRefinementState);
    initialGraspSelectionState->addTransition(bciService, SIGNAL(goToPreviousState()), objectSelectionState);
    initialGraspSelectionState->addTransition(bciService, SIGNAL(exec()), confirmationState);
    activateRefinementState->addTransition(bciService, SIGNAL(goToNextState1()), confirmationState);
    finalGraspSelectionState->addTransition(bciService, SIGNAL(exec()),confirmationState);
    onlinePlanningState->addTransition(bciService, SIGNAL(exec()), finalGraspSelectionState);
    confirmationState->addTransition(bciService, SIGNAL(exec()), executionState);
    executionState->addTransition(bciService, SIGNAL(exec()), stoppedExecutionState);
    stoppedExecutionState->addTransition(bciService, SIGNAL(exec()), executionState);

    stoppedExecutionState->addTransition(bciService, SIGNAL(next()), objectRecognitionState);


    //next returns us to the previous state in the confirmation state
    confirmationState->addTransition(bciService, SIGNAL(next()), initialGraspSelectionState);

    //------------------------------------------------------------------------------------

    stateMachine.addState(objectRecognitionState);
    stateMachine.addState(objectSelectionState);
    stateMachine.addState(initialGraspSelectionState);
    stateMachine.addState(activateRefinementState);
    stateMachine.addState(finalGraspSelectionState);
    stateMachine.addState(onlinePlanningState);
    stateMachine.addState(confirmationState);
    stateMachine.addState(executionState);
    stateMachine.addState(stoppedExecutionState);

    stateMachine.setInitialState(objectRecognitionState);
    stateMachine.start();

}

