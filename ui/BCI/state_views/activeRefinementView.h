#ifndef ACTIVEREFINEMENTVIEW_H
#define ACTIVEREFINEMENTVIEW_H

#include <QWidget>

namespace Ui {
class ActiveRefinementView;
}

class ActiveRefinementView : public QWidget
{
    Q_OBJECT
    
public:
    explicit ActiveRefinementView(QWidget *parent = 0);
    ~ActiveRefinementView();

public slots:
    void onOk();
    void onRotLat();
    void onRotLong();
    
private:
    Ui::ActiveRefinementView *ui;
};

#endif // ACTIVEREFINEMENTVIEW_H
