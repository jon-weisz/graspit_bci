#include "BCI/uiTools.h"
#include "world.h"
#include "body.h"
#include "ivmgr.h"
#include "graspitGUI.h"
#include <Inventor/nodes/SoMaterial.h>
#include "robot.h"
#include <Inventor/nodes/SoCamera.h>
#include <searchState.h>
#include "BCI/worldElementTools.h"


namespace bci_experiment{
namespace ui_tools{

void highlightBody(Body * b, SbColor color)
{
  b->getIVMat()->emissiveColor.setIgnored(false);
  b->getIVMat()->emissiveColor.setValue(color);
  b->getIVMat()->transparency.setIgnored(true);
}



void unhighlightBody(Body * b)
{
  b->getIVMat()->emissiveColor.setIgnored(true);
  b->getIVMat()->transparency.setIgnored(false);
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


}
}
