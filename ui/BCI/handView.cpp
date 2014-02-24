#include "handView.h"


#include <QWidget>
#include <QApplication>
#include <QObject>
#include <Q3MainWindow>
#include <QTimer>
#include <QThread>

#include <Inventor/SbColor.h>

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
void HandView::setupIVHandGeometry(Hand * h)
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


//Handview
//Constructor
//mainView: pass in the viewer (to base class)
//parentWindow: to attach window to main window
//viewname: use it for captioning of windows
HandView::HandView(SoQtExaminerViewer *mainViewer, Hand * h, QFrame &parentWindow, QString viewName): viewName_(viewName), mainViewer_(mainViewer),
IVRoot(NULL), IVHandGeometry(NULL), IVObjectGeometry(NULL), stateID_(-1)
{

  viewViewer = new SoQtRenderArea(&parentWindow, " ",true);  
  viewViewer->setTransparencyType(SoGLRenderAction::SORTED_OBJECT_BLEND);  
  viewWin = &parentWindow;

  //set up IV root
  IVRoot = new SoSeparator();
  SoCamera * cameraTest = mainViewer_->getCamera();
  camera_ = static_cast<SoCamera *>(mainViewer_->getCamera()->copy());
  camera_->scaleHeight(.7);
  camera_->nearDistance = .1;
  camera_->farDistance=1e5;
  //camera->orientation.connectFrom(&mainViewer_->getCamera()->orientation);
  //camera->position.connectFrom(&mainViewer_->getCamera()->position);
  camera_->setName("ViewCamera");
  viewViewer->setSceneGraph(IVRoot);
  
  //Set up camera tied to main view camera
  IVRoot->addChild(camera_);
  
  //Set up lighting to be the same as the main view's lighting
  SoRotation *lightDir = new SoRotation;
  lightDir->rotation.connectFrom(&mainViewer_->getCamera()->orientation);
  SoTransformSeparator *lightSep = new SoTransformSeparator;
  lightSep->addChild(lightDir);
  lightSep->addChild(mainViewer_->getHeadlight());
  IVRoot->addChild(lightSep);
  
  // Initialize the hand geometry node to contain all geometry
  // and add to scene graph
  setupIVHandGeometry(h);
  IVRoot->addChild(IVHandGeometry);
  
  // Initialize object geometry and add to scene graph
  IVObjectGeometry = static_cast<SoSeparator*>(h->getGrasp()->getObject()->getIVRoot()->copy(false));
  IVRoot->addChild(IVObjectGeometry);  
  viewViewer->setBackgroundColor(SbColor(1.0,1.0,1.0));
}



///Handview
//Destructor
HandView::~HandView(){
 //FIXME if segfaulting, this may need to be removed. 
  //IVRoot->unref();
  //fixme - do the rest of these windows need destroying?
  std::cout << "Deleted view " << viewName_.toStdString();
  delete viewViewer;
}


/*
  Copies a scene graph transform in to the link's scene graph.
  This must fail if the link's scene graph does not contain the 
  SoTransform node as its first child - which it must be to work properly
  anyway. Recall that children effect their antecedent peers, 
  so to move the root of the geometry of the link, the SoTransform must 
  precede it in the child list. Always putting it first therefore makes sense. 
*/
void copyIVTran(SoSeparator * parentNode, const SoTransform & ivTran)
{
  SoTransform* tranNode = static_cast<SoTransform *>(ivTran.copy());
  parentNode->removeChild(0);
  parentNode->insertChild(tranNode, 0);
}

/*
    Copies current hand scenegraph transforms to stored scenegraph. 
    Rather than discarding and making a new copy of the scenegraph each time
    the HandView is updated, we keep the old scenegraph and simply update the
    SoTransform node associated with each link within it. This is necessary
    because each body in the Inventor scene graph has its position set independently,
    even when the node is part of an ensemble of bodies such as a robot. The
    joint constraints between bodies are maintained independently of the scene graph. 
*/
void  copyLinkTransforms(Hand * h, SoSeparator * handIVRoot)
{
  std::vector<DynamicBody *> links;

  copyIVTran(static_cast<SoSeparator*>(handIVRoot->getChild(0)),
              *h->getPalm()->getIVTran());

  h->getAllLinks(links);
  
  for(unsigned int i = 0; i < links.size(); ++i)
  {
    copyIVTran(static_cast<SoSeparator*>(handIVRoot->getChild(i+1)), *links[i]->getIVTran());
  }
  
}

/*
  Updates the current scene graph to represent the a new hand/object relationship.
  This does not copy the current scene graph but instead updates the positions
  of the bodies in the scenegraph by updating the SoTransform node associated with
  each body. See CopyLinkTransforms for more details. 
*/

bool
HandView::update(HandObjectState & s, Hand & cloneHand)
{
  double testResult = s.getAttribute("testResult");
  double stateID = s.getAttribute("graspId");
  if(testResult > 0.0)
  {
    viewViewer->setBackgroundColor(SbColor(.8,1,.8));
  }
  else if(testResult <= -1.0)
  {
    viewViewer->setBackgroundColor(SbColor(1,0.8,0.8));
  }

  if(testResult <= 0.0 && testResult >-1.0){
    viewViewer->setBackgroundColor(SbColor(1,1.0,1.0));
  }
  if(stateID_ != stateID)
  {
    stateID_ = stateID;

    //need to activate the collision on the copied hand using the cloned hand
    //container object
    cloneHand.getWorld()->toggleCollisions(true, &cloneHand, s.getObject());

    //execute the grasp
    s.execute(&cloneHand);
    
    copyLinkTransforms(&cloneHand, IVHandGeometry);
  }
  camera_->position = mainViewer_->getCamera()->position;
  camera_->orientation = mainViewer_->getCamera()->orientation;
  camera_->viewAll(IVRoot, viewViewer->getViewportRegion());
  mainViewer_->render();
  viewViewer->render();
  //disable collisions between clone hand and everything  
  cloneHand.getWorld()->toggleCollisions(false, &cloneHand);       
  
  return true;
}


//! Extracts the  IVRoot. FIXME: Why does this currently exist?
SoSeparator * 
HandView::getIVRoot()
{
  return this->IVRoot;
}


//Get name (useful to treat names as Unique IDs - needed to save state of preview Window)
QString
HandView::getName()
{
  return this->viewName_;
}

//Returns a pointer to the rendering area.
SoQtRenderArea * 
HandView::getViewViewer()
{
  return viewViewer;
}

// Set the viewViewer
void
HandView::setViewViewer(SoQtRenderArea * newView)
{
  viewViewer = newView;
  return;
}

//Returns the window itself
QFrame * 
HandView::getViewWindow()
{
  return viewWin;
}


