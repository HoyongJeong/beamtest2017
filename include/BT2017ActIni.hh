#ifndef BT2017ACTINI_h
#define BT2017ACTINI_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017ActIni.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for BT2017ActIni class. Every actions are          //
// initialized through this class.                                            //
//                                                                            //
//                    - 22. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4VUserActionInitialization.hh"
#include "G4String.hh"

#include "BT2017ConMan.hh"

class BT2017ConMan;

class BT2017ActIni : public G4VUserActionInitialization
{
  public:
	BT2017ActIni(BT2017ConMan* CM);
	virtual ~BT2017ActIni();

	virtual void BuildForMaster() const;
	virtual void Build() const;

  private:
	// Configuration manager
	BT2017ConMan* m_CM;
};

#endif
