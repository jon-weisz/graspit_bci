#include "BCI/uiTools.h"
#include "world.h"
#include "body.h"
#include "ivmgr.h"
#include "graspitGUI.h"
#include <Inventor/nodes/SoMaterial.h>
#include "robot.h"
#include <Inventor/nodes/SoCamera.h>
#include <searchState.h>

namespace bci_experiment{

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


void highlightBody(Body * b, SbColor color)
{
  b->getIVMat()->emissiveColor.setIgnored(false);
  b->getIVMat()->emissiveColor.setValue(color);
  b->getIVMat()->transparency.setIgnored(true);
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

void unhighlightBody(Body * b)
{
  b->getIVMat()->emissiveColor.setIgnored(true);
  b->getIVMat()->transparency.setIgnored(false);
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
      std::cout << "highlightNextGraspableBody -- ERROR -- attempted to get next of unregistered body -- \n";
        return NULL;
    }
  int nextBodyIndex = (bodyIndex + 1) % w->getNumGB();
  nextBody = getWorld()->getGB(nextBodyIndex);
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

GraspableBody * highlightNextGraspableBody(GraspableBody *b)
{
  if(!b)
    return b;
  GraspableBody * nextBody = getNextGraspableBody(b);
  if(nextBody)
    {
      highlightBody(b, SbColor(1,0,0));
        highlightBody(nextBody, SbColor(0,1,0));
    }
  return nextBody;
}

bool unhighlightAll()
{
  for(int i = 0; i < getWorld()->getNumGB(); ++i)
  {
    unhighlightBody(getWorld()->getGB(i));
  }
  return true;
}



bool highlightAll()
{
  for(int i = 0; i < getWorld()->getNumGB(); ++i)
  {
    highlightBody(getWorld()->getGB(i), SbColor(1,0,0));
  }
  return true;
}




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

void sendString(const QString & s)
{
  emit graspItGUI->getIVmgr()->emitSendString(s);
}


void sendSetTarget(Body * b)
{
  QString setTargetString = "setTarget " + b->getName();
  sendString(setTargetString);
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


void viewBodies(std::vector<Body *> & body_vec)
{
  SoGroup * so = new SoGroup();
  so->ref();
  for(unsigned int i = 0; i < body_vec.size(); ++i)
    so->addChild(body_vec[i]->getIVRoot());
  graspItGUI->getIVmgr()->getViewer()->getCamera()->viewAll(so, graspItGUI->getIVmgr()->getViewer()->getViewportRegion(), 1.2);
  so->removeAllChildren();
  so->unref();
}


void viewGraspableBodies()
{
  std::vector<Body *> body_vec;
  for(int gi = 0; gi < getWorld()->getNumGB(); ++gi)
    body_vec.push_back(getWorld()->getGB(gi));
  viewBodies(body_vec);
}



void viewHand(Hand * h)
{
  graspItGUI->getIVmgr()->getViewer()->getCamera()->viewAll(h->getIVRoot(), graspItGUI->getIVmgr()->getViewer()->getViewportRegion(), 0.5);
}


void viewTarget(Body * b)
{
  graspItGUI->getIVmgr()->getViewer()->getCamera()->viewAll(b->getIVRoot(), graspItGUI->getIVmgr()->getViewer()->getViewportRegion(), 1.0);
  Body * tableBody= getObjectByName("experiment_table");
  SbVec3f table_z = tableBody->getTran().affine().transpose().row(2).toSbVec3f();



  graspItGUI->getIVmgr()->getViewer()->getCamera()->pointAt(SbVec3f(0,0,0), table_z);
}

bool setPointcloudTransparency(double transparency)
{
  SoMaterial * mat = static_cast<SoMaterial *>(SoMaterial::getByName("PointCloudColorMaterial"));
  if(!mat)
    return false;
  mat->transparency = transparency;
  return true;
}


bool testPreGraspCollisions(Hand * h, float pregrasp_dist)
{
  h->autoGrasp(false, -2.0, true);
  h->approachToContact(pregrasp_dist, false);
  return (getNumHandCollisions(h));
}


bool testGraspCollisions(Hand * h, const GraspPlanningState * s)
{
  bool result = false;
  std::vector<bool> currentCollisionState;
  resetHandCollisions(h, true, currentCollisionState);
  s->execute(h);
  World * w = getWorld();
  w->toggleCollisions(false, h, s->getObject());
  if(getNumHandCollisions(h))
    result = true;
  if(testPreGraspCollisions(h, -50.0))
    result = true;

  setCollisionState(h, currentCollisionState);
  return result;
}


int getNumHandCollisions(Hand * h)
{
  CollisionReport colReport;
  std::vector<Body *> body_list;
  h->getBodyList(&body_list);
  getWorld()->getCollisionReport(&colReport, &body_list);
  return colReport.size();
}

bool setCollisionState(Hand * h, std::vector<bool> & collisionStatus)
{
  World * w = getWorld();
  if(collisionStatus.size() != w->getNumGB() + 1)
    return false;

  Body * experiment_table = getOrAddExperimentTable();
  w->toggleCollisions(collisionStatus[0], h, experiment_table);
  for (int i = 0; i < w->getNumGB(); ++i)
  {
    w->toggleCollisions(collisionStatus[i+1], h, w->getGB(i));
  }
  return true;
}


void resetHandCollisions(Hand * h, bool setting, std::vector<bool> & collisionStatus)
{
  World * w = getWorld();

  Body * experiment_table = getOrAddExperimentTable();
  collisionStatus.push_back(!w->collisionsAreOff(h, experiment_table));
  w->toggleCollisions(setting, h, experiment_table);

  for (int i = 0; i < w->getNumGB(); ++i)
  {
    collisionStatus.push_back(!w->collisionsAreOff(h, w->getGB(i)));
    w->toggleCollisions(setting, h, w->getGB(i));
  }
}


}
