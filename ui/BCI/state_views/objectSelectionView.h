#ifndef OBJECTSELECTIONVIEW_H
#define OBJECTSELECTIONVIEW_H

#include <QWidget>


#include<Inventor/nodes/SoSeparator.h>
#include<Inventor/nodes/SoMaterial.h>
#include<Inventor/nodes/SoTransformSeparator.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoLightModel.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoQtRenderArea.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoRotationXYZ.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/engines/SoElapsedTime.h>

#include "graspitGUI.h"
#include "ivmgr.h"
#include "body.h"
#include "world.h"
#include "robot.h"
#include "grasp.h"

namespace Ui {
class ObjectSelectionView;
}

class ObjectSelectionView : public QWidget
{
    Q_OBJECT
    
public:
    explicit ObjectSelectionView(QWidget *parent = 0);
    void showSelectedObject(GraspableBody * currentTarget);
    ~ObjectSelectionView();
    
private:

    Ui::ObjectSelectionView *ui;
    SoQtRenderArea *soQtRenderArea;
    SoSeparator * IVObjectGeometry;
    SoSeparator *root;

    void initRenderArea();

public slots:
    void onSelect();
    void onNext();
};

#endif // OBJECTSELECTIONVIEW_H
