#ifndef BCIPREVIEWVIEW_H
#define BCIPREVIEWVIEW_H

#include <QWidget>

namespace Ui {
class BCIPreviewView;
}

class BCIPreviewView : public QWidget
{
    Q_OBJECT
    
public:
    explicit BCIPreviewView(QWidget *parent = 0);
    ~BCIPreviewView();
    
private:
    Ui::BCIPreviewView *ui;
};

#endif // BCIPREVIEWVIEW_H
