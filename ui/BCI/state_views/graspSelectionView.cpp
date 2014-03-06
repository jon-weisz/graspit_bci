#include "graspSelectionView.h"
#include "ui_graspSelectionView.h"
#include "BCI/bciService.h"
#include "BCI/handView.h"


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

    showSpinner();

}

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

void GraspSelectionView::onRefineGrasp()
{
    BCIService::getInstance()->emitGoToNextState2();
}

void GraspSelectionView::onOk()
{
    BCIService::getInstance()->emitExec();
}

void GraspSelectionView::onBack()
{
    BCIService::getInstance()->emitGoToPreviousState();
}


void GraspSelectionView::showSelectedGrasp()
{
    SoQtExaminerViewer *mainViewer = graspItGUI->getIVmgr()->getViewer();
    Hand * h = graspItGUI->getIVmgr()->getWorld()->getCurrentHand();
    QFrame *parentWindow = this->ui->renderArea;
    QString viewName = QString("current best grasp");
    HandView *handView = new HandView(mainViewer,h,*parentWindow,viewName);
}


GraspSelectionView::~GraspSelectionView()
{
    delete ui;
}
