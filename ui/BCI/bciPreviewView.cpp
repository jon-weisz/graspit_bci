#include "bciPreviewView.h"
#include "ui_bciPreviewView.h"


BCIPreviewView::BCIPreviewView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BCIPreviewView)
{
    ui->setupUi(this);

//    SoQtRenderArea *soQtRenderArea = new SoQtRenderArea(this, " ",true);
//    SoQtExaminerViewer *mainViewer_ =  graspItGUI->getIVmgr()->getViewer();
//    SoSeparator *ivRoot = new SoSeparator();
//    SoCamera *camera_ = static_cast<SoCamera *>(mainViewer_->getCamera()->copy());
//    SoRotation *lightDir = new SoRotation;
//    SoTransformSeparator *lightSep = new SoTransformSeparator;
//    Hand *currentHand =   graspItGUI->getIVmgr()->getWorld()->getCurrentHand();

//    soQtRenderArea->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_BLEND);
//    camera_->scaleHeight(.7);
//    camera_->nearDistance = .1;
//    camera_->farDistance=1e5;
//    camera_->setName("ViewCamera");

//    soQtRenderArea->setSceneGraph(ivRoot);

//    //Set up camera tied to main view camera
//    ivRoot->addChild(camera_);

//    //Set up lighting to be the same as the main view's lighting

//    lightDir->rotation.connectFrom(&mainViewer_->getCamera()->orientation);

//    lightSep->addChild(lightDir);
//    lightSep->addChild(mainViewer_->getHeadlight());
//    ivRoot->addChild(lightSep);

//    // Initialize the hand geometry node to contain all geometry
//    // and add to scene graph
//    setupIVHandGeometry(currentHand);
//    ivRoot->addChild(IVHandGeometry);

//    // Initialize object geometry and add to scene graph
//    IVObjectGeometry = static_cast<SoSeparator*>(currentHand->getGrasp()->getObject()->getIVRoot()->copy(false));
//    ivRoot->addChild(IVObjectGeometry);
//    soQtRenderArea->setBackgroundColor(SbColor(1.0,1.0,1.0));
//    soQtRenderArea->scheduleRedraw();
//    soQtRenderArea->render();
//    soQtRenderArea->show();

}

/*!
  Copies the scene graph of the hand in the viewer.
  Here, we initialize the hand geometry scene graph that will
  be used in the view window. We do this by performing a deep copy
  of the scene graph for each individual link to avoid getting
  extraneous geometry attached to the hand such as contact points and
  approach directions indicators. This assumes that the hand is free of such
  decorations when the HandView is initialized.

  \param h a hand to copy
*/
 void BCIPreviewView::setupIVHandGeometry(Hand * h)
{
  //Set up the scene graphs for the hand geometry
  IVHandGeometry = new SoSeparator;
  //copy palm geometry
  IVHandGeometry->addChild(h->getPalm()->getIVRoot()->copy(false));
  std::vector<DynamicBody *> links;

  //Get link pointers
  h->getAllLinks(links);

  //copy link geometry
  for(unsigned int i = 0; i < links.size(); ++i)
  {
    IVHandGeometry->addChild(links[i]->getIVRoot()->copy(false));
  }
}

BCIPreviewView::~BCIPreviewView()
{
    delete ui;
}
