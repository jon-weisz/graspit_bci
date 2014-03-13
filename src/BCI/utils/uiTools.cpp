#include "BCI/utils/uiTools.h"
#include "world.h"
#include "body.h"
#include "ivmgr.h"
#include "graspitGUI.h"
#include <Inventor/nodes/SoMaterial.h>
#include "robot.h"
#include <Inventor/nodes/SoCamera.h>
#include <searchState.h>
#include "BCI/utils/worldElementTools.h"

using bci_experiment::world_element_tools::getWorld;
using bci_experiment::world_element_tools::getObjectByName;
using bci_experiment::world_element_tools::getNextGraspableBody;

namespace bci_experiment
{
    namespace ui_tools
    {

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


        void highlightCurrentGraspableBody(GraspableBody *b)
        {
            highlightAll();

            if(b)
            {
                highlightBody(b, SbColor(0,1,0));
            }
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
