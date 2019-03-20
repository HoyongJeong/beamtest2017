#ifndef BT2017DETCON_h
#define BT2017DETCON_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017DetCon.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for BT2017DetCon class. It's for construction of   //
// whole geometry of simulation, which includes target geometry and detector  //
// geometry. Details of configuration can be set at config.cfg file. The      //
// configuration is tranfered at main function and used here to generate      //
// world of simulation.                                                       //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////


#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4SubtractionSolid.hh"

#include "BT2017ConMan.hh"


class G4VPhysicalVolume;

class BT2017ConMan;

class BT2017DetCon : public G4VUserDetectorConstruction
{
  public:
	BT2017DetCon(BT2017ConMan* CM);
	virtual ~BT2017DetCon();
	virtual G4VPhysicalVolume* Construct();

  private:
	void DefineDimensions();
	void ConstructMaterials();
	void DestructMaterials();
	void ConstructCrystal(G4String, G4int, G4int, G4int, G4int);

  private:
	// Configuration manager
	BT2017ConMan* m_CM;

	// Elements
	G4Element* m_ElH;
	G4Element* m_ElC;
	G4Element* m_ElN;
	G4Element* m_ElO;
	G4Element* m_ElF;
	G4Element* m_ElMg;
	G4Element* m_ElAl;
	G4Element* m_ElSi;
	G4Element* m_ElAr;
	G4Element* m_ElCr;
	G4Element* m_ElFe;
	G4Element* m_ElNi;
	G4Element* m_ElCu;
	G4Element* m_ElZn;
	G4Element* m_ElY;
	G4Element* m_ElSn;
	G4Element* m_ElCe;
	G4Element* m_ElLu;

	// Materials
	G4Material* m_AirMat;
	G4Material* m_TarMat;
	G4Material* m_DetMat;
	G4Material* m_CouMat;
	G4Material* m_PipMat;
	G4Material* m_VacMat;
	G4Material* m_TefMat;
	G4Material* m_TedMat;
	G4Material* m_KapMat;
	G4Material* m_GasMat;
	G4Material* m_PCBMat;
	G4Material* m_CoaMat;

	// Dimensions and detector setup
	G4double labX, labY, labZ;
	G4double pipR, pipT, pipt, pipP;
	G4double tarD, tarT;
	G4double coud, couD, couT;
	G4double staW, staH, staT, staX, staY, staZ;
	G4double detE, detL, detG;
	G4double detX, detY, detZ, detA;
	std::vector<G4bool> detS;
	G4double tefT, tedT, kapT;
	G4double copT, driT, traT, pcbT;
	G4double gemX, gemY, gemZ;
	G4double ka0Z, ka1Z, ka2Z, ka3Z, ka4Z;
	G4double co0Z, co1Z, co2Z, co3Z, co4Z, co5Z, co6Z, co7Z;
	G4double ga0Z, ga1Z, ga2Z, ga3Z, pcbZ;
	G4double gemS;

	// Geometry objects
	G4Box* labSolid;
	G4LogicalVolume* labLV;
	G4VPhysicalVolume* labPV;

	G4Tubs* target;
	G4LogicalVolume* tarLV;

	G4Box* kaptonBase;
	G4SubtractionSolid* kapton;
	G4LogicalVolume* kapLV[120];
	G4ThreeVector kapPos[120];
	G4Box* tedlarBase;
	G4SubtractionSolid* tedlar;
	G4LogicalVolume* tedLV[120];
	G4ThreeVector tedPos[120];
	G4Box* teflonBase;
	G4SubtractionSolid* teflon;
	G4LogicalVolume* tefLV[120];
	G4ThreeVector tefPos[120];
	G4String cryName[120];
	G4Box* crystal;
	G4LogicalVolume* cryLV[120];
	G4ThreeVector cryPos[120];
	G4bool isConstructed[120] = {false};

	G4Tubs* dESolid;
	G4LogicalVolume* dELV;

	G4Box* scSolid;
	G4LogicalVolume* scLV;

	G4Tubs* pipSolid;
	G4LogicalVolume* pipLV;
	G4Tubs* ewSolid;
	G4LogicalVolume* ewLV;
	G4Tubs* vacSolid;
	G4LogicalVolume* vacLV;

	G4Box* kapFil[5];
	G4Box* copCoa[8];
	G4Box* gasGap[4];
	G4Box* pcb;
	G4LogicalVolume* kapFilLV[5];
	G4LogicalVolume* copCoaLV[8];
	G4LogicalVolume* gasGapLV[4];
	G4LogicalVolume* pcbLV;

	// Rotation for crystals
	G4RotationMatrix* cryRot;
};
#endif
