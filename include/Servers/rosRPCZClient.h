#ifndef ROSRPCZCLIENT_H
#define ROSRPCZCLIENT_H

#include "rpcz/rpcz.hpp"

#include <boost/shared_ptr.hpp>
#include "BCI/requests/objectRecognitionStub.h"
#include "BCI/requests/cameraOriginStub.h"
#include "BCI/requests/graspReachabilityStub.h"
#include "BCI/requests/executeGraspStub.h"

using namespace graspit_rpcz;
class GraspPlanningState;
class RosRPCZClient
{

public:
    RosRPCZClient();
    //const QObject * receiver, const char * member
    void runObjectRecognition();
    void getCameraOrigin();
    void checkGraspReachability(const GraspPlanningState * gps);
    void executeGrasp();

private:
    rpcz::application _application;

    GraspReachabilityStub graspReachabilityStub;
    ObjectRecognitionStub objectRecognitionStub;
    CameraOriginStub cameraOriginStub;
    ExecuteGraspStub executeGraspStub;

};

#endif // ROSRPCZCLIENT_H
