#include "graspSelectionView.h"
#include "ui_graspSelectionView.h"
#include "BCI/bciService.h"

using bci_experiment::OnlinePlannerController;

GraspSelectionView::GraspSelectionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraspSelectionView)
{
    ui->setupUi(this);

    spinner = new QtWaitingSpinner(10,7,3,15,ui->renderArea);

    connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(ui->buttonRefineGrasp, SIGNAL(clicked()), this, SLOT(onRefineGrasp()));
    connect(ui->buttonBack, SIGNAL(clicked()), this, SLOT(onBack()));

    //showSpinner();
    showSelectedGrasp(NULL);

}
///////////////////////////////////////////////////
//Button Callbacks
void GraspSelectionView::onRefineGrasp()
{
    BCIService::getInstance()->emitGoToNextState2();
}

void GraspSelectionView::onOk()
{
    BCIService::getInstance()->emitGoToNextState1();
}

void GraspSelectionView::onBack()
{
    BCIService::getInstance()->emitGoToPreviousState();
}

///////////////////////////////////////////////////
//hide/show spinner and handView
void GraspSelectionView::showSpinner()
{
    spinner->setSpeed(1.5);
    spinner->start();
    spinner->move(spinner->parentWidget()->geometry().center()/2.0);
}

void GraspSelectionView::hideSpinner()
{
    spinner->hide();
}

void GraspSelectionView::showSelectedGrasp(const GraspPlanningState *graspPlanningState)
{
    hideSpinner();
    SoQtExaminerViewer *mainViewer = graspItGUI->getIVmgr()->getViewer();
    Hand * h = graspItGUI->getIVmgr()->getWorld()->getCurrentHand();
    QFrame *parentWindow = this->ui->renderArea;
    QString viewName = QString("current best grasp");
    handView = new HandView(mainViewer,h,*parentWindow, viewName);
    if(graspPlanningState)
    {
        handView->update(*graspPlanningState, *h);
    }
}


GraspSelectionView::~GraspSelectionView()
{
    delete ui;
}
