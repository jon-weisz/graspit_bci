#include "BCI/states/executionState.h"



ExecutionState::ExecutionState(BCIControlWindow *_bciControlWindow, QState* parent)
    :State("ExecutionState", parent), bciControlWindow(_bciControlWindow)
{

}


void ExecutionState::onEntry(QEvent *e)
{
    DBGA("I am in ExecutionState On Entry");
    executionView = new ExecutionView(bciControlWindow->currentFrame);
    executionView->show();
    bciControlWindow->currentFrame->show();
    bciControlWindow->currentState->setText("Execution State");
}


void ExecutionState::onExit(QEvent *e)
{
    bciControlWindow->currentFrame->removeChild(executionView);
}
