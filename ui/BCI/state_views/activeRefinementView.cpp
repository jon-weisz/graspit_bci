#include "activeRefinementView.h"
#include "ui_activeRefinementView.h"
#include "BCI/bciService.h"
#include "BCI/onlinePlannerController.h"

using bci_experiment::OnlinePlannerController;

ActiveRefinementView::ActiveRefinementView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveRefinementView)
{
    ui->setupUi(this);

    connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(ui->buttonRotLat, SIGNAL(clicked()), this, SLOT(onRotLat()));
    connect(ui->buttonRotLong, SIGNAL(clicked()), this, SLOT(onRotLong()));

    showSelectedGrasp(NULL);

}


void ActiveRefinementView::onOk()
{
    BCIService::getInstance()->emitGoToNextState1();
}

void ActiveRefinementView::onRotLat()
{
   BCIService::getInstance()->emitRotLat();
}

void ActiveRefinementView::onRotLong()
{
   BCIService::getInstance()->emitRotLong();
}

void ActiveRefinementView::showSelectedGrasp(const GraspPlanningState *graspPlanningState)
{
    SoQtExaminerViewer *mainViewer = graspItGUI->getIVmgr()->getViewer();
    Hand * h = OnlinePlannerController::getInstance()->getGraspDemoHand();
    QFrame *parentWindow = this->ui->previewFrame;
    QString viewName = QString("current best grasp");
    handView = new HandView(mainViewer,h,*parentWindow,viewName);
    if(graspPlanningState)
    {
        handView->update(*graspPlanningState, *h);
    }
}

ActiveRefinementView::~ActiveRefinementView()
{
    delete ui;
}

