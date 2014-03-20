#ifndef ROSRPCZCLIENT_H
#define ROSRPCZCLIENT_H


#include "rpcz/rpcz.hpp"

#include "run_recognition.rpcz.h"
#include "run_recognition.pb.h"

#include "get_camera_origin.pb.h"
#include "get_camera_origin.rpcz.h"

#include "check_grasp_reachability.pb.h"
#include "check_grasp_reachability.rpcz.h"

#include <QObject>
#include <boost/shared_ptr.hpp>

using namespace graspit_rpcz;

class RosRPCZClient:public QObject
{
        Q_OBJECT

public:
    RosRPCZClient();
    void runObjectRecognition();
    void getCameraOrigin();
    void checkGraspReachability();

//    void objectRecognitionCallback(graspit_rpcz::ObjectRecognitionResponse *response);
    void objectRecognitionCallback( boost::shared_ptr<graspit_rpcz::ObjectRecognitionResponse> response);
//    void objectRecognitionCallback();
    void getCameraOriginCallback( graspit_rpcz::CameraOriginResponse response );
    void checkGraspReachabilityCallback( graspit_rpcz::CheckGraspReachabilityResponse response );


private:
    rpcz::application _application;
    rpcz::rpc _rpc;
    graspit_rpcz::CameraOriginService_Stub cameraOrigin_stub;
    graspit_rpcz::ObjectRecognitionService_Stub objectRecognition_stub;
    graspit_rpcz::CheckGraspReachabilityService_Stub checkGraspReachability_stub;


};

#endif // ROSRPCZCLIENT_H
