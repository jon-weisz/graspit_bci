#include "objectSelectionView.h"
#include "ui_objectSelectionView.h"
#include "BCI/bciService.h"
#include "debug.h"

ObjectSelectionView::ObjectSelectionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectSelectionView)
{
    ui->setupUi(this);


    connect(ui->next, SIGNAL(clicked()), this, SLOT(onNext()));
    connect(ui->select, SIGNAL(clicked()), this, SLOT(onSelect()));

}


void ObjectSelectionView::onNext()
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
}
