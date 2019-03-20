#ifndef BT2017CONMAN_h
#define BT2017CONMAN_h 1

////////////////////////////////////////////////////////////////////////////////
//   BT2017ConMan.hh for beamtest2017 of JEDI                                 //
//                                                                            //
//   This file is a header for BT2017ConMan class. It's a configuration       //
// manager for simulation. The class contains all configuration parameters    //
// for simulation configuration from a file.                                  //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <vector>
#include "globals.hh"

class BT2017ConMan
{
  public:
	// Constructors and Destructor
	BT2017ConMan();
	BT2017ConMan(const char* fileName);
	~BT2017ConMan();

	// Initialize
	void Init(const char* fileName = 0);

	// Load configuration file
	bool Load(const char* fileName);
	void PrintConfiguration();

	// Set & get configurations: Computing
	void SetUseMTD(const G4bool   useMTD);
	const G4bool   GetUseMTD() const;
	void SetNofTRD(const G4int    nofTRD);
	const G4int    GetNofTRD() const;
	// Set & get configurations: Physics
	void SetUseJED(const G4bool   useJED);
	const G4bool   GetUseJED() const;
	// Set & get configurations: World
	void SetWorldX(const G4double worldX);
	const G4double GetWorldX() const;
	void SetWorldY(const G4double worldY);
	const G4double GetWorldY() const;
	void SetWorldZ(const G4double worldZ);
	const G4double GetWorldZ() const;
	// Set & get configurations: Beam
	void SetBeamPX(const G4double beamPX);	
	const G4double GetBeamPX() const;
	void SetBeamPY(const G4double beamPY);
	const G4double GetBeamPY() const;
	void SetBeamDX(const G4double beamDX);
	const G4double GetBeamDX() const;
	void SetBeamDY(const G4double beamDY);
	const G4double GetBeamDY() const;
	void SetBeamKE(const G4double beamKE);
	const G4double GetBeamKE() const;
	// Set & get configurations: Pipe
	void SetPipePZ(const G4double pipePZ);
	const G4double GetPipePZ() const;
	// Set & get configurations: Target
	void SetUseTar(const G4bool   useTar);
	const G4bool   GetUseTar() const;
	void SetTarMat(const G4String tarMat);
	const G4String GetTarMat() const;
	void SetTarThi(const G4double tarThi);
	const G4double GetTarThi() const;
	// Set & get configurations: Counters
	void SetUseStC(const G4bool   useStC);
	const G4bool   GetUseStC() const;
	void SetStCLeX(const G4double stCLeX);
	const G4double GetStCLeX() const;
	void SetStCLeY(const G4double stCLeY);
	const G4double GetStCLeY() const;
	void SetStCLeZ(const G4double stCLeZ);
	const G4double GetStCLeZ() const;
	void SetStCPoX(const G4double stCPoX);
	const G4double GetStCPoX() const;
	void SetStCPoY(const G4double stCPoY);
	const G4double GetStCPoY() const;
	void SetStCPoZ(const G4double stCPoZ);
	const G4double GetStCPoZ() const;
	void SetUseDES(const G4bool   useDES);
	const G4bool   GetUseDES() const;
	void SetDESThi(const G4double dESThi);
	const G4double GetDESThi() const;
	// Set & get configurations: Crystals
	void SetDetSet(const std::vector<G4bool> detSet);
	const std::vector<G4bool> GetDetSet() const;
	void SetDetPoX(const G4double detPoX);
	const G4double GetDetPoX() const;
	void SetDetPoY(const G4double detPoY);
	const G4double GetDetPoY() const;
	void SetDetPoZ(const G4double detPoZ);
	const G4double GetDetPoZ() const;
	void SetDetAng(const G4double detAng);
	const G4double GetDetAng() const;
	// Set & get configurations: GEM
	void SetUseGEM(const G4bool   useGEM);
	const G4bool   GetUseGEM() const;
	void SetGEMPoX(const G4double gEMPoX);
	const G4double GetGEMPoX() const;
	void SetGEMPoY(const G4double gEMPoY);
	const G4double GetGEMPoY() const;
	void SetGEMPoZ(const G4double gEMPoZ);
	const G4double GetGEMPoZ() const;

	// Does the line start with specific word?
	bool StartsWith(const std::string& line, const std::string& token);

  private:
	void SetDefault();

	// Computing resource
	std::string m_SUseMTD; G4bool   m_UseMTD;
	std::string m_SNofTRD; G4int    m_NofTRD;
	// Physics
	std::string m_SUseJED; G4bool   m_UseJED;
	// World
	std::string m_SWorldX; G4double m_WorldX;
	std::string m_SWorldY; G4double m_WorldY;
	std::string m_SWorldZ; G4double m_WorldZ;
	// Beam
	std::string m_SBeamPX; G4double m_BeamPX;
	std::string m_SBeamPY; G4double m_BeamPY;
	std::string m_SBeamDX; G4double m_BeamDX;
	std::string m_SBeamDY; G4double m_BeamDY;
	std::string m_SBeamKE; G4double m_BeamKE;
	// Pipe
	std::string m_SPipePZ; G4double m_PipePZ;
	// Target
	std::string m_SUseTar; G4bool   m_UseTar;
	std::string m_STarMat; G4String m_TarMat;
	std::string m_STarThi; G4double m_TarThi;
	// Counters
	std::string m_SUseStC; G4bool   m_UseStC;
	std::string m_SStCLeX; G4double m_StCLeX;
	std::string m_SStCLeY; G4double m_StCLeY;
	std::string m_SStCLeZ; G4double m_StCLeZ;
	std::string m_SStCPoX; G4double m_StCPoX;
	std::string m_SStCPoY; G4double m_StCPoY;
	std::string m_SStCPoZ; G4double m_StCPoZ;
	std::string m_SUseDES; G4bool   m_UseDES;
	std::string m_SDESThi; G4double m_DESThi;
	// Crystals
	std::string m_SDetSet; std::vector<G4bool> m_DetSet;
	std::string m_SDetPoX; G4double m_DetPoX;
	std::string m_SDetPoY; G4double m_DetPoY;
	std::string m_SDetPoZ; G4double m_DetPoZ;
	std::string m_SDetAng; G4double m_DetAng;
	// GEM
	std::string m_SUseGEM; G4bool   m_UseGEM;
	std::string m_SGEMPoX; G4double m_GEMPoX;
	std::string m_SGEMPoY; G4double m_GEMPoY;
	std::string m_SGEMPoZ; G4double m_GEMPoZ;
};

#endif
