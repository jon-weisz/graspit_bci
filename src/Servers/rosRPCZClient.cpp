#include "rosRPCZClient.h"

#include "BCI/bciService.h"
#include "EGPlanner/searchState.h"


RosRPCZClient::RosRPCZClient():
    _application(),
    graspReachabilityStub(_application.create_rpc_channel("tcp://localhost:5561")),
    objectRecognitionStub(_application.create_rpc_channel("tcp://localhost:5561")),
    cameraOriginStub(_application.create_rpc_channel("tcp://localhost:5561")),
    executeGraspStub(_application.create_rpc_channel("tcp://localhost:5561"))
{

}


void RosRPCZClient::runObjectRecognition()
{
    objectRecognitionStub.sendRequest();
}

void RosRPCZClient::getCameraOrigin()
{
    cameraOriginStub.sendRequest();
}

void RosRPCZClient::checkGraspReachability(const GraspPlanningState * gps)
{    
    graspReachabilityStub.buildRequest(gps);
    graspReachabilityStub.sendRequest();
}

void RosRPCZClient::executeGrasp()
{
    executeGraspStub.sendRequest();
}




