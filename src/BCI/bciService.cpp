#include "BCI/bciService.h"


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
//    //builds and starts a qtStateMachine
//    BCIStateMachine *bciStateMachine = new BCIStateMachine(bciControlWindow);
//    bciStateMachine->start();
}


