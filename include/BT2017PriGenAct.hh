#ifndef BT2017PRIGENACT_h
#define BT2017PRIGENACT_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017PriGenAct.hh for beamtest2017 of JEDI                              //
//                                                                            //
//   This file is a header for BT2017PriGenAct class. You can set primary     //
// beam options in this class.                                                //
//                                                                            //
//                    - 21. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"

#include "BT2017ConMan.hh"

class G4ParticleGun;

class BT2017ConMan;

class BT2017PriGenAct: public G4VUserPrimaryGeneratorAction
{
  private:
	G4ParticleGun* PG;

  public:
	BT2017PriGenAct(BT2017ConMan* CM);
	~BT2017PriGenAct();

	virtual void GeneratePrimaries(G4Event* anEvent);

  private:
	BT2017ConMan* m_CM;

	G4double m_BeamPX, m_BeamPY;
	G4double m_BeamDX, m_BeamDY;
	G4double m_WorldZ;
	G4ThreeVector m_GunPos;
	G4ParticleDefinition* m_Par;
	G4ThreeVector m_MomDir;
	G4double m_Mom;
	G4double m_KinEgy;
	G4ThreeVector m_Pol;
};

#endif
