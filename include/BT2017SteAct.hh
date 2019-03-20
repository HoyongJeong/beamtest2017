#ifndef BT2017STEACT_h
#define BT2017STEACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017SetAct.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for BT2017SteAct class. User can add user-defined  //
// stepping action in this class. So this class works at every step.          //
// The most busiest class. :)                                                 //
//                                                                            //
//                    - 23. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4UserSteppingAction.hh"
#include "BT2017EveAct.hh"
#include "BT2017DetMap.hh"

class BT2017EveAct;

class BT2017SteAct : public G4UserSteppingAction
{
  public:
	BT2017SteAct(BT2017EveAct* EA);
	virtual ~BT2017SteAct();

	virtual void UserSteppingAction(const G4Step*);

  private:
	BT2017EveAct* m_EA;
	BT2017DetMap* m_DM;
};

#endif
