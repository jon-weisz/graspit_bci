#include <QString>

#include "BCI/requests/graspReachabilityStub.h"
#include "egPlanner.h"
#include "graspitGUI.h"
#include "ivmgr.h"
#include "grasp.h"
#include "world.h"
#include "searchState.h"

GraspReachabilityStub::GraspReachabilityStub(rpcz::rpc_channel * channel)
    :graspReachability_stub(channel, "CheckGraspReachabilityService")
{
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
        const GraspPlanningState * gs = currentWorldPlanner->getGrasp(i);
        if (gs->getAttribute("graspId") == response.graspid())
        {
            currentWorldPlanner->setGraspAttribute(i,attribute, response.graspstatus());
            std::cout << "SetGraspAttribute graspId " << response.graspid() << " attributeString " << response.graspstatus() << "\n";
        }
    }
}

