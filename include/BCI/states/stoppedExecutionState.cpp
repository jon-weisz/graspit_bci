#include "BCI/states/stoppedExecutionState.h"

StoppedExecutionState::StoppedExecutionState(BCIControlWindow *_bciControlWindow, QState* parent)
    :State("StoppedExecutionState", parent), bciControlWindow(_bciControlWindow)
{

}


void StoppedExecutionState::onEntry(QEvent *e)
{
    stoppedExecutionView = new StoppedExecutionView(bciControlWindow->currentFrame);
    stoppedExecutionView->show();
    bciControlWindow->currentFrame->show();
    bciControlWindow->currentState->setText("Execution State");
}


void StoppedExecutionState::onExit(QEvent *e)
{
    bciControlWindow->currentFrame->removeChild(stoppedExecutionView);
}
