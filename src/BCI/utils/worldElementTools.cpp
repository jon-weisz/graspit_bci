
#include "BCI/utils/worldElementTools.h"

namespace bci_experiment{
namespace world_element_tools{

void moveBody(Body * b, const transf & relTran)
{
  b->setTran(b->getTran() * relTran);
}


void moveAllBodies(const transf & relTran)
{
  for(int b_ind = 0; b_ind < getWorld()->getNumGB(); ++b_ind)
    {
        moveBody(getWorld()->getGB(b_ind), relTran);
    }
}


Body * getOrAddExperimentTable()
{
  QString bodyName("experiment_table");
  Body * tableBody= getObjectByName(bodyName);
  if(tableBody)
    return tableBody;
  return addToWorld("models/objects/","Obstacle", bodyName+".xml");
}




void setObjectCentral(Body * b)
{
  Body * table = getOrAddExperimentTable();
  moveAllBodies(table->getTran().inverse());
  transf centralize(Quaternion::IDENTITY, -b->getTran().translation());
  moveAllBodies(centralize);

  table->setTran(centralize);
  SoNodeList l;
  unsigned int listLen = SoTransform::getByName("PointCloudTransform", l);
  if(listLen == 1)
  {
    SoTransform * tran = static_cast<SoTransform*>(l[0]);
    centralize.toSoTransform(tran);
  }
}


void disableNontargetCollisions(Hand * h, GraspableBody * target)
{
  World * w = getWorld();
  for (int i = 0; i < w->getNumGB(); ++i)
    {
  if(w->getGB(i) != target)
    w->toggleCollisions(false, w->getGB(i), h);
    }
  w->toggleCollisions(true, target, h);
}


void setTableObjectCollisions(bool setting)
{
  World * w = getWorld();
  Body * experiment_table = getOrAddExperimentTable();
  for (int i = 0; i < w->getNumGB(); ++i)
    w->toggleCollisions(setting, experiment_table, w->getGB(i));
}

void disableTableObjectCollisions()
{
  setTableObjectCollisions(false);
}



GraspableBody * getNextGraspableBody(GraspableBody * b)
{
    GraspableBody * nextBody = NULL;
    World * w = getWorld();
    if(b)
    {
        int bodyIndex = getGraspableBodyIndex(b);
        if(bodyIndex == -1)
        {
            std::cout << "getNextGraspableBody -- ERROR -- attempted to get next of unregistered body -- \n";
            return NULL;
        }
        int nextBodyIndex = (bodyIndex + 1) % w->getNumGB();
        nextBody = w->getGB(nextBodyIndex);
    }
    else if(w->getNumGB() > 0)
    {
         nextBody = getWorld()->getGB(0);
    }


    return nextBody;
}



int getGraspableBodyIndex(Body * b)
{
  World * w = getWorld();
  int bodyIndex = -1;
  while(bodyIndex < w->getNumGB() - 1)
    {
  ++bodyIndex;
  if(w->getGB(bodyIndex) == b)
    break;
    }
  return bodyIndex;
}

Body * getObjectByName(const QString & objectName)
{
  World * w = getWorld();
  Body * b = NULL;
  for(int i = 0; i < w->getNumBodies(); ++i)
    {
  if(w->getBody(i)->getName() == objectName)
    b = w->getBody(i);
    }
  return b;
}


World * getWorld()
{
  return graspItGUI->getIVmgr()->getWorld();
}


//! Brief helper to add an object to the world from relative directory, model type, and model filename.
Body * addToWorld(const QString & relativeModelDir, const QString & modelType, const QString & modelFilename)
{
  QString bodyFile = QString(getenv("GRASPIT")) + "/" +  relativeModelDir + modelFilename;
  std::cout << "body string: "<< bodyFile.toStdString() << std::endl;
  return graspItGUI->getIVmgr()->getWorld()->importBody(modelType, bodyFile);
}


//! If the named body doesn't exist, add it to the world
Body * addBodyIfUnique(const QString & bodyName)
{
  Body * newBody = getObjectByName(bodyName);
  if(newBody)
    return newBody;
  newBody = addToWorld("models/objects/","Body", bodyName+".xml");

  return newBody;
}




//!  Realigns the hand so that it is facing the object and at a reasonable distance
void realignHand(Hand * h)
{
  double approachDist;
  h->quickOpen(1.0);
  if(!h->getGrasp()->getObject())
    approachDist = 300;
  else
    {
      approachDist = 300 - h->getTran().translation().len();

    }
  h->approachToContact(-approachDist, true);
  graspItGUI->getIVmgr()->align();
}

}
}
