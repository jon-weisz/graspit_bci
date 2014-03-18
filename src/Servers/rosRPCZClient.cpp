#include "rosRPCZClient.h"

#include "BCI/bciService.h"
RosRPCZClient::RosRPCZClient():
    _application(),
    objectRecognition_stub(_application.create_rpc_channel("tcp://localhost:5555"), "RecognitionService", true),
    cameraOrigin_stub(_application.create_rpc_channel("tcp://localhost:5555"), "CameraOriginService", true),
    checkGraspReachability_stub(_application.create_rpc_channel("tcp://localhost:5555"),"CheckGraspReachabilityService", true)
{

}


void RosRPCZClient::runObjectRecognition()
{
    graspit_rpcz::ObjectRecognitionRequest request;
    graspit_rpcz::ObjectRecognitionResponse response;

    rpcz::closure *c = rpcz::new_callback(this, &RosRPCZClient::objectRecognitionCallback, response);
    rpcz::rpc rpc;

    try
    {
        objectRecognition_stub.RunObjectRecognition(request,&response, &rpc,c);
    }
    catch (rpcz::rpc_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;;
    }
}


void RosRPCZClient::getCameraOrigin()
{
    graspit_rpcz::CameraOriginRequest request;
    graspit_rpcz::CameraOriginResponse response;

    rpcz::closure *c = rpcz::new_callback(this, &RosRPCZClient::getCameraOriginCallback, response);
    rpcz::rpc rpc;

    try
    {
        cameraOrigin_stub.GetCameraOrigin(request,&response, &rpc,c);
    }
    catch (rpcz::rpc_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;;
    }
}

void RosRPCZClient::checkGraspReachability()
{
    graspit_rpcz::CheckGraspReachabilityRequest request;
    graspit_rpcz::CheckGraspReachabilityResponse response;


    rpcz::closure *c = rpcz::new_callback(this, &RosRPCZClient::checkGraspReachabilityCallback, response);
    rpcz::rpc rpc;

    try
    {
        checkGraspReachability_stub.CheckGraspReachability(request,&response, &rpc,c);
    }
    catch (rpcz::rpc_error &e)
    {
        std::cout << "Error: " << e.what() << std::endl;;
    }
}



void RosRPCZClient::getCameraOriginCallback( graspit_rpcz::CameraOriginResponse response )
{
    std::cout << "hello world I am a callback!!!!";
}

void RosRPCZClient::objectRecognitionCallback( graspit_rpcz::ObjectRecognitionResponse response )
{
    std::cout << "hello world I am a callback!!!!";
}

void RosRPCZClient::checkGraspReachabilityCallback( graspit_rpcz::CheckGraspReachabilityResponse response )
{
    std::cout << "hello world I am a callback!!!!";
}



