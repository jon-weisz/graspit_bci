#include "graspSelectionView.h"
#include "ui_graspSelectionView.h"
#include "BCI/bciService.h"

GraspSelectionView::GraspSelectionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraspSelectionView)
{
    ui->setupUi(this);

    this->showSelectedGrasp();

    connect(ui->ok, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(ui->refine_grasp, SIGNAL(clicked()), this, SLOT(onRefineGrasp()));

}

void GraspSelectionView::onRefineGrasp()
{
    BCIService::getInstance()->emitNext();
}

void GraspSelectionView::onOk()
{
    BCIService::getInstance()->emitExec();
}


void GraspSelectionView::showSelectedGrasp()
{

    // create scene root
    SoSeparator *root = new SoSeparator;
    root->ref();

    // camera
    SoQtExaminerViewer *mainViewer_ =  graspItGUI->getIVmgr()->getViewer();
    SoCamera *camera = static_cast<SoCamera *>(mainViewer_->getCamera()->copy());
    root->addChild(camera);

    // light
    root->addChild(new SoDirectionalLight);

    // material
    SoMaterial *material = new SoMaterial;
    material->diffuseColor.setValue(1.0, 0.0, 0.0);
    root->addChild(material);

    //add hand
    Hand *currentHand =   graspItGUI->getIVmgr()->getWorld()->getCurrentHand();
    setupIVHandGeometry(currentHand);
    root->addChild(IVHandGeometry);

    //add object
    IVObjectGeometry = static_cast<SoSeparator*>(currentHand->getGrasp()->getObject()->getIVRoot()->copy(false));
    root->addChild(IVObjectGeometry);

    // create rendering window
    soQtRenderArea = new SoQtRenderArea(ui->renderArea);
    soQtRenderArea->setBackgroundColor(SbColor(1,1,1));

    // camera setup
    camera->viewAll(root, soQtRenderArea->getViewportRegion());

    // rendering window setup
    soQtRenderArea->setSceneGraph(root);
    soQtRenderArea->show();

    // show window and enter main loop
    SoQt::show(ui->renderArea);
}


SoSeparator* GraspSelectionView::buildLinkCopy(Link * l)
{
//    SoSeparator * newRoot = new SoSeparator();
//    SoTransform * newTran = newTran = l->getIVTran()->copy(false);
//    newRoot->addChild(newTran);
//    newRoot->addChild(l->getIVMat());
//    newRoot->addChild(l->getIVGeomRoot());
//    return newRoot;
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
 void GraspSelectionView::setupIVHandGeometry(Hand * h)
{
  //Set up the scene graphs for the hand geometry
  IVHandGeometry = new SoSeparator;
  //copy palm geometry
  IVHandGeometry->addChild(h->getPalm()->getIVRoot()->copy(false));
  //IVHandGeometry->addChild(buildLinkCopy(h->getPalm()));
  std::vector<DynamicBody *> links;

  //Get link pointers
  h->getAllLinks(links);

  //copy link geometry
  for(unsigned int i = 0; i < links.size(); ++i)
  {
    IVHandGeometry->addChild(links[i]->getIVRoot()->copy(false));
     // IVHandGeometry->addChild(buildLinkCopy(links.at(i)));
  }
}

GraspSelectionView::~GraspSelectionView()
{
    delete ui;
}
