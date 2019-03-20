////////////////////////////////////////////////////////////////////////////////
//   BT2017EveAct.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of BT2017EveAct class's member functions. Details of user    //
// actions are here.                                                          //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4Event.hh"
#include "G4SystemOfUnits.hh"

#include "BT2017EveAct.hh"
#include "BT2017Ana.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
BT2017EveAct::BT2017EveAct(BT2017ConMan* CM)
	: m_CM(CM)
{
	m_DetSet = m_CM -> GetDetSet();
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
BT2017EveAct::~BT2017EveAct()
{
}

//////////////////////////////////////////////////
//   Begin of event action                      //
//////////////////////////////////////////////////
void BT2017EveAct::BeginOfEventAction(const G4Event* /*anEvent*/)
{
	// Initialize
	m_EDepCry.clear();
	for ( int i = 0; i < 120; i++ ) m_EDepCry[i] = 0.0;
	m_EDepdE = 0.0;	
}

//////////////////////////////////////////////////
//   End of event action                        //
//////////////////////////////////////////////////
void BT2017EveAct::EndOfEventAction(const G4Event* anEvent)
{
	// Get analysis manager
	G4AnalysisManager* AM = G4AnalysisManager::Instance();

	// Fill ntuple with result
	G4int eID = anEvent -> GetEventID();
	AM -> FillNtupleIColumn(0, eID);
	G4int iDet = 1;
	for ( int i = 0; i < 120; i++ )
		if ( m_DetSet[i] )
		{
			AM -> FillNtupleDColumn(iDet, m_EDepCry[i]);
			iDet++;
		}
	AM -> FillNtupleDColumn(iDet, m_EDepdE);
	AM -> AddNtupleRow();
}

//////////////////////////////////////////////////
//   Add energy deposition                      //
//////////////////////////////////////////////////
void BT2017EveAct::AddEDepCry(G4int id, G4double eD)
{
	m_EDepCry[id] += eD;
}

void BT2017EveAct::AddEDepdE(G4double eD)
{
	m_EDepdE += eD;
}
