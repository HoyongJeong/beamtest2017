////////////////////////////////////////////////////////////////////////////////
//   BT2017PriGenAct.cc for beamtest2017 of JEDI                              //
//                                                                            //
//   Definitions of BT2017PriGenAct class's member functions.                 //
//                                                                            //
//                    - 21. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////


#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

#include "BT2017PriGenAct.hh"

//////////////////////////////////////////////////
//   Constructor and destructor                 //
//////////////////////////////////////////////////
BT2017PriGenAct::BT2017PriGenAct(BT2017ConMan* CM)
	: m_CM(CM)
{
	PG = new G4ParticleGun();

	// Gun position
	m_WorldZ = m_CM -> GetWorldZ();
	m_BeamPX = m_CM -> GetBeamPX();
	m_BeamPY = m_CM -> GetBeamPY();
	m_BeamDX = m_CM -> GetBeamDX();
	m_BeamDY = m_CM -> GetBeamDY();

	// Set particle definition
	G4ParticleTable* PT = G4ParticleTable::GetParticleTable();
	m_Par = PT -> FindParticle("deuteron");
	PG -> SetParticleDefinition(m_Par);

	// Momentum
	m_MomDir = G4ThreeVector(0., 0., 1.);
	PG -> SetParticleMomentumDirection(m_MomDir);

	// Kinetic energy
	m_KinEgy = m_CM -> GetBeamKE();
	PG -> SetParticleEnergy(m_KinEgy);

	// Polarization
	m_Pol = G4ThreeVector(0., 1., 0.);
	PG -> SetParticlePolarization(m_Pol);
}

BT2017PriGenAct::~BT2017PriGenAct()
{
	delete PG;
}


//////////////////////////////////////////////////
//   Shoot!                                     //
//////////////////////////////////////////////////
void BT2017PriGenAct::GeneratePrimaries(G4Event* anEvent)
{
	// 2D Gaussian
	G4double dX = G4RandGauss::shoot(0., m_BeamDX / mm / 3.0); // 3 sigma
	G4double dY = G4RandGauss::shoot(0., m_BeamDY / mm / 3.0); // 3 sigma
	m_GunPos = G4ThreeVector(m_BeamPX + dX * mm, m_BeamPY + dY * mm, - m_WorldZ/2);
//	G4cout << m_GunPos << G4endl;
	PG -> SetParticlePosition(m_GunPos);

	PG -> GeneratePrimaryVertex(anEvent);
}
