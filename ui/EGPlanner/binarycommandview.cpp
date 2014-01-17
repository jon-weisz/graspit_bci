#include "binarycommandview.h"
#include "Drawable.pb.h"

BinaryCommandView::BinaryCommandView(QWidget * parent) :QWidget(parent)
{
    currentFrame = new DrawableFrame;
}


void BinaryCommandView::paintEvent(QPaintEvent *ev)
{

   QPainter painter(this);
   painter.setBrush(Qt::blue);
   float vwidth = width();//painter.viewport().width();
   float vheight= height();//painter.viewport().height();
   double cursorRadius = .3/7.5*vwidth;

   painter.drawEllipse(cursorX*vwidth + cursorRadius, vheight - (cursorY*vheight+cursorRadius), cursorRadius, cursorRadius);

   double rectWidth = 1.0/7.5*width();
   double rect1XOffset = 2.5/7.5*width();
   double rect2XOffset = 4.5/7.5*width();
   double rect3XOffset = 6.5/7.5*width();

   painter.drawRect(QRect(rect1XOffset,0,rectWidth,height()));
   painter.drawRect(QRect(rect2XOffset,0,rectWidth,height()));
   painter.drawRect(QRect(rect3XOffset,0,rectWidth,height()));

   QPointF boundaryPoint1 = QPointF(0,height() - 2/7.5*height());
   QPointF boundaryPoint2 = QPointF(width(),height() - 2/7.5*height());

   painter.drawLine(boundaryPoint1, boundaryPoint2);
}

void BinaryCommandView::updateCursor(double x, double y)
{
    cursorX = x/7.5;
    cursorY = y/7.5;
    update();
}


QObject * shapeDrawableToQObject(ShapeDrawable & shape)
{
    shape.
}

 void BinaryCommandView::updateFrame(DrawableFrame & drawing)
 {

 }
