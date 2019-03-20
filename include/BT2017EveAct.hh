#ifndef BT2017EVEACT_h
#define BT2017EVEACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017EveAct.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for BT2017EveAct class. User can add user-defined  //
// event action in this class.                                                //
//                                                                            //
//                    - 22. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4UserEventAction.hh"
#include "G4String.hh"
#include <map>

#include "BT2017ConMan.hh"

class G4Event;

class BT2017ConMan;

class BT2017EveAct: public G4UserEventAction
{
  public:
	BT2017EveAct(BT2017ConMan* CM);
	virtual ~BT2017EveAct();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);

	void AddEDepCry(G4int, G4double);
	void AddEDepdE(G4double);

  private:
	std::map<G4int, G4double> m_EDepCry;
	G4double m_EDepdE;
	BT2017ConMan* m_CM;
	std::vector<G4bool> m_DetSet;
};

#endif
