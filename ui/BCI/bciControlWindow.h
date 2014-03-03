#ifndef BCICONTROLWINDOW_H
#define BCICONTROLWINDOW_H




#include <QDialog>
#include "ui_BCIControlWindowBase.h"
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
    }

};


#endif // BCICONTROLWINDOW_H
