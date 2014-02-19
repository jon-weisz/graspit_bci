#ifndef UITOOLS_H
#define UITOOLS_H


namespace bci_experiment{

World * getWorld();

//! Gets first object that matches the given name.
Body * getObjectByName(const QString & objectName);

//! Brief helper to add an object to the world from relative directory, model type, and model filename.
Body * addToWorld(const QString & relativeModelDir,
                  const QString & modelType,
                  const QString & modelFilename);

//! If the named body doesn't exist, add it to the world
Body * addBodyIfUnique(const QString & bodyName);


//! Make a particular body a particular color
void highlightBody(Body * b, SbColor color);


//! Get a particular body if it exists
Body * getObjectByName(const QString & objectName);


//! Remove any existing highlighting on a body
void unhighlightBody(Body * b);

//! Get the next body in the graspable body list
GraspableBody * getNextGraspableBody(GraspableBody * b);

//! Find the index of a given body in the world's graspable body vector
int getGraspableBodyIndex(Body * b);

//! Highlight the next graspable body according to graspable body index
GraspableBody * highlightNextGraspableBody(GraspableBody *b);

//! Unhighlight all graspable bodies
bool unhighlightAll();

//! Highlight all graspable bodies
bool highlightAll();


//! Move the given body by some relative transform
void moveBody(Body * b, const transf & relTran);

//!Move all graspable bodies by some relative transform
void moveAllBodies(const transf & relTran)

//! Add an experiment table to world or get a pointer to an existing one
Body * getOrAddExperimentTable();

//!Move this body to the origin of the world and shift all other bodies to
//!maintain their position relative to this body
void setObjectCentral(Body * b);

//! Tell the graspit socket server to emit an arbitrary string
void sendString(const QString & s);


//! send a message on the graspit server to inform a listener that a planning
//! target has been chosen
void sendSetTarget(Body * b);

//! Tell the hand to ignore all bodies that aren't the target.
void disableNontargetCollisions(Hand * h, GraspableBody * target);


//! Determine if the experiment table can collide with objects
void setTableObjectCollisions(bool setting);

//!Tell the table not to collide with any graspable objects
void disableTableObjectCollisions();

//! Change the view to focus on all of the bodies given
void viewBodies(std::vector<Body *> & body_vec);


//! Change the view to focus on all of the graspable bodies in the scene
void viewGraspableBodies();

//!Focus the camera on the hand
void viewHand(Hand * h);


//! Focus the hand on a target object
void viewTarget(Body * b);

//! Change the point cloud transparency
bool setPointcloudTransparency(double transparency);

//! Verify that the pregrasp and grasp states are not in collision
bool testGraspCollisions(Hand * h, const GraspPlanningState * s);


//! Verify that the pregrasp is not in collision
bool testPreGraspCollisions(Hand * h, float pregrasp_dist);


//! Count number of collisions on the hand
int getNumHandCollisions(Hand * h);


//! Determine whether collisions are allowed between the hand and all bodies in the world independently
bool setCollisionState(Hand * h, std::vector<bool> & collisionStatus);

//! Set the collision status after storing the current collision status between all objects in the world and the hand
void resetHandCollisions(Hand * h, bool setting, std::vector<bool> & collisionStatus);


}

#endif // UITOOLS_H
