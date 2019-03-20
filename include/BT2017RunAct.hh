#ifndef BT2017RUNACT_h
#define BT2017RUNACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017RunAct.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for BT2017RunAct class. In addition to the basic   //
// actions, user can add additional user-defined actions.                     //
//                                                                            //
//                    - 21. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4UserRunAction.hh"

#include "BT2017ConMan.hh"

class G4Run;

class BT2017ConMan;

class BT2017RunAct : public G4UserRunAction
{
  public:
	BT2017RunAct(BT2017ConMan* CM);
    virtual ~BT2017RunAct();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
	// Configuration
	BT2017ConMan* m_CM;
	std::vector<G4bool> m_DetSet;
};

#endif
