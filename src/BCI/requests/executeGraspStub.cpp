
#include "BCI/requests/executeGraspStub.h"


ExecuteGraspStub::ExecuteGraspStub(rpcz::rpc_channel * channel)
    :executeGrasp_stub(channel, "ExecuteGraspService")
{
}


void ExecuteGraspStub::sendRequestImpl()
{
    executeGrasp_stub.run(request,&response, &_rpc,rpcz::new_callback<ExecuteGraspStub>(this, &ExecuteGraspStub::callback));
}

void ExecuteGraspStub::callbackImpl()
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
}
