#include "rosRPCZClient.h"

#include "BCI/bciService.h"



RosRPCZClient::RosRPCZClient():
    _application(),
    graspReachabilityStub(_application.create_rpc_channel("tcp://localhost:5556")),
    objectRecognitionStub(_application.create_rpc_channel("tcp://localhost:5556")),
    cameraOriginStub(_application.create_rpc_channel("tcp://localhost:5556"))
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







void RosRPCZClient::checkGraspReachabilityCallback( graspit_rpcz::CheckGraspReachabilityResponse response )
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
}



