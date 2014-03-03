#include "confirmationView.h"
#include "ui_confirmationView.h"
#include "BCI/bciService.h"

ConfirmationView::ConfirmationView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfirmationView)
{
    ui->setupUi(this);


    connect(ui->buttonOk, SIGNAL(clicked()), this, SLOT(onOk()));
    connect(ui->buttonBack, SIGNAL(clicked()), this, SLOT(onBack()));

}

ConfirmationView::~ConfirmationView()
{
    delete ui;
}


void ConfirmationView::onOk()
{
    BCIService::getInstance()->emitExec();
}

void ConfirmationView::onBack()
{
    BCIService::getInstance()->emitNext();
}
