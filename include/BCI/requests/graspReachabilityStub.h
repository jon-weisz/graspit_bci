#ifndef GRASPREACHABILITYSERVICEWRAPPER_H
#define GRASPREACHABILITYSERVICEWRAPPER_H

#include "rpcz/rpc_channel.hpp"
#include "rpcz/rpc_channel_impl.hpp"
#include "check_grasp_reachability.pb.h"
#include "check_grasp_reachability.rpcz.h"

#include "BCI/requests/requestStub.h"

//class GraspReachabilityStub : public RequestType
//{
//public:
//    GraspReachabilityStub(rpcz::rpc_channel * channel);

//protected:
//    virtual void callback();
//};


class GraspReachabilityStub : public Request
{
public:
    GraspReachabilityStub(rpcz::rpc_channel * channel);

protected:
    virtual void sendRequestImpl();
    virtual void callback();

private:
    graspit_rpcz::CheckGraspReachabilityService_Stub graspReachability_stub;
    graspit_rpcz::CheckGraspReachabilityRequest request;
    graspit_rpcz::CheckGraspReachabilityResponse response;
};

#endif // GRASPREACHABILITYSERVICEWRAPPER_H
