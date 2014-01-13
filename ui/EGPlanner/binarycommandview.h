
#ifndef BINARYCOMMANDVIEW_H
#define BINARYCOMMANDVIEW_H

#include <QPainter>
#include<QWidget>

class BinaryCommandView: public QWidget
{
    Q_OBJECT
public:
    BinaryCommandView(QWidget * parent);

    virtual void updateCursor(double, double);

protected:
    double cursorX;
    double cursorY;
    void paintEvent(QPaintEvent*);
signals:
public slots:

};

#endif // BINARYCOMMANDVIEW_H

