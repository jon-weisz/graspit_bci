#include "activeRefinementView.h"
#include "ui_activeRefinementView.h"
#include "BCI/bciService.h"

ActiveRefinementView::ActiveRefinementView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActiveRefinementView)
{
    ui->setupUi(this);

    connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(ui->buttonRotLat, SIGNAL(clicked()), this, SLOT(onRotLat()));
    connect(ui->buttonRotLong, SIGNAL(clicked()), this, SLOT(onRotLong()));
}

ActiveRefinementView::~ActiveRefinementView()
{
    delete ui;
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
