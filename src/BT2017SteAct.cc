////////////////////////////////////////////////////////////////////////////////
//   BT2017SteAct.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of BT2017SteAct class's member functions. Details of user    //
// actions are here.                                                          //
//                                                                            //
//                    - 21. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4VProcess.hh"

#include "BT2017SteAct.hh"
#include "BT2017EveAct.hh"

//////////////////////////////////////////////////
//   Constructor                                //
//////////////////////////////////////////////////
BT2017SteAct::BT2017SteAct(BT2017EveAct* EA)
	: G4UserSteppingAction(), m_EA(EA)
{
	m_DM = new BT2017DetMap();
}

//////////////////////////////////////////////////
//   Destructor                                 //
//////////////////////////////////////////////////
BT2017SteAct::~BT2017SteAct()
{
	delete m_DM;
}

//////////////////////////////////////////////////
//   User stepping action                       //
//////////////////////////////////////////////////
void BT2017SteAct::UserSteppingAction(const G4Step* step)
{
	// I wrote examples of some information which can be extracted from a step.
	// Uncomment whatever you want to use.

	// Who am I? Where am I? What am I undergoing?
	// // Track ID
//	G4int trackID = step -> GetTrack() -> GetTrackID();
	// // Particle name
//	G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();
	// // Particle ID
//	G4int parID = step -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
	// // Particle charge
//	G4int parCharge = step -> GetTrack() -> GetDefinition() -> GetPDGCharge();
	// // Process name
//	const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();
//	G4String procName = step -> GetPostStepPoint() -> GetProcessDefinedStep() -> GetProcessName();
	// // Physical volume
	G4String namePrePV = step -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName();
//	G4String namePostPV;
//	G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
//	if ( postPV != 0 ) namePostPV = postPV -> GetName();
//	else namePostPV = "outside";
	// // Status
//	G4StepStatus preStat = step -> GetPreStepPoint() -> GetStepStatus();
//	G4StepStatus postStat = step -> GetPostStepPoint() -> GetStepStatus();
	// // Position
//	G4ThreeVector prePos = step -> GetPreStepPoint() -> GetPosition();
//	G4ThreeVector postPos = step -> GetPostStepPoint() -> GetPosition();
	// // Momentum
//	G4ThreeVector preMom = step -> GetPreStepPoint() -> GetMomentum();
//	G4ThreeVector postMom = step -> GetPostStepPoint() -> GetMomentum();
	// // Kinetic energy
//	G4double preKinEgy = step -> GetPreStepPoint() -> GetKineticEnergy();
//	G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();
	// // Energy deposition
	G4double eDep = step -> GetTotalEnergyDeposit();

	// Send information to the event action object.
	if ( namePrePV.contains("cryPV") )
		m_EA -> AddEDepCry(m_DM -> GetDetIDFromDetName(namePrePV.remove(6)), eDep);

	if ( namePrePV == "dEPV" )
		m_EA -> AddEDepdE(eDep);
}
