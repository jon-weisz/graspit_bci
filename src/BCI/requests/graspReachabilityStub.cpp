#include <QString>

#include "BCI/requests/graspReachabilityStub.h"
#include "egPlanner.h"
#include "graspitGUI.h"
#include "ivmgr.h"
#include "grasp.h"
#include "world.h"
#include "searchState.h"
#include "body.h"
#include "robot.h"

GraspReachabilityStub::GraspReachabilityStub(rpcz::rpc_channel * channel)
    :graspReachability_stub(channel, "CheckGraspReachabilityService")
{
}

void GraspReachabilityStub::buildRequest(const GraspPlanningState * gps)
{


    request.grasp().set_graspid(gps->getAttribute("graspId"));

    request.grasp().object().name(gps->getObject()->name());
    //not finished request.grasp().object().pose(gps->getObject()->getPos());

    request.grasp().set_epsilon_quality(gps->getEpsilonQuality());
    request.grasp().set_volume_quality(gps->getVolume());
    gps->getHand()->getDOF();

    for(int i = 0; i < gps->graspQualities.size(); i++)
    {
        request.grasp().add_secondary_qualities(gps->graspQualities.at(i));
    }

    for(int i = 0; i < gps->getHand()->getNumDOF(); i ++)
    {
        double dof = gps->getHand()->getDOF(i);
        request.grasp().pre_grasp_hand_state().add_hand_dof(dof);
        request.grasp().final_grasp_hand_state().add_hand_dof(dof);
    }

    gps->getHand()->getPalm()->getPos();


    // not finished request.grasp().pre_grasp_hand_state().hand_pose();
    // not finished request.grasp().final_grasp_hand_state().hand_pose();
}


void GraspReachabilityStub::sendRequestImpl()
{
    graspReachability_stub.run(request,&response, &_rpc,rpcz::new_callback<GraspReachabilityStub>(this, &GraspReachabilityStub::callback));
}

void GraspReachabilityStub::callbackImpl()
{
    QString attribute = QString("testResult");
    EGPlanner* currentWorldPlanner = graspItGUI->getIVmgr()->getWorld()->getCurrentPlanner();
    for(int i = 0; i < currentWorldPlanner->getListSize(); i++ )
    {
        const GraspPlanningState * gps = currentWorldPlanner->getGrasp(i);
        if (gps->getAttribute("graspId") == response.graspid())
        {
            currentWorldPlanner->setGraspAttribute(i,attribute, response.graspstatus());
            std::cout << "SetGraspAttribute graspId " << response.graspid() << " attributeString " << response.graspstatus() << "\n";
        }
    }
}

