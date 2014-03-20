#ifndef ROSRPCZCLIENT_H
#define ROSRPCZCLIENT_H


#include "rpcz/rpcz.hpp"

#include "run_recognition.rpcz.h"
#include "run_recognition.pb.h"

#include "get_camera_origin.pb.h"
#include "get_camera_origin.rpcz.h"

#include "check_grasp_reachability.pb.h"
#include "check_grasp_reachability.rpcz.h"


using namespace graspit_rpcz;

class RosRPCZClient
{
public:
    RosRPCZClient();

    void runObjectRecognition();
    void getCameraOrigin();
    void checkGraspReachability();

    void objectRecognitionCallback(graspit_rpcz::ObjectRecognitionResponse response);
    void getCameraOriginCallback( graspit_rpcz::CameraOriginResponse response );
    void checkGraspReachabilityCallback( graspit_rpcz::CheckGraspReachabilityResponse response );


private:
    rpcz::application _application;
    graspit_rpcz::CameraOriginService_Stub cameraOrigin_stub;
    graspit_rpcz::ObjectRecognitionService_Stub objectRecognition_stub;
    graspit_rpcz::CheckGraspReachabilityService_Stub checkGraspReachability_stub;

};

#endif // ROSRPCZCLIENT_H
