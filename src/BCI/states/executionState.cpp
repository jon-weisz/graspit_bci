#include "BCI/states/executionState.h"



ExecutionState::ExecutionState(BCIControlWindow *_bciControlWindow, QState* parent)
    :State("ExecutionState", parent), bciControlWindow(_bciControlWindow)
{
    executionView = new ExecutionView(bciControlWindow->currentFrame);
    executionView->hide();
}


void ExecutionState::onEntry(QEvent *e)
{
    executionView->show();
    bciControlWindow->currentState->setText("Execution State");
}


void ExecutionState::onExit(QEvent *e)
{
    executionView->hide();
}
