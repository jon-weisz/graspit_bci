
#include "BCI/BCIStateMachine.h"

#include "BCI/states/objectSelectionState.h"
#include "BCI/states/graspSelectionState.h"
#include "BCI/states/placementLocationSelectionState.h"
#include "BCI/states/confirmationState.h"
#include "BCI/states/onlinePlanningState.h"
#include "BCI/states/activateRefinementState.h"

#include "BCI/bciService.h"

BCIStateMachine::BCIStateMachine(BCIControlWindow *_bciControlWindow)
{
    bciControlWindow = _bciControlWindow;
}

void BCIStateMachine::start()
{        
    BCIService * bciService = BCIService::getInstance();

    ObjectSelectionState *objectSelectionState = new ObjectSelectionState(bciControlWindow);
    GraspSelectionState *initialGraspSelectionState = new GraspSelectionState(bciControlWindow);
    OnlinePlanningState * onlinePlanningState = new OnlinePlanningState(bciControlWindow);
    ActivateRefinementState *activateRefinementState = new ActivateRefinementState(bciControlWindow);
    GraspSelectionState *finalGraspSelectionState = new GraspSelectionState(bciControlWindow);
    ConfirmationState *confirmationState = new ConfirmationState(bciControlWindow);


    //Add all state transistions that are not self transitions----------------------------

    //exec always goes to the next state
    objectSelectionState->addTransition(bciService,SIGNAL(exec()), initialGraspSelectionState);
    initialGraspSelectionState->addTransition(bciService, SIGNAL(exec()), activateRefinementState);
    activateRefinementState->addTransition(bciService, SIGNAL(exec()), onlinePlanningState);
    finalGraspSelectionState->addTransition(bciService, SIGNAL(exec()),confirmationState);
    onlinePlanningState->addTransition(bciService, SIGNAL(exec()), finalGraspSelectionState);

    //next returns us to the previous state in the confirmation state
    confirmationState->addTransition(bciService, SIGNAL(next()), onlinePlanningState);

    //------------------------------------------------------------------------------------

    stateMachine.addState(objectSelectionState);
    stateMachine.addState(initialGraspSelectionState);
    stateMachine.addState(activateRefinementState);
    stateMachine.addState(finalGraspSelectionState);
    stateMachine.addState(onlinePlanningState);
    stateMachine.addState(confirmationState);

    stateMachine.setInitialState(objectSelectionState);
    stateMachine.start();

}

