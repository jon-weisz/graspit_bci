
#include "BCI/requests/executeGraspStub.h"


ExecuteGraspStub::ExecuteGraspStub(rpcz::rpc_channel * channel)
    :executeGrasp_stub(channel, "ExecuteGraspService")
{
}

void ExecuteGraspStub::buildRequest()
{
//    request.grasp().set_graspid(gps->getAttribute("graspId"));

//    request.grasp().object().name(gps->getObject()->name());
//    //not finished request.grasp().object().pose(gps->getObject()->getPos());

//    request.grasp().set_epsilon_quality(gps->getEpsilonQuality());
//    request.grasp().set_volume_quality(gps->getVolume());
//    gps->getHand()->getDOF();

//    for(int i = 0; i < gps->graspQualities.size(); i++)
//    {
//        request.grasp().add_secondary_qualities(gps->graspQualities.at(i));
//    }

//    for(int i = 0; i < gps->getHand()->getNumDOF(); i ++)
//    {
//        double dof = gps->getHand()->getDOF(i);
//        request.grasp().pre_grasp_hand_state().add_hand_dof(dof);
//        request.grasp().final_grasp_hand_state().add_hand_dof(dof);
//    }

//    gps->getHand()->getPalm()->getPos();


    // not finished request.grasp().pre_grasp_hand_state().hand_pose();
    // not finished request.grasp().final_grasp_hand_state().hand_pose();
}

void ExecuteGraspStub::sendRequestImpl()
{
    executeGrasp_stub.run(request,&response, &_rpc,rpcz::new_callback<ExecuteGraspStub>(this, &ExecuteGraspStub::callback));
}

void ExecuteGraspStub::callbackImpl()
{
    std::cout << "hello world I am a callback!!!!"<< std::endl;
}
