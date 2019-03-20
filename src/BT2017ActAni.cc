////////////////////////////////////////////////////////////////////////////////
//   BT2017ActIni.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of BT2017ActIni class's member functions.                    //
// All actions must be initialized here in order to use multi thread.         //
//                                                                            //
//                    - 28. Feb. 2018. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////


#include "BT2017ActIni.hh"
#include "BT2017PriGenAct.hh"
#include "BT2017RunAct.hh"
#include "BT2017EveAct.hh"
#include "BT2017SteAct.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
BT2017ActIni::BT2017ActIni(BT2017ConMan* CM)
	: G4VUserActionInitialization(), m_CM(CM)
{
	// Pointer of configuration manager class is initialized
	// when this class is constructed. (CM object)
	// This pointer will be delivered to user actions.
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
BT2017ActIni::~BT2017ActIni()
{
}

//////////////////////////////////////////////////
//   Build For Master                           //
//////////////////////////////////////////////////
void BT2017ActIni::BuildForMaster() const
{
	// So, this part is for master. This program is possible to do multithread.
	// A thread will care things as a master.

	// Master thread must have this.
	SetUserAction(new BT2017RunAct(m_CM));
}

//////////////////////////////////////////////////
//   Build                                      //
//////////////////////////////////////////////////
void BT2017ActIni::Build() const
{
	// All user actions are here.
	SetUserAction(new BT2017PriGenAct(m_CM));
	SetUserAction(new BT2017RunAct(m_CM));
  
	BT2017EveAct* BT2017EA = new BT2017EveAct(m_CM);
	SetUserAction(BT2017EA);
  
	SetUserAction(new BT2017SteAct(BT2017EA));
}
