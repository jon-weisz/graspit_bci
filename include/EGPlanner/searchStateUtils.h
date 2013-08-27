#ifndef SEARCH_STATE_UTILS_H_
#define SEARCH_STATE_UTILS_H_
#include "searchState.h"
#include "matvecIO.h"

template <class streamtype>
streamtype & operator<<(streamtype & os, const VariableSet & vs)
{
  // os << vs.getType() << " ";
  //os << vs.getNumVariables();
  for (int i=0; i < vs.getNumVariables(); ++i)
    os << vs.getVariable(i)->getValue() << " ";
  //os << '\n';
  return os;

}

template <class streamtype>
streamtype & operator<<( streamtype & os,  const HandObjectState & vs)
{
  os << *vs.readPosture() << *vs.readPosition();
  return os;

}


template <class streamtype>
streamtype & operator<<( streamtype & os,  const GraspPlanningState & vs)
{
  os << vs.readPosition()->getCoreTran().rotation().w << ' ' << vs.readPosition()->getCoreTran().rotation().x << ' ' << vs.readPosition()->getCoreTran().rotation().y << ' ' << vs.readPosition()->getCoreTran().rotation().z << ' '
     << vs.readPosition()->getCoreTran().translation().x() << ' ' << vs.readPosition()->getCoreTran().translation().y() << ' ' << vs.readPosition()->getCoreTran().translation().z() << ' ' 
     << *vs.readPosture() 
     << vs.getEpsilonQuality() <<' ' << vs.getVolume();
  
  const std::vector<double> * qm = vs.getQualityMeasures();
  
  for(std::vector<double>::const_iterator quality_iter = qm->begin(); quality_iter != qm->end(); ++quality_iter )
    os << ' ' << *quality_iter;
  
  
  return os;

}



#endif
