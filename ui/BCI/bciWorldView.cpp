#include "bciWorldView.h"
#include "ui_bciWorldView.h"

BCIWorldView::BCIWorldView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BCIWorldView)
{
    ui->setupUi(this);

    SoQtRenderArea * render = new SoQtRenderArea(this, " ",true);


    SoSeparator * testRoot = new SoSeparator;
    SoNode *ivRoot = graspItGUI->getIVmgr()->getViewer()->getSceneGraph();

    SoMaterial * testMaterial = new SoMaterial;

    testMaterial->diffuseColor.setValue(1,0,0);
    testRoot->addChild(graspItGUI->getIVmgr()->getViewer()->getCamera());
    SoTransformSeparator *lightSep = new SoTransformSeparator;
    SoRotation *lightDir = new SoRotation;
    lightDir->rotation.connectFrom(&graspItGUI->getIVmgr()->getViewer()->getCamera()->orientation);
    lightSep->addChild(lightDir);
    lightSep->addChild(graspItGUI->getIVmgr()->getViewer()->getHeadlight());
    SoLightModel * model = new SoLightModel;
    model->model=SoLightModel::PHONG;
    testRoot->addChild(lightSep);
    testRoot->addChild(model);
    testRoot->addChild(ivRoot);
    render->setSceneGraph(testRoot);
    render->setBackgroundColor(SbColor(1,1,1));
    render->scheduleRedraw();
    render->render();
    render->show();
}

BCIWorldView::~BCIWorldView()
{
    delete ui;
}
