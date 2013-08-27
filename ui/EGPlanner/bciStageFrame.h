#ifndef BCISTAGEFRAME_H_
#define BCISTAGEFRAME_H_
#include "ui_bciStageFrame.h"
#include "ivmgr.h"

class BciStageFrame : public QFrame, public Ui::UserGuideWindow 
{
  Q_OBJECT

public:
  BciStageFrame(){
    setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->show();

  }
  void setUpState(char * currentName, char * button1string, char * button2string)
    {
      currentStageName->setText(currentName);
      button1ActionText->setText(button1string);
      button2ActionText->setText(button2string);
    }

  void setBCIState(BciPlanningState * currentState, BciPlanningState nextState)
    {
      *currentState = nextState;
      switch(nextState)
	{	  
	case INITIALIZATION_PHASE:
	  {
	    setUpState("Initialization Phase", "Rerun Vision", "Initialize");
	    break;
	  }
	case OBJECT_SELECTION_PHASE:
	  {
	    setUpState("Object Selection", "Next Object","Select Object");
	    break;
	  }
	case INITIAL_REVIEW_PHASE:  
	  {	    
	    setUpState("Initial Review Phase", "Next Grasp", "Select Grasp");
	    break;
	  }
	case START_PHASE:
	  {
	    setUpState("Start Phase", "Select Grasp", "Start Planner");
	    break;
	  }
	case PLANNING_PHASE:
	  {
	    setUpState("Planning Phase", "Next Grasp", "Enter Review Phase");
	    break;
	  }
	case FINAL_REVIEW_PHASE:
	  {
	    setUpState("Final Review Phase","Next Grasp","Select Grasp");
	    break;
	  }
	
	case CONFIRM_PHASE:
	  {
	    setUpState("Confirm Phase", "Re-Plan Grasp","Confirm Grasp");
	    break;
	  }
	case EXECUTION_PHASE:
	  {
  	    setUpState("Execution Phase", "Re-Plan Grasp","Execute Grasp");
	    break;
	  }
	  
	}
      
    }

public slots:
  void blinkArea1()
  {    
    CurrentStageArea_2->setBackgroundColor(QColor(255,255,255));

    QTimer::singleShot(100, this, SLOT(restoreArea1()));

  };
  void blinkArea2()
  {
    CurrentStageArea_3->setBackgroundColor(QColor(255,255,255));

    QTimer::singleShot(100, this, SLOT(restoreArea2()));
  };
void restoreArea1()
{
  CurrentStageArea_2->setBackgroundColor(QColor(255,0,0));
};

void restoreArea2()
{
  CurrentStageArea_3->setBackgroundColor(QColor(0,255,0));
};

};



#endif
