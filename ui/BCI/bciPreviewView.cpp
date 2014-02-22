#include "bciPreviewView.h"
#include "ui_bciPreviewView.h"

BCIPreviewView::BCIPreviewView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BCIPreviewView)
{
    ui->setupUi(this);
}

BCIPreviewView::~BCIPreviewView()
{
    delete ui;
}
