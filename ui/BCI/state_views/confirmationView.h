#ifndef CONFIRMATIONVIEW_H
#define CONFIRMATIONVIEW_H

#include <QWidget>

namespace Ui {
class ConfirmationView;
}

class ConfirmationView : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConfirmationView(QWidget *parent = 0);
    ~ConfirmationView();
    
public slots:
    void onOk();
    void onBack();

private:
    Ui::ConfirmationView *ui;
};

#endif // CONFIRMATIONVIEW_H
