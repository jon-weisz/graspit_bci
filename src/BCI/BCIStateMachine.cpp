
#include "BCI/BCIStateMachine.h"


BCIStateMachine::BCIStateMachine(BCIControlWindow *_bciControlWindow)
{
    bciControlWindow = _bciControlWindow;
}

void BCIStateMachine::start()
{
        State *objectSelectionState = new ObjectSelectionState("objectSelectionState");
        State *graspSelectionState = new GraspSelectionState("graspSelectionState");
        State *placementLocationSelectionState = new PlacementLocationSelectionState("placementLocationSelectionState");
        State *confirmationState = new ConfirmationState("confirmationState");

        objectSelectionState->addTransition(bciControlWindow->button1, SIGNAL(clicked()), graspSelectionState);
        graspSelectionState->addTransition(bciControlWindow->button1, SIGNAL(clicked()), placementLocationSelectionState);
        placementLocationSelectionState->addTransition(bciControlWindow->button1, SIGNAL(clicked()), confirmationState);
        confirmationState->addTransition(bciControlWindow->button1, SIGNAL(clicked()), objectSelectionState);

        objectSelectionState->assignProperty(bciControlWindow->currentState, "text", "Object Selection State");
        graspSelectionState->assignProperty(bciControlWindow->currentState, "text", "Grasp Selection State");
        placementLocationSelectionState->assignProperty(bciControlWindow->currentState, "text", "Placement Location Selection State");
        confirmationState->assignProperty(bciControlWindow->currentState, "text", "Confirmation State");

        stateMachine.addState(objectSelectionState);
        stateMachine.addState(graspSelectionState);
        stateMachine.addState(placementLocationSelectionState);
        stateMachine.addState(confirmationState);

        QObject::connect(bciControlWindow->button2,SIGNAL(clicked()),objectSelectionState,SLOT(button2Clicked()));
        QObject::connect(bciControlWindow->button3,SIGNAL(clicked()),objectSelectionState,SLOT(button3Clicked()));
        QObject::connect(bciControlWindow->button4,SIGNAL(clicked()),objectSelectionState,SLOT(button4Clicked()));

        QObject::connect(bciControlWindow->button2,SIGNAL(clicked()),graspSelectionState,SLOT(button2Clicked()));
        QObject::connect(bciControlWindow->button3,SIGNAL(clicked()),graspSelectionState,SLOT(button3Clicked()));
        QObject::connect(bciControlWindow->button4,SIGNAL(clicked()),graspSelectionState,SLOT(button4Clicked()));

        QObject::connect(bciControlWindow->button2,SIGNAL(clicked()),placementLocationSelectionState,SLOT(button2Clicked()));
        QObject::connect(bciControlWindow->button3,SIGNAL(clicked()),placementLocationSelectionState,SLOT(button3Clicked()));
        QObject::connect(bciControlWindow->button4,SIGNAL(clicked()),placementLocationSelectionState,SLOT(button4Clicked()));

        QObject::connect(bciControlWindow->button2,SIGNAL(clicked()),confirmationState,SLOT(button2Clicked()));
        QObject::connect(bciControlWindow->button3,SIGNAL(clicked()),confirmationState,SLOT(button3Clicked()));
        QObject::connect(bciControlWindow->button4,SIGNAL(clicked()),confirmationState,SLOT(button4Clicked()));

        stateMachine.setInitialState(objectSelectionState);
        stateMachine.start();
}
