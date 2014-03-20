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
#include "BCI/requests/objectRecognitionStub.h"
#include "BCI/requests/cameraOriginStub.h"
#include "BCI/requests/graspReachabilityStub.h"

using namespace graspit_rpcz;

class RosRPCZClient:public QObject
{
        Q_OBJECT

public:
    RosRPCZClient();
    void runObjectRecognition();
    void getCameraOrigin();
    void checkGraspReachability();

    void checkGraspReachabilityCallback( graspit_rpcz::CheckGraspReachabilityResponse response );


private:
    rpcz::application _application;

    GraspReachabilityStub graspReachabilityStub;
    ObjectRecognitionStub objectRecognitionStub;
    CameraOriginStub cameraOriginStub;



};

#endif // ROSRPCZCLIENT_H
