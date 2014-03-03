#include "objectSelectionView.h"
#include "ui_objectSelectionView.h"
#include "BCI/bciService.h"

ObjectSelectionView::ObjectSelectionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectSelectionView)
{
    ui->setupUi(this);

    initRenderArea();

    connect(ui->next, SIGNAL(clicked()), this, SLOT(onNext()));
    connect(ui->select, SIGNAL(clicked()), this, SLOT(onSelect()));
    connect(ui->prev, SIGNAL(clicked()), this, SLOT(onPrev()));

}

void ObjectSelectionView::initRenderArea()
{
    // create scene root
    root = new SoSeparator;
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


    // create rendering window
    soQtRenderArea = new SoQtRenderArea(ui->rendeArea);
    soQtRenderArea->setBackgroundColor(SbColor(1,1,1));

    // camera setup
    camera->viewAll(root, soQtRenderArea->getViewportRegion());

    // rendering window setup
    soQtRenderArea->setSceneGraph(root);
    soQtRenderArea->show();

    // show window and enter main loop
    SoQt::show(ui->rendeArea);
}

void ObjectSelectionView::showSelectedObject(GraspableBody *newTarget)
{
    //add new target
    if(newTarget)
    {
        SoNode* newTargetNode = newTarget->getIVRoot()->copy(false);

        root->removeAllChildren();

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

        root->addChild(newTargetNode);
    }


    soQtRenderArea->show();
}

void ObjectSelectionView::onNext()
{
    BCIService::getInstance()->emitNext();
}

void ObjectSelectionView::onPrev()
{
    BCIService::getInstance()->emitNext();
}


void ObjectSelectionView::onSelect()
{
    BCIService::getInstance()->emitExec();
}



ObjectSelectionView::~ObjectSelectionView()
{
    delete ui;
    delete soQtRenderArea;
}
