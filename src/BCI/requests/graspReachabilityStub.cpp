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

//void GraspReachabilityStub::buildRequest(const GraspPlanningState * gps)
//{
//    transf requestTransform = gps->readPosition()->getCoreTran();

//    request.mutable_final_hand_pose()->mutable_position()->set_x(requestTransform.translation().x());
//    request.mutable_final_hand_pose()->mutable_position()->set_y(requestTransform.translation().y());
//    request.mutable_final_hand_pose()->mutable_position()->set_z(requestTransform.translation().z());

//    request.mutable_final_hand_pose()->mutable_orientation()->set_x(requestTransform.rotation().x);
//    request.mutable_final_hand_pose()->mutable_orientation()->set_y(requestTransform.rotation().y);
//    request.mutable_final_hand_pose()->mutable_orientation()->set_z(requestTransform.rotation().z);
//    request.mutable_final_hand_pose()->mutable_orientation()->set_w(requestTransform.rotation().w);
//}

void GraspReachabilityStub::buildRequest(const GraspPlanningState * gps)
{

    request.clear_grasp();

    request.mutable_grasp()->set_graspid(gps->getAttribute("graspId"));

    request.mutable_grasp()->mutable_object()->set_name(gps->getObject()->name());


    request.mutable_grasp()->mutable_object()->mutable_pose()->mutable_position()->set_x(gps->getObject()->getTran().translation().x());
    request.mutable_grasp()->mutable_object()->mutable_pose()->mutable_position()->set_y(gps->getObject()->getTran().translation().y());
    request.mutable_grasp()->mutable_object()->mutable_pose()->mutable_position()->set_z(gps->getObject()->getTran().translation().z());
    request.mutable_grasp()->mutable_object()->mutable_pose()->mutable_orientation()->set_w(gps->getObject()->getTran().rotation().w);
    request.mutable_grasp()->mutable_object()->mutable_pose()->mutable_orientation()->set_x(gps->getObject()->getTran().rotation().x);
    request.mutable_grasp()->mutable_object()->mutable_pose()->mutable_orientation()->set_y(gps->getObject()->getTran().rotation().y);
    request.mutable_grasp()->mutable_object()->mutable_pose()->mutable_orientation()->set_z(gps->getObject()->getTran().rotation().z);

    request.mutable_grasp()->set_epsilon_quality(gps->getEpsilonQuality());
    request.mutable_grasp()->set_volume_quality(gps->getVolume());

    for(int i = 0; i < gps->getQualityMeasures()->size(); i++)
    {
        request.mutable_grasp()->add_secondary_qualities(gps->getQualityMeasures()->at(i));
    }


    for(int i = 0; i < gps->getHand()->getNumDOF(); i ++)
    {
        double dof = gps->getHand()->getDOF(i)->getVal();
        request.mutable_grasp()->mutable_pre_grasp_hand_state()->add_hand_dof(dof);
        request.mutable_grasp()->mutable_final_grasp_hand_state()->add_hand_dof(dof);
    }


    transf finalHandTransform = gps->readPosition()->getCoreTran();

    float tx = finalHandTransform.translation().x();
    float ty = finalHandTransform.translation().y();
    float tz = finalHandTransform.translation().z();
    float rw = finalHandTransform.rotation().w;
    float rx = finalHandTransform.rotation().x;
    float ry = finalHandTransform.rotation().y;
    float rz = finalHandTransform.rotation().z;

    request.mutable_grasp()->mutable_final_grasp_hand_state()->mutable_hand_pose()->mutable_position()->set_x(tx);
    request.mutable_grasp()->mutable_final_grasp_hand_state()->mutable_hand_pose()->mutable_position()->set_y(ty);
    request.mutable_grasp()->mutable_final_grasp_hand_state()->mutable_hand_pose()->mutable_position()->set_z(tz);
    request.mutable_grasp()->mutable_final_grasp_hand_state()->mutable_hand_pose()->mutable_orientation()->set_w(rw);
    request.mutable_grasp()->mutable_final_grasp_hand_state()->mutable_hand_pose()->mutable_orientation()->set_x(rx);
    request.mutable_grasp()->mutable_final_grasp_hand_state()->mutable_hand_pose()->mutable_orientation()->set_y(ry);
    request.mutable_grasp()->mutable_final_grasp_hand_state()->mutable_hand_pose()->mutable_orientation()->set_z(rz);

    request.mutable_grasp()->mutable_pre_grasp_hand_state()->mutable_hand_pose()->mutable_position()->set_x(tx);
    request.mutable_grasp()->mutable_pre_grasp_hand_state()->mutable_hand_pose()->mutable_position()->set_y(ty);
    request.mutable_grasp()->mutable_pre_grasp_hand_state()->mutable_hand_pose()->mutable_position()->set_z(tz);
    request.mutable_grasp()->mutable_pre_grasp_hand_state()->mutable_hand_pose()->mutable_orientation()->set_w(rw);
    request.mutable_grasp()->mutable_pre_grasp_hand_state()->mutable_hand_pose()->mutable_orientation()->set_x(rx);
    request.mutable_grasp()->mutable_pre_grasp_hand_state()->mutable_hand_pose()->mutable_orientation()->set_y(ry);
    request.mutable_grasp()->mutable_pre_grasp_hand_state()->mutable_hand_pose()->mutable_orientation()->set_z(rz);
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

