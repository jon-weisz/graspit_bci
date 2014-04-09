#include "BCI/bciService.h"
#include "BCI/BCIStateMachine.h"

BCIService * BCIService::bciServiceInstance = NULL;

BCIService* BCIService::getInstance()
{
    if(!bciServiceInstance)
    {
        bciServiceInstance = new BCIService();
    }

    return bciServiceInstance;
}

BCIService::BCIService()
{

}

void BCIService::init(BCIControlWindow *bciControlWindow)
{
    //builds and starts a qtStateMachine
    BCIStateMachine *bciStateMachine = new BCIStateMachine(bciControlWindow,this);
    bciStateMachine->start();
}




void BCIService::runObjectRecognition()
{
    rosServer.runObjectRecognition();
}

void BCIService::getCameraOrigin()
{
    rosServer.getCameraOrigin();
}

void BCIService::checkGraspReachability(const GraspPlanningState * state)
{
    rosServer.checkGraspReachability(state);
}


