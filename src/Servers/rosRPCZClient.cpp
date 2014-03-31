#include "rosRPCZClient.h"

#include "BCI/bciService.h"



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

void RosRPCZClient::checkGraspReachability()
{
    graspReachabilityStub.sendRequest();
}

void RosRPCZClient::executeGrasp()
{
    executeGraspStub.sendRequest();
}





