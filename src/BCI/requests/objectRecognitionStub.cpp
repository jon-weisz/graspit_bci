#include "BCI/requests/objectRecognitionStub.h"
#include "graspable_object.pb.h"
#include "robot.h"
#include "graspitGUI.h"
#include "ivmgr.h"
#include "world.h"
#include "BCI/onlinePlannerController.h"

ObjectRecognitionStub::ObjectRecognitionStub(rpcz::rpc_channel * channel):
    objectRecognition_stub(channel, "ObjectRecognitionService", true)
{
    connect(
        this,
        SIGNAL(addToWorld(const QString, const QString )),
        bci_experiment::OnlinePlannerController::getInstance(),
        SLOT(addToWorld(const QString , const QString )));
}

void ObjectRecognitionStub::sendRequestImpl()
{
    objectRecognition_stub.run(request,&response, _rpc,rpcz::new_callback<ObjectRecognitionStub>(this, &ObjectRecognitionStub::callback));
}

void ObjectRecognitionStub::callbackImpl()
{
    std::for_each(response.foundobjects().begin(),
                  response.foundobjects().end(),
                  boost::bind(&ObjectRecognitionStub::addObject, this, _1));
}


void ObjectRecognitionStub::addObject(GraspableObject object)
{
    QString  objectName(QString::fromStdString(object.name()) + ".xml");

    //Body b = addToWorld(objectName);

    //b.setName(objectName);

    transf object_pose = transf(
                Quaternion(
                    object.pose().orientation().w(),
                    object.pose().orientation().x(),
                    object.pose().orientation().y(),
                    object.pose().orientation().z()),
                vec3(
                    object.pose().position().x()*1000.0,
                    object.pose().position().y()*1000.0,
                    object.pose().position().z()*1000.0
                    ));
    std::stringstream s;
    s << object_pose;
    QString stringPose(QString::fromStdString(s.str()));
    emit addToWorld(objectName, stringPose);
}



