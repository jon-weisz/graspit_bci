#ifndef BCICONTROLWINDOW_H
#define BCICONTROLWINDOW_H




#include <QDialog>
#include "ui_BCIControlWindowBase.h"
#include "BCI/uiTools.h"

class BCIControlWindow: public QDialog, public Ui::BCIControlWindowBase
{
public:


    BCIControlWindow(QWidget *parent = 0 )
        :QDialog(parent)
    {
        setupUi(this);
    }

};




#endif // BCICONTROLWINDOW_H
