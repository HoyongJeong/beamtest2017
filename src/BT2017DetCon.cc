////////////////////////////////////////////////////////////////////////////////
//   BT2017DetCon.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of BT2017DetCon class's member functions.                    //
// And it describes geometry of simulation.                                   //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4UIcommand.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "BT2017DetCon.hh"


//////////////////////////////////////////////////
//   Constructor and destructor                 //
//////////////////////////////////////////////////
BT2017DetCon::BT2017DetCon(BT2017ConMan* CM)
	: m_CM(CM)
{
	ConstructMaterials();
	DefineDimensions();
}


BT2017DetCon::~BT2017DetCon()
{
	DestructMaterials();
}


//////////////////////////////////////////////////
//   Define dimensions                          //
//////////////////////////////////////////////////
void BT2017DetCon::DefineDimensions()
{

	// World dimensions
	// // Laboratory size
	labX = m_CM -> GetWorldX(); // World x dimension
	labY = m_CM -> GetWorldY(); // World y dimension
	labZ = m_CM -> GetWorldZ(); // World z dimension

	// Beam pipe dimensions
	pipR =  50.0 * mm; // Radius (inner)
	pipT =   2.0 * mm; // Pipe thickness
	pipt =   0.1 * mm; // Exit window thickness
	pipP = m_CM -> GetPipePZ(); // Position from the target (outside edge of window <-> tatget center)

	// Target dimensions
	tarD =  50.0 * mm; // Target diameter
	tarT = m_CM -> GetTarThi(); // Thickness

	// Plastic dimensions (It will measure dE)
	coud =  80.0 * mm; // Inner diameter
	couD = 420.0 * mm; // Outer diameter
	couT = m_CM -> GetDESThi(); // Thickness

	// Start counter dimensions
	staW = m_CM -> GetStCLeX(); // Width
	staH = m_CM -> GetStCLeY(); // Height
	staT = m_CM -> GetStCLeZ(); // Thickness
	staX = m_CM -> GetStCPoX();
	staY = m_CM -> GetStCPoY();
	staZ = m_CM -> GetStCPoZ(); // Distance from the target

	// Crystral dimensions
	detE =  30.0 * mm; // Edge of square
	detL =  80.0 * mm; // Length of crystal
	detG =   0.3 * mm; // Gap between modules
	detX = m_CM -> GetDetPoX();
	detY = m_CM -> GetDetPoY();
	detZ = m_CM -> GetDetPoZ(); // Position
	detA = m_CM -> GetDetAng(); // Rotation
	detS = m_CM -> GetDetSet(); // Setup
	tefT =  50.0 * um; // Teflon thickness
	tedT =  50.0 * um; // Tedlar thickness
	kapT =  25.0 * um; // Kapton thickness

	// GEM dimensions
	copT =   5.0 * um; // Copper coating thickness
	driT =   3.0 * mm; // Drift gap
	traT =   2.0 * mm; // Transfer gap
	pcbT =   2.0 * mm; // PCB thickness
	gemX = m_CM -> GetGEMPoX();
	gemY = m_CM -> GetGEMPoY();
	gemZ = m_CM -> GetGEMPoZ();
	ka0Z = gemZ + 0.5*kapT;            // Cathode
	co0Z = ka0Z + 0.5*kapT + 0.5*copT; // Cathode
	ga0Z = co0Z + 0.5*copT + 0.5*driT; // Drift gap
	co1Z = ga0Z + 0.5*driT + 0.5*copT; // foil 1
	ka1Z = co1Z + 0.5*copT + 0.5*kapT; // foil 1
	co2Z = ka1Z + 0.5*kapT + 0.5*copT; // foil 1
	ga1Z = co2Z + 0.5*copT + 0.5*traT; // Transfer gap 1
	co3Z = ga1Z + 0.5*traT + 0.5*copT; // foil 2
	ka2Z = co3Z + 0.5*copT + 0.5*kapT; // foil 2
	co4Z = ka2Z + 0.5*kapT + 0.5*copT; // foil 2
	ga2Z = co4Z + 0.5*copT + 0.5*traT; // Transfer gap 2
	co5Z = ga2Z + 0.5*traT + 0.5*copT; // foil 3
	ka3Z = co5Z + 0.5*copT + 0.5*kapT; // foil 3
	co6Z = ka3Z + 0.5*kapT + 0.5*copT; // foil 3
	ga3Z = co6Z + 0.5*copT + 0.5*traT; // collection gap
	co7Z = ga3Z + 0.5*traT + 0.5*copT; // Anode
	ka4Z = co7Z + 0.5*copT + 0.5*kapT; // Anode
	pcbZ = ka4Z + 0.5*kapT + 0.5*pcbT; // Anode

	gemS = 100.0 * mm; // Size of GEM
}


//////////////////////////////////////////////////
//   Construct everything                       //
//////////////////////////////////////////////////
G4VPhysicalVolume* BT2017DetCon::Construct()
{
	// World
	labSolid = new G4Box("labSolid", labX/2, labY/2, labZ/2);
	labLV = new G4LogicalVolume(labSolid, m_AirMat, "labLV");
	labPV = new G4PVPlacement(0, G4ThreeVector(), "labPV", labLV, 0, false, 0);

	// Cylindrical target
	target = new G4Tubs("target", 0., tarD/2, tarT/2, 0.*degree, 360.*degree);
	tarLV = new G4LogicalVolume(target, m_TarMat, "tarLV");
	if ( m_CM -> GetUseTar() )
		new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), "tarPV", tarLV, labPV, false, 0);

	// Crystal detectors start here
	kaptonBase = new G4Box("kaptonBase", detE/2+tefT+tedT+kapT, detE/2+tefT+tedT+kapT, detL/2+tefT+tedT+kapT);
	tedlarBase = new G4Box("tedlarBase", detE/2+tefT+tedT,      detE/2+tefT+tedT,      detL/2+tefT+tedT);
	teflonBase = new G4Box("teflonBase", detE/2+tefT,           detE/2+tefT,           detL/2+tefT);
	crystal   = new G4Box("crystal", detE/2,              detE/2,                detL/2);
	teflon = new G4SubtractionSolid("teflon", teflonBase, crystal,    0, G4ThreeVector(0., 0., tefT));
	tedlar = new G4SubtractionSolid("tedlar", tedlarBase, teflonBase, 0, G4ThreeVector(0., 0., tedT));
	kapton = new G4SubtractionSolid("kapton", kaptonBase, tedlarBase, 0, G4ThreeVector(0., 0., kapT));
	cryRot = new G4RotationMatrix();
	cryRot -> rotateZ(-detA);
	// Left crystals
	for ( int i = 0; i < 3; i++ ) // L1 crystals
		                   ConstructCrystal("L", 69-10*i, 1, i+1, 3);
	for ( int i = 0; i < 5; i++ ) // L2 crystals
	{
		if      ( i < 4 )  ConstructCrystal("L", 78-10*i, 2, i+1, 5);
		else               ConstructCrystal("L",      35, 2, i+1, 5);
	}
	for ( int i = 0; i < 7; i++ ) // L3 crystals
	{
		if      ( i < 1 )  ConstructCrystal("L",      89, 3, i+1, 7);
		else if ( i < 5 )  ConstructCrystal("L", 87-10*i, 3, i+1, 7);
		else if ( i == 5 ) ConstructCrystal("L",      34, 3, i+1, 7);
		else               ConstructCrystal("L",      22, 3, i+1, 7);
	}
	for ( int i = 0; i < 7; i++ ) // L4 crystals
	{
		if      ( i < 1 )  ConstructCrystal("L",      88, 4, i+1, 7);
		else if ( i < 5 )  ConstructCrystal("L", 86-10*i, 4, i+1, 7);
		else if ( i == 5 ) ConstructCrystal("L",      33, 4, i+1, 7);
		else               ConstructCrystal("L",      21, 4, i+1, 7);
	}
	for ( int i = 0; i < 5; i++ ) // L5 crystals
	{
		if      ( i < 4 )  ConstructCrystal("L", 75-10*i, 5, i+1, 5);
		else               ConstructCrystal("L",      32, 5, i+1, 5);
	}
	// Right crystals
	for ( int i = 0; i < 3; i++ ) // R1 crystals
		                   ConstructCrystal("R", 50+10*i, 1, i+1, 3);
	for ( int i = 0; i < 5; i++ ) // R2 crystals
	{
		if      ( i < 4 )  ConstructCrystal("R", 41+10*i, 2, i+1, 5);
		else               ConstructCrystal("R",      84, 2, i+1, 5);
	}
	for ( int i = 0; i < 7; i++ ) // R3 crystals
	{
		if      ( i < 1 )  ConstructCrystal("R",      30, 3, i+1, 7);
		else if ( i < 5 )  ConstructCrystal("R", 32+10*i, 3, i+1, 7);
		else if ( i == 5 ) ConstructCrystal("R",      85, 3, i+1, 7);
		else               ConstructCrystal("R",      97, 3, i+1, 7);
	}
	for ( int i = 0; i < 7; i++ ) // R4 crystals
	{
		if      ( i < 1 )  ConstructCrystal("R",      31, 4, i+1, 7);
		else if ( i < 5 )  ConstructCrystal("R", 33+10*i, 4, i+1, 7);
		else if ( i == 5 ) ConstructCrystal("R",      86, 4, i+1, 7);
		else               ConstructCrystal("R",      98, 4, i+1, 7);
	}
	for ( int i = 0; i < 5; i++ ) // R5 crystals
	{
		if      ( i < 4 )  ConstructCrystal("R", 44+10*i, 5, i+1, 5);
		else               ConstructCrystal("R",      87, 5, i+1, 5);
	}
	// Up crystals
	for ( int i = 0; i < 3; i++ ) // U1 crystals
		                   ConstructCrystal("U",    37+i, 1, i+1, 3);
	for ( int i = 0; i < 5; i++ ) // U2 crystals
		                   ConstructCrystal("U",    24+i, 2, i+1, 5);
	for ( int i = 0; i < 7; i++ ) // U3 crystals
		                   ConstructCrystal("U",    13+i, 3, i+1, 7);
	for ( int i = 0; i < 7; i++ ) // U4 crystals
		                   ConstructCrystal("U",     5+i, 4, i+1, 7);
	for ( int i = 0; i < 5; i++ ) // U5 crystals
		                   ConstructCrystal("U",       i, 5, i+1, 5);
	// Down crystals
	for ( int i = 0; i < 3; i++ ) // D1 crystals
		                   ConstructCrystal("D",    82-i, 1, i+1, 3);
	for ( int i = 0; i < 5; i++ ) // D2 crystals
		                   ConstructCrystal("D",    95-i, 2, i+1, 5);
	for ( int i = 0; i < 7; i++ ) // D3 crystals
		                   ConstructCrystal("D",   106-i, 3, i+1, 7);
	for ( int i = 0; i < 7; i++ ) // D4 crystals
		                   ConstructCrystal("D",   114-i, 4, i+1, 7);
	for ( int i = 0; i < 5; i++ ) // D5 crystals
		                   ConstructCrystal("D",   119-i, 5, i+1, 5);
	// Cross crystals
	ConstructCrystal("C",  36, 1, 1, 4); // C1 crystals from here
	ConstructCrystal("C",  40, 1, 2, 4);
	ConstructCrystal("C",  83, 1, 3, 4);
	ConstructCrystal("C",  79, 1, 4, 4);
	ConstructCrystal("C",  23, 2, 1, 4); // C2 crystals from here
	ConstructCrystal("C",  29, 2, 2, 4);
	ConstructCrystal("C",  96, 2, 3, 4);
	ConstructCrystal("C",  90, 2, 4, 4);
	ConstructCrystal("C",  12, 3, 1, 4); // C3 crystals from here
	ConstructCrystal("C",  20, 3, 2, 4);
	ConstructCrystal("C", 107, 3, 3, 4);
	ConstructCrystal("C",  99, 3, 4, 4);
	// Place them
	for ( int i = 0; i < 120; i++ )
		if ( detS[i] && isConstructed[i] )
		{
			new G4PVPlacement(cryRot, cryPos[i], cryName[i]+"_cryPV", cryLV[i], labPV, false, 0);
			new G4PVPlacement(cryRot, tefPos[i], cryName[i]+"_tefPV", tefLV[i], labPV, false, 0);
			new G4PVPlacement(cryRot, tedPos[i], cryName[i]+"_tedPV", tedLV[i], labPV, false, 0);
			new G4PVPlacement(cryRot, kapPos[i], cryName[i]+"_kapPV", kapLV[i], labPV, false, 0);
		}

	// Plastic scintillators
	dESolid = new G4Tubs("deSolud", coud/2, couD/2, couT/2, 0.*degree, 360.*degree);
	dELV = new G4LogicalVolume(dESolid, m_CouMat, "dELV");
	dELV -> SetVisAttributes(new G4VisAttributes(G4Colour::Gray()));
	if ( m_CM -> GetUseDES() )
		new G4PVPlacement(0, G4ThreeVector(detX, detY, detZ - couT/2 - 1.*mm), "dEPV", dELV, labPV, false, 0);

	// Start counter
	scSolid = new G4Box("scSolid", staW/2, staH/2, staT/2);
	scLV = new G4LogicalVolume(scSolid, m_CouMat, "scLV");
	scLV -> SetVisAttributes(new G4VisAttributes(G4Colour::Gray()));
	if ( m_CM -> GetUseStC() )
		new G4PVPlacement(0, G4ThreeVector(staX, staY, - staZ), "scPV", scLV, labPV, false, 0);

	// Beam pipe
	pipSolid = new G4Tubs("pipSolid", pipR, pipR + pipT, (labZ/2 - pipP - pipT)/2, 0.*deg, 360.0*deg); // Pipe
	pipLV = new G4LogicalVolume(pipSolid, m_PipMat, "bpLV");
	new G4PVPlacement(0, G4ThreeVector(0., 0., - (labZ/2 + pipP + pipT)/2), "pipPV", pipLV, labPV, false, 0);
	ewSolid = new G4Tubs("ewSolid", 0., pipR + pipT, pipt/2, 0.*deg, 360.*deg); // Exit window
	ewLV = new G4LogicalVolume(ewSolid, m_PipMat, "ewLV");
	new G4PVPlacement(0, G4ThreeVector(0., 0., - pipP - pipt/2), "ewPV", ewLV, labPV, false, 0);
	vacSolid = new G4Tubs("VacSolid", 0., pipR, (labZ/2 - pipP - pipT)/2, 0.*deg, 360.*deg); // Vacuum
	vacLV = new G4LogicalVolume(vacSolid, m_VacMat, "vacLV");
	vacLV -> SetVisAttributes(new G4VisAttributes(0));
	new G4PVPlacement(0, G4ThreeVector(0., 0., - (labZ/2 + pipP + pipT)/2), "vacPV", vacLV, labPV, false, 0);

	// GEM
	kapFil[0] = new G4Box("kapFil0", gemS/2, gemS/2, kapT/2); // Geomtry: Cathode
	copCoa[0] = new G4Box("copCoa0", gemS/2, gemS/2, copT/2); // Geomtry: Cathode
	gasGap[0] = new G4Box("gasGap0", gemS/2, gemS/2, driT/2); // Geomtry: Drift gap
	copCoa[1] = new G4Box("copCoa1", gemS/2, gemS/2, copT/2); // Geomtry: Foil 1
	kapFil[1] = new G4Box("kapFil1", gemS/2, gemS/2, kapT/2); // Geomtry: Foil 1
	copCoa[2] = new G4Box("copCoa2", gemS/2, gemS/2, copT/2); // Geomtry: Foil 1
	gasGap[1] = new G4Box("gasGap1", gemS/2, gemS/2, traT/2); // Geomtry: Transfer gap 1
	copCoa[3] = new G4Box("copCoa3", gemS/2, gemS/2, copT/2); // Geomtry: Foil 2
	kapFil[2] = new G4Box("kapFil2", gemS/2, gemS/2, kapT/2); // Geomtry: Foil 2
	copCoa[4] = new G4Box("copCoa4", gemS/2, gemS/2, copT/2); // Geomtry: Foil 2
	gasGap[2] = new G4Box("gasGap2", gemS/2, gemS/2, traT/2); // Geomtry: Transfer gap 2
	copCoa[5] = new G4Box("copCoa5", gemS/2, gemS/2, copT/2); // Geomtry: Foil 3
	kapFil[3] = new G4Box("kapFil3", gemS/2, gemS/2, kapT/2); // Geomtry: Foil 3
	copCoa[6] = new G4Box("copCoa6", gemS/2, gemS/2, copT/2); // Geomtry: Foil 3
	gasGap[3] = new G4Box("gasGap2", gemS/2, gemS/2, traT/2); // Geomtry: Collection gap
	copCoa[7] = new G4Box("copCoa7", gemS/2, gemS/2, copT/2); // Geomtry: Anode
	kapFil[4] = new G4Box("kapFil4", gemS/2, gemS/2, kapT/2); // Geomtry: Anode
	pcb       = new G4Box("pcb"    , gemS/2, gemS/2, pcbT/2); // Geomtry: Anode
	kapFilLV[0] = new G4LogicalVolume(kapFil[0], m_KapMat, "kapFil0LV"); // LV: Cathode
	copCoaLV[0] = new G4LogicalVolume(copCoa[0], m_CoaMat, "copCoa0LV"); // LV: Cathode
	gasGapLV[0] = new G4LogicalVolume(gasGap[0], m_GasMat, "gasGap0LV"); // LV: Cathode
	copCoaLV[1] = new G4LogicalVolume(copCoa[1], m_CoaMat, "copCoa1LV"); // LV: Foil 1
	kapFilLV[1] = new G4LogicalVolume(kapFil[1], m_KapMat, "kapFil1LV"); // LV: Foil 1
	copCoaLV[2] = new G4LogicalVolume(copCoa[2], m_CoaMat, "copCoa2LV"); // LV: Foil 1
	gasGapLV[1] = new G4LogicalVolume(gasGap[1], m_GasMat, "gasGap1LV"); // LV: Transfer gap 1
	copCoaLV[3] = new G4LogicalVolume(copCoa[3], m_CoaMat, "copCoa3LV"); // LV: Foil 2
	kapFilLV[2] = new G4LogicalVolume(kapFil[2], m_KapMat, "kapFil2LV"); // LV: Foil 2
	copCoaLV[4] = new G4LogicalVolume(copCoa[4], m_CoaMat, "copCoa4LV"); // LV: Foil 2
	gasGapLV[2] = new G4LogicalVolume(gasGap[2], m_GasMat, "gasGap2LV"); // LV: Transfer gap 2
	copCoaLV[5] = new G4LogicalVolume(copCoa[5], m_CoaMat, "copCoa5LV"); // LV: Foil 3
	kapFilLV[3] = new G4LogicalVolume(kapFil[3], m_KapMat, "kapFil3LV"); // LV: Foil 3
	copCoaLV[6] = new G4LogicalVolume(copCoa[6], m_CoaMat, "copCoa6LV"); // LV: Foil 3
	gasGapLV[3] = new G4LogicalVolume(gasGap[3], m_GasMat, "gasGap3LV"); // LV: Collection gap
	copCoaLV[7] = new G4LogicalVolume(copCoa[7], m_CoaMat, "copCoa7LV"); // LV: Anode
	kapFilLV[4] = new G4LogicalVolume(kapFil[4], m_KapMat, "kapFil4LV"); // LV: Anode
	pcbLV       = new G4LogicalVolume(pcb      , m_PCBMat, "pcbLV"    ); // LV: Anode
	for ( int i = 0; i < 5; i++ ) kapFilLV[i] -> SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));
	for ( int i = 0; i < 8; i++ ) copCoaLV[i] -> SetVisAttributes(new G4VisAttributes(G4Colour(0.58, 0.29, 0.0)));
	for ( int i = 0; i < 4; i++ ) gasGapLV[i] -> SetVisAttributes(new G4VisAttributes(0)); // Invisible
	pcbLV -> SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ka0Z), "kapFil0PV", kapFilLV[0], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, co0Z), "copCoa0PV", copCoaLV[0], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ga0Z), "gasGap0PV", gasGapLV[0], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, co1Z), "copCoa1PV", copCoaLV[1], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ka1Z), "kapFil1PV", kapFilLV[1], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, co2Z), "copCoa2PV", copCoaLV[2], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ga1Z), "gasGap1PV", gasGapLV[1], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, co3Z), "copCoa3PV", copCoaLV[3], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ka2Z), "kapFil2PV", kapFilLV[2], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, co4Z), "copCoa4PV", copCoaLV[4], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ga2Z), "gasGap2PV", gasGapLV[2], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, co5Z), "copCoa5PV", copCoaLV[5], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ka3Z), "kapFil3PV", kapFilLV[3], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, co6Z), "copCoa6PV", copCoaLV[6], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ga3Z), "gasGap3PV", gasGapLV[3], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, co7Z), "copCoa7PV", copCoaLV[7], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, ka4Z), "kapFil4PV", kapFilLV[4], labPV, false, 0);
	new G4PVPlacement(0, G4ThreeVector(gemX, gemY, pcbZ), "pcbLV"    , pcbLV      , labPV, false, 0);

	return labPV;
}

void BT2017DetCon::ConstructMaterials()
{
	const G4double labTemp = 300.0 * kelvin;

	// Elements to be used to construct materials
	m_ElH  = new G4Element( "Hydrogen",  "H",  1,   1.00794*g/mole);
	m_ElC  = new G4Element(   "Carbon",  "C",  6,  12.011  *g/mole);
	m_ElN  = new G4Element( "Nitrogen",  "N",  7,  14.00674*g/mole);
	m_ElO  = new G4Element(   "Oxygen",  "O",  8,  15.9994 *g/mole);
	m_ElF  = new G4Element( "Fluorine",  "F",  9,  18.9984 *g/mole);
	m_ElMg = new G4Element("Magnesium", "Mg", 12,  24.3050 *g/mole);
	m_ElAl = new G4Element( "Aluminum", "Al", 13,  26.98154*g/mole);
	m_ElSi = new G4Element(  "Silicon", "Si", 14,  28.0855 *g/mole);
	m_ElAr = new G4Element(    "Argon", "Ar", 18,  39.948  *g/mole);
	m_ElCr = new G4Element("Chromuium", "Cr", 24,  51.9961 *g/mole);
	m_ElFe = new G4Element(     "Iron", "Fe", 26,  55.845  *g/mole);
	m_ElNi = new G4Element(   "Nickel", "Ni", 28,  58.9634 *g/mole);
	m_ElCu = new G4Element(   "Copper", "Cu", 29,  63.546  *g/mole);
	m_ElZn = new G4Element(     "Zinc", "Zn", 30,  65.38   *g/mole);
	m_ElY  = new G4Element(  "Yttrium",  "Y", 39,  88.90585*g/mole);
	m_ElSn = new G4Element(      "Tin", "Sn", 50, 118.71   *g/mole);
	m_ElCe = new G4Element(   "Cerium", "Ce", 58, 140.116  *g/mole);
	m_ElLu = new G4Element( "Lutetium", "Lu", 71, 176.944  *g/mole);

	// Air material
	m_AirMat = new G4Material("Air", 1.1839e-3*g/cm3, 3, kStateGas, labTemp); // Density at 1 atm
	m_AirMat -> AddElement(m_ElN, 75.47/99.95);
	m_AirMat -> AddElement(m_ElO, 23.20/99.95);
	m_AirMat -> AddElement(m_ElAr, 1.28/99.95);

	// Target material
	G4String targetMaterial = m_CM -> GetTarMat();
	if ( targetMaterial == "C" )
	{
		m_TarMat = new G4Material("Graphite", 1.7*g/cm3, 3, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElC, 99.0/100.0);
		m_TarMat -> AddElement(m_ElN,  0.7/100.0);
		m_TarMat -> AddElement(m_ElO,  0.3/100.0);
	}
	else if ( targetMaterial == "Mg" )
	{
		m_TarMat = new G4Material("Magnesium", 1.738*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElMg, 1.0);
	}
	else if ( targetMaterial == "Al" )
	{
		m_TarMat = new G4Material("Aluminum", 2.70*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElAl, 1.0);
	}
	else if ( targetMaterial == "Sn" )
	{
		m_TarMat = new G4Material("Tin", 5.769*g/cm3, 1, kStateSolid, labTemp); // Gray tin?
		m_TarMat -> AddElement(m_ElSn, 1.0);
	}
	else if ( targetMaterial == "Si" )
	{
		m_TarMat = new G4Material("Silicon", 2.329*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElSi, 1.0);
	}
	else if ( targetMaterial == "Ni" )
	{
		m_TarMat = new G4Material("Nickel", 8.908*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElNi, 1.0);
	}
	else if ( targetMaterial == "Zn" )
	{
		m_TarMat = new G4Material("Zinc", 7.14*g/cm3, 1, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElZn, 1.0);
	}
	else if ( targetMaterial == "CH2" )
	{
		m_TarMat = new G4Material("Polyethelene", 0.92*g/cm3, 2, kStateSolid, labTemp);
		m_TarMat -> AddElement(m_ElC, 1);
		m_TarMat -> AddElement(m_ElH, 2);
	}
	else
	{
		std::stringstream message;
		message << "Could not find target material with name " << targetMaterial;
		G4Exception("BT2017DetCon::ConstructMaterials()", "", FatalException, message.str().c_str());
	}

	// Crystal scintillator material
	m_DetMat = new G4Material("LYSO", 7.1*g/cm3, 5, kStateSolid, labTemp);
	m_DetMat -> AddElement(m_ElLu, 71.43/100.0);
	m_DetMat -> AddElement(m_ElY,   4.03/100.0);
	m_DetMat -> AddElement(m_ElSi,  6.37/100.0);
	m_DetMat -> AddElement(m_ElO,  18.14/100.0);
	m_DetMat -> AddElement(m_ElCe,  0.02/100.0);

	// Plastic scintillator material
	m_CouMat = new G4Material("PlasticScint", 1.032*g/cm3, 2, kStateSolid, labTemp);
	m_CouMat -> AddElement(m_ElC, 10);
	m_CouMat -> AddElement(m_ElH, 11);

	// Pipe material
	m_PipMat = new G4Material("StainlessSteel", 8.03*g/cm3, 3, kStateSolid, labTemp);
	m_PipMat -> AddElement(m_ElFe, 70.0/100.0);
	m_PipMat -> AddElement(m_ElCr, 20.0/100.0);
	m_PipMat -> AddElement(m_ElNi, 10.0/100.0);

	// Vacuum material
	m_VacMat = new G4Material("Vacumm", 1.1839e-10*g/cm3, 3, kStateGas, labTemp);
	m_VacMat -> AddElement(m_ElN, 75.47/99.95);
	m_VacMat -> AddElement(m_ElO, 23.20/99.95);
	m_VacMat -> AddElement(m_ElAr, 1.28/99.95);

	// Teflon material
	m_TefMat = new G4Material("Teflon", 2.2*g/cm3, 2, kStateSolid, labTemp);
	m_TefMat -> AddElement(m_ElC, 1);
	m_TefMat -> AddElement(m_ElF, 2);

	// Tedlar material
	m_TedMat = new G4Material("Tedlar", 1.545*g/cm3, 3, kStateSolid, labTemp);
	m_TedMat -> AddElement(m_ElC, 2);
	m_TedMat -> AddElement(m_ElH, 3);
	m_TedMat -> AddElement(m_ElF, 1);

	// Kapton mateiral
	m_KapMat = new G4Material("Kapton", 1.39*g/cm3, 3, kStateSolid, labTemp);
	m_KapMat -> AddElement(m_ElC, 5);
	m_KapMat -> AddElement(m_ElO, 2);
	m_KapMat -> AddElement(m_ElH, 4);

	// Ar+CO2 gas material
	m_GasMat = new G4Material("Gas", 1.184*kg/m3, 3, kStateGas, labTemp);
	m_GasMat -> AddElement(m_ElAr, 12);
	m_GasMat -> AddElement(m_ElC,   1);
	m_GasMat -> AddElement(m_ElO,   2);

	// PCB material
	m_PCBMat = new G4Material("PCB", 2.0*g/cm3, 2, kStateSolid, labTemp);
	m_PCBMat -> AddElement(m_ElSi, 1);
	m_PCBMat -> AddElement(m_ElO,  2);

	// Copper coating material
	m_CoaMat = new G4Material("Coating", 8.96*g/cm3, 1, kStateSolid, labTemp);
	m_CoaMat -> AddElement(m_ElCu, 1);
}

void BT2017DetCon::DestructMaterials()
{
	delete m_CoaMat;
	delete m_PCBMat;
	delete m_GasMat;
	delete m_KapMat;
	delete m_TedMat;
	delete m_TefMat;
	delete m_VacMat;
	delete m_PipMat;
	delete m_CouMat;
	delete m_TarMat;
	delete m_AirMat;

	delete m_ElLu;
	delete m_ElCe;
	delete m_ElSn;
	delete m_ElY;
	delete m_ElZn;
	delete m_ElCu;
	delete m_ElNi;
	delete m_ElFe;
	delete m_ElCr;
	delete m_ElAr;
	delete m_ElSi;
	delete m_ElAl;
	delete m_ElMg;
	delete m_ElF;
	delete m_ElO;
	delete m_ElN;
	delete m_ElC;
	delete m_ElH;
}

//////////////////////////////////////////////////
//   Construct a crystal                        //
//   This function is used to repeat            //
// construction of crystals in                  //
// BT2017DetCon::Contruct function.             //
//////////////////////////////////////////////////
void BT2017DetCon::ConstructCrystal(G4String direction,
	G4int detID, G4int thetaID, G4int phiID, G4int maxPhi)
{
	// Construct name of this module
	cryName[detID]  = direction + G4UIcommand::ConvertToString(thetaID);
	cryName[detID] += "_" + G4UIcommand::ConvertToString(phiID);
	cryName[detID] += "_" + G4UIcommand::ConvertToString(maxPhi);

	// Define logical volume
	kapLV[detID] = new G4LogicalVolume(kapton,  m_KapMat, "kapLV");
	tedLV[detID] = new G4LogicalVolume(tedlar,  m_TedMat, "tedLV");
	tefLV[detID] = new G4LogicalVolume(teflon,  m_TefMat, "tefLV");
	cryLV[detID] = new G4LogicalVolume(crystal, m_DetMat, cryName[detID]);

	// Where is it?
	if      ( direction == "L" )
		cryPos[detID] = G4ThreeVector(30.3*(thetaID+1)*mm, 30.3*(phiID-maxPhi/2-1)*mm, detZ + detL/2);
	else if ( direction == "R" )
		cryPos[detID] = G4ThreeVector(- 30.3*(thetaID+1)*mm, 30.3*(phiID-maxPhi/2-1)*mm, detZ + detL/2);
	else if ( direction == "U" )
		cryPos[detID] = G4ThreeVector(30.3*(phiID-maxPhi/2-1)*mm, 30.3*(thetaID+1)*mm, detZ + detL/2);
	else if ( direction == "D" )
		cryPos[detID] = G4ThreeVector(30.3*(phiID-maxPhi/2-1)*mm, - 30.3*(thetaID+1)*mm, detZ + detL/2);
	else if ( direction == "C" )
		cryPos[detID] = G4ThreeVector(std::sqrt(2.0)*std::cos((90.0*phiID-45.0)*deg)*30.3*(thetaID+1)*mm,
		                              std::sqrt(2.0)*std::sin((90.0*phiID-45.0)*deg)*30.3*(thetaID+1)*mm,
		                              detZ + detL/2);
	// Apply translation
	cryPos[detID] = cryPos[detID] + G4ThreeVector(m_CM -> GetDetPoX(), m_CM -> GetDetPoY(), 0.);

	// Rotate it
	cryPos[detID].rotateZ(detA);

	// Wrap this crystal
	tefPos[detID] = cryPos[detID] - G4ThreeVector(0., 0., tefT);
	tedPos[detID] = cryPos[detID] - G4ThreeVector(0., 0., tefT+tedT);
	kapPos[detID] = cryPos[detID] - G4ThreeVector(0., 0., tefT+tedT+kapT);

	// Beautiful colours
	if ( direction == "L" )
		cryLV[detID] -> SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
	if ( direction == "R" )
		cryLV[detID] -> SetVisAttributes(new G4VisAttributes(G4Colour::Cyan()));
	if ( direction == "U" )
		cryLV[detID] -> SetVisAttributes(new G4VisAttributes(G4Colour::Magenta()));
	if ( direction == "D" )
		cryLV[detID] -> SetVisAttributes(new G4VisAttributes(G4Colour::Magenta()));
	if ( direction == "C" )
		cryLV[detID] -> SetVisAttributes(new G4VisAttributes(G4Colour::Green()));
	tefLV[detID] -> SetVisAttributes(new G4VisAttributes(G4Colour::White()));
	tedLV[detID] -> SetVisAttributes(new G4VisAttributes(G4Colour::Gray()));
	kapLV[detID] -> SetVisAttributes(new G4VisAttributes(G4Colour::Yellow()));

	// Done!
	isConstructed[detID] = true;
}
