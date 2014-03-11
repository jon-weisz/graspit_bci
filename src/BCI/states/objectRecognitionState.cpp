#include "BCI/states/objectRecognitionState.h"
#include "BCI/onlinePlannerController.h"

using bci_experiment::OnlinePlannerController;

ObjectRecognitionState::ObjectRecognitionState(BCIControlWindow *_bciControlWindow,QState* parent):
        State("ObjectRecognitionState", parent),bciControlWindow(_bciControlWindow)
{
}


void ObjectRecognitionState::onEntry(QEvent *e)
  {

    objectRecognitionView = new ObjectRecognitionView(bciControlWindow->currentFrame);
    objectRecognitionView->show();
    bciControlWindow->currentState->setText("Object Recognition State");

    BCIService::getInstance()->emitRunObjectRecognition();

    if(OnlinePlannerController::getInstance()->hasRecognizedObjects())
    {
        BCIService::getInstance()->emitGoToNextState1();
    }

}


void ObjectRecognitionState::onExit(QEvent *e)
{
    bciControlWindow->currentFrame->removeChild(objectRecognitionView);
}
