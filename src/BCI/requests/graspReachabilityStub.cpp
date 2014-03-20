#include "BCI/requests/graspReachabilityStub.h"

GraspReachabilityStub::GraspReachabilityStub(rpcz::rpc_channel * channel)
    :graspReachability_stub(channel, "CheckGraspReachabilityService")
{
}


void GraspReachabilityStub::sendRequestImpl()
{
    graspReachability_stub.CheckGraspReachability(request,&response, &_rpc,rpcz::new_callback(this, &GraspReachabilityStub::callback));
}

void GraspReachabilityStub::callback()
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
}
