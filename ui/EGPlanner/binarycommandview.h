
#ifndef BINARYCOMMANDVIEW_H
#define BINARYCOMMANDVIEW_H

#include <QPainter>
#include<QWidget>
class DrawableFrame;

class BinaryCommandView: public QWidget
{
    Q_OBJECT
public:
    BinaryCommandView(QWidget * parent);

    virtual void updateCursor(double, double);
public slots:
    virtual void updateFrame(DrawableFrame & drawing);

protected:
    double cursorX;
    double cursorY;
    DrawableFrame * currentFrame;
    void paintEvent(QPaintEvent*);
signals:


};

#endif // BINARYCOMMANDVIEW_H

