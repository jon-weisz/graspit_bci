#ifndef BCISERVICE_H
#define BCISERVICE_H

#include <QObject>

class BCIStateMachine;
class GraspableBody;
class DrawableFrame;
class GraspPlanningState;


class BCIService:public QObject
{

    Q_OBJECT

public:


    void emitExec(){emit exec();}
    void emitNext(){emit next();}
    void emitTargetBodyChanged(GraspableBody * b){emit targetBodyChanged(b);}
    void emitResetStateMachine(){resetStateMachine();}
    void emitCursorPosition(double x, double y){emit cursorPosition(x,y);}
    void emitDrawableFrame(DrawableFrame *drawableFrame){emit drawShapes(drawableFrame);}
    void emitRotLat(){emit rotLat();}
    void emitRotLong(){emit rotLong();}

    void emitAnalyzeGrasp(const GraspPlanningState * gps) {emit analyzeGrasp(gps); }
    void emitAnalyzeNextGrasp() {emit analyzeNextGrasp(); }
    void emitRunObjectRecognition(){emit runObjectRecognition();}

    void emitSendString(const QString & s){emit sendString(s);}


    void emitAnalyzeApproachDir(GraspPlanningState * gs){emit analyzeApproachDir(gs);}


    static BCIService* getInstance();

signals:


    //! Signal to planner to execute
    void exec();

    //! Signal to planner to go to next state
    void next();

    //! Target body changed
    void targetBodyChanged(GraspableBody * b);

    //! Reset the current state machine
    void resetStateMachine();

    //! signal to give cursor position for binary message cursor
    void cursorPosition(double x, double y);

    //! signal to have something draw 2D shapes
    void drawShapes(DrawableFrame *drawableFrame);

    //! signal to rotate the hand longitudinally around the target object
    void rotLong();

    //! signal to rotate the hand latitudinally around the target object
    void rotLat();

    //! Signal that object recognition system should be rerun
    void runObjectRecognition();
    void sendString(const QString & s);

    // determine reachability of the grasp at this index
    void analyzeGrasp(const GraspPlanningState * gps);
    void analyzeNextGrasp();
    void analyzeApproachDir(GraspPlanningState * gps);


private:
        static BCIService * bciServiceInstance;
};

#endif // BCISERVICE_H
