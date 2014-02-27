#ifndef BCICONTROLWINDOW_H
#define BCICONTROLWINDOW_H




#include <QDialog>
#include "ui_BCIControlWindowBase.h"
#include "BCI/uiTools.h"
#include "BCI/bciService.h"
#include "debug.h"

class BCIControlWindow: public QDialog, public Ui::BCIControlWindowBase
{

    Q_OBJECT

public:


    BCIControlWindow(QWidget *parent = 0 )
        :QDialog(parent)
    {
        setupUi(this);

        connect(button1, SIGNAL(clicked()), this, SLOT(onButton1Clicked()));
        connect(button2, SIGNAL(clicked()), this, SLOT(onButton2Clicked()));
        connect(button3, SIGNAL(clicked()), this, SLOT(onButton3Clicked()));
        connect(button4, SIGNAL(clicked()), this, SLOT(onButton4Clicked()));
    }



public slots:

    void onButton1Clicked(){
        BCIService::getInstance()->emitExec();
    }

    void onButton2Clicked(){
        BCIService::getInstance()->emitNext();
    }

    void onButton3Clicked(){
        BCIService::getInstance()->emitRotLat();
    }

    void onButton4Clicked(){
        BCIService::getInstance()->emitRotLong();
    }

};


#endif // BCICONTROLWINDOW_H
