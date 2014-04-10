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
    transf requestTransform = gps->readPosition()->getCoreTran();

    request.mutable_final_hand_pose()->mutable_position()->set_x(requestTransform.translation().x());
    request.mutable_final_hand_pose()->mutable_position()->set_y(requestTransform.translation().y());
    request.mutable_final_hand_pose()->mutable_position()->set_z(requestTransform.translation().z());

    request.mutable_final_hand_pose()->mutable_orientation()->set_x(requestTransform.rotation().x);
    request.mutable_final_hand_pose()->mutable_orientation()->set_y(requestTransform.rotation().y);
    request.mutable_final_hand_pose()->mutable_orientation()->set_z(requestTransform.rotation().z);
    request.mutable_final_hand_pose()->mutable_orientation()->set_w(requestTransform.rotation().w);
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

