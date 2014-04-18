#include "BCI/requests/objectRecognitionStub.h"
#include "graspable_object.pb.h"
#include "matvec3D.h"
#include "robot.h"
#include "graspitGUI.h"
#include "ivmgr.h"
#include "world.h"
ObjectRecognitionStub::ObjectRecognitionStub(rpcz::rpc_channel * channel):
    objectRecognition_stub(channel, "ObjectRecognitionService", true)
{

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
    QString  objectName;
    objectName.fromStdString(object.name());
    Body * b = addToWorld(objectName);

    b->setName(objectName);

    transf object_pose = transf(
                Quaternion(
                    object.pose().orientation().w(),
                    object.pose().orientation().x(),
                    object.pose().orientation().y(),
                    object.pose().orientation().z()),
                vec3(
                    object.pose().position().x(),
                    object.pose().position().y(),
                    object.pose().position().z()
                    ));

    b->setTran(object_pose);
}

Body *ObjectRecognitionStub::addToWorld(const QString & model_filename)
{
 QString body_file = QString(getenv("GRASPIT")) + "/" +  "models/objects/" + model_filename;
 Body *b = graspItGUI->getIVmgr()->getWorld()->importBody("GraspableBody", body_file);
 if(!b)
 {
     QString body_file = QString(getenv("GRASPIT")) + "/" +  "models/object_database/" + model_filename;
     b = graspItGUI->getIVmgr()->getWorld()->importBody("GraspableBody", body_file);
 }
 return b;
}



