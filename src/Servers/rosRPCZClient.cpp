#include "rosRPCZClient.h"

#include "BCI/bciService.h"

//For camerapose callback
#include "matvec3D.h"
#include "graspitGUI.h"
#include "ivmgr.h"
#include <Inventor/nodes/SoCamera.h>

RosRPCZClient::RosRPCZClient():
    _application(),
    _rpc(),
    objectRecognition_stub(_application.create_rpc_channel("tcp://localhost:5556"), "RecognitionService", true),
    cameraOrigin_stub(_application.create_rpc_channel("tcp://localhost:5556"), "CameraOriginService", true),
    checkGraspReachability_stub(_application.create_rpc_channel("tcp://localhost:5556"),"CheckGraspReachabilityService", true)
{

}


void RosRPCZClient::runObjectRecognition()
{
    graspit_rpcz::ObjectRecognitionRequest request;
    boost::shared_ptr<graspit_rpcz::ObjectRecognitionResponse> response = boost::shared_ptr<graspit_rpcz::ObjectRecognitionResponse>(new graspit_rpcz::ObjectRecognitionResponse());

    try
    {
        objectRecognition_stub.RunObjectRecognition(request,response.get(), &_rpc,rpcz::new_callback(this, &RosRPCZClient::objectRecognitionCallback,response));
    }
    catch(rpcz::rpc_error &e)
    {
        std::cout << "RPCZ Error: " << e.what() << std::endl;;
    }
    catch(const std::exception &e)
    {
        std::cout << "NON RPCZ Error: " << e.what() << std::endl;;
    }
}


void RosRPCZClient::getCameraOrigin()
{
//    graspit_rpcz::CameraOriginRequest request;
//    graspit_rpcz::CameraOriginResponse response;

//    rpcz::closure *c = rpcz::new_callback(this, &RosRPCZClient::getCameraOriginCallback, response);
//    rpcz::rpc rpc;

//    try
//    {
//        cameraOrigin_stub.GetCameraOrigin(request,&response, &rpc,c);
//    }
//    catch (rpcz::rpc_error &e)
//    {
//        std::cout << "Error: " << e.what() << std::endl;;
//    }
}

void RosRPCZClient::checkGraspReachability()
{
//    graspit_rpcz::CheckGraspReachabilityRequest request;
//    graspit_rpcz::CheckGraspReachabilityResponse response;


//    rpcz::closure *c = rpcz::new_callback(this, &RosRPCZClient::checkGraspReachabilityCallback, response);
//    rpcz::rpc rpc;

//    try
//    {
//        checkGraspReachability_stub.CheckGraspReachability(request,&response, &rpc,c);
//    }
//    catch (rpcz::rpc_error &e)
//    {
//        std::cout << "Error: " << e.what() << std::endl;;
//    }
}



void RosRPCZClient::getCameraOriginCallback( graspit_rpcz::CameraOriginResponse response )
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
    float x = response.cameraorigin().position().x();
    float y = response.cameraorigin().position().y();
    float z = response.cameraorigin().position().z();
    transf t(mat3::IDENTITY, vec3(x,y,z));
    graspItGUI->getIVmgr()->setCameraTransf(t);
    graspItGUI->getIVmgr()->getViewer()->getCamera()->pointAt(SbVec3f(0,0,0), SbVec3f(0,0,1));
}


void RosRPCZClient::objectRecognitionCallback(boost::shared_ptr<graspit_rpcz::ObjectRecognitionResponse> response)
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
}

void RosRPCZClient::checkGraspReachabilityCallback( graspit_rpcz::CheckGraspReachabilityResponse response )
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
}



