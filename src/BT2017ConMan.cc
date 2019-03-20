////////////////////////////////////////////////////////////////////////////////
//   BT2017ConMan.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of BT2017ConMan class's member functions                     //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "BT2017ConMan.hh"
#include "G4SystemOfUnits.hh"

//////////////////////////////////////////////////
//   Constructors and destructor                //
//////////////////////////////////////////////////
BT2017ConMan::BT2017ConMan()
{
	Init();
}


BT2017ConMan::BT2017ConMan(const char* fileName)
{
	Init(fileName);
}


BT2017ConMan::~BT2017ConMan()
{
}


//////////////////////////////////////////////////
//   Initialization function                    //
//////////////////////////////////////////////////
void BT2017ConMan::Init(const char* fileName)
{
	if ( !fileName ) SetDefault();
	else if ( !Load(fileName) ) SetDefault();
//	SetDefault();
}

void BT2017ConMan::SetDefault()
{
	// When the class fails to find configuration file, this setup is applied.

	// Computing
	m_UseMTD =        true;
	m_NofTRD =           4;
	// Physics
	m_UseJED =        true;
	// World
	m_WorldX = 2400.0 * mm;
	m_WorldY = 2400.0 * mm;
	m_WorldZ = 2400.0 * mm;
	// Beam
	m_BeamPX =    0.0 * mm;
	m_BeamPY =    0.0 * mm;
	m_BeamDX =   10.0 * mm;
	m_BeamDY =   10.0 * mm;
	m_BeamKE =  270.0 * MeV;
	// Pipe
	m_PipePZ =  200.0 * mm;
	// Target
	m_TarMat =         "C";
	m_TarThi =    5.0 * mm;
	// Counters
	m_UseStC =        true;
	m_StCLeX =   20.0 * mm;
	m_StCLeY =   15.0 * mm;
	m_StCLeZ =    2.0 * mm;
	m_StCPoX =    0.0 * mm;
	m_StCPoY =    0.0 * mm;
	m_StCPoZ =   20.0 * mm;
	m_UseDES =        true;
	m_DESThi =   20.0 * mm;
	// Crystals
	m_DetSet.assign(120, false);
	m_DetPoX =    0.0 * mm;
	m_DetPoY =    0.0 * mm;
	m_DetPoZ =  690.0 * mm;
	m_DetAng =    0.0 * deg;
	// GEM
	m_UseGEM = true;
	m_GEMPoX =    0.0 * mm;
	m_GEMPoY =    0.0 * mm;
	m_GEMPoZ = 2400.0 * mm;
}


//////////////////////////////////////////////////
//   Load configuration file                    //
//////////////////////////////////////////////////
bool BT2017ConMan::Load(const char* fileName)
{
	// Open file
	std::ifstream file(fileName, std::ifstream::in);
	if ( !file.is_open() ) return false;

	// Read line by line
	std::string line;
	m_DetSet.assign(120, false);
	while ( std::getline(file, line) )
	{
		if ( StartsWith(line, "#") ) continue;

		// Read configurations: Computing
		if ( StartsWith(line, "USEMULTITHREADS") )
		{
			char hfile[1000];
			sscanf(line.data(), "USEMULTITHREADS %s", hfile);
			m_SUseMTD = hfile;
			if      ( m_SUseMTD == "ON"  ) m_UseMTD = true;
			else if ( m_SUseMTD == "OFF" ) m_UseMTD = false;
		}
		if ( StartsWith(line, "NTHREADS") )
		{
			char hfile[1000];
			sscanf(line.data(), "NTHREADS %s", hfile);
			m_SNofTRD = hfile;
			m_NofTRD = std::stoi(m_SNofTRD);
		}
		// Read configurations: Physics
		if ( StartsWith(line, "USEJEDIPHYSICS") )
		{
			char hfile[1000];
			sscanf(line.data(), "USEJEDIPHYSICS %s", hfile);
			m_SUseJED = hfile;
			if      ( m_SUseJED == "ON"  ) m_UseJED = true;
			else if ( m_SUseJED == "OFF" ) m_UseJED = false;

		}
		// Read configurations: World
		if ( StartsWith(line, "WORLDX") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDX %s", hfile);
			m_SWorldX = hfile;
			m_WorldX = std::stod(m_SWorldX) * mm;
		}
		if ( StartsWith(line, "WORLDY") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDY %s", hfile);
			m_SWorldY = hfile;
			m_WorldY = std::stod(m_SWorldY) * mm;
		}
		if ( StartsWith(line, "WORLDZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "WORLDZ %s", hfile);
			m_SWorldZ = hfile;
			m_WorldZ = std::stod(m_SWorldZ) * mm;
		}
		// Read configurations: Beam
		if ( StartsWith(line, "BEAMPOSITIONX") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMPOSITIONX %s", hfile);
			m_SBeamPX = hfile;
			m_BeamPX = std::stod(m_SBeamPX) * mm;
		}
		if ( StartsWith(line, "BEAMPOSITIONY") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMPOSITIONY %s", hfile);
			m_SBeamPY = hfile;
			m_BeamPY = std::stod(m_SBeamPY) * mm;
		}
		if ( StartsWith(line, "BEAMDELTAX") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMDELTAX %s", hfile);
			m_SBeamDX = hfile;
			m_BeamDX = std::stod(m_SBeamDX) * mm;
		}
		if ( StartsWith(line, "BEAMDELTAY") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMDELTAY %s", hfile);
			m_SBeamDY = hfile;
			m_BeamDY = std::stod(m_SBeamDY) * mm;
		}
		if ( StartsWith(line, "BEAMKINETICENERGY") )
		{
			char hfile[1000];
			sscanf(line.data(), "BEAMKINETICENERGY %s", hfile);
			m_SBeamKE = hfile;
			m_BeamKE = std::stod(m_SBeamKE) * MeV;
		}
		// Read configurations: Pipe
		if ( StartsWith(line, "PIPEPOSITION") )
		{
			char hfile[1000];
			sscanf(line.data(), "PIPEPOSITION %s", hfile);
			m_SPipePZ = hfile;
			m_PipePZ = std::stod(m_SPipePZ) * mm;
		}
		// Read configurations: Target
		if ( StartsWith(line, "USETARGET") )
		{
			char hfile[1000];
			sscanf(line.data(), "USETARGET %s", hfile);
			m_SUseTar = hfile;
			if      ( m_SUseTar == "ON"  ) m_UseTar = true;
			else if ( m_SUseTar == "OFF" ) m_UseTar = false;
		}
		if ( StartsWith(line, "TARGETMATERIAL") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETMATERIAL %s", hfile);
			m_STarMat = hfile;
			m_TarMat = m_STarMat;
		}
		if ( StartsWith(line, "TARGETTHICKNESS") )
		{
			char hfile[1000];
			sscanf(line.data(), "TARGETTHICKNESS %s", hfile);
			m_STarThi = hfile;
			m_TarThi = std::stod(m_STarThi) * mm;
		}
		// Read configurations: Counters
		if ( StartsWith(line, "USESTARTCOUNTER") )
		{
			char hfile[1000];
			sscanf(line.data(), "USESTARTCOUNTER %s", hfile);
			m_SUseStC = hfile;
			if      ( m_SUseStC == "ON"  ) m_UseStC = true;
			else if ( m_SUseStC == "OFF" ) m_UseStC = false;
		}
		if ( StartsWith(line, "STARTCOUNTERLX") )
		{
			char hfile[1000];
			sscanf(line.data(), "STARTCOUNTERLX %s", hfile);
			m_SStCLeX = hfile;
			m_StCLeX = std::stod(m_SStCLeX) * mm;
		}
		if ( StartsWith(line, "STARTCOUNTERLY") )
		{
			char hfile[1000];
			sscanf(line.data(), "STARTCOUNTERLY %s", hfile);
			m_SStCLeY = hfile;
			m_StCLeY = std::stod(m_SStCLeY) * mm;
		}
		if ( StartsWith(line, "STARTCOUNTERLZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "STARTCOUNTERLZ %s", hfile);
			m_SStCLeZ = hfile;
			m_StCLeZ = std::stod(m_SStCLeZ) * mm;
		}
		if ( StartsWith(line, "STARTCOUNTERPX") )
		{
			char hfile[1000];
			sscanf(line.data(), "STARTCOUNTERPX %s", hfile);
			m_SStCPoX = hfile;
			m_StCPoX = std::stod(m_SStCPoX) * mm;
		}
		if ( StartsWith(line, "STARTCOUNTERPY") )
		{
			char hfile[1000];
			sscanf(line.data(), "STARTCOUNTERPY %s", hfile);
			m_SStCPoY = hfile;
			m_StCPoY = std::stod(m_SStCPoY) * mm;
		}
		if ( StartsWith(line, "STARTCOUNTERPZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "STARTCOUNTERPZ %s", hfile);
			m_SStCPoZ = hfile;
			m_StCPoZ = std::stod(m_SStCPoZ) * mm;
		}
		if ( StartsWith(line, "USEDESCINTILLATOR") )
		{
			char hfile[1000];
			sscanf(line.data(), "USEDESCINTILLATOR %s", hfile);
			m_SUseDES = hfile;
			if      ( m_SUseDES == "ON"  ) m_UseDES = true;
			else if ( m_SUseDES == "OFF" ) m_UseDES = false;
		}
		if ( StartsWith(line, "DESCINTILLATORT") )
		{
			char hfile[1000];
			sscanf(line.data(), "DESCINTILLATORT %s", hfile);
			m_SDESThi = hfile;
			m_DESThi = std::stod(m_SDESThi) * mm;
		}
		// Read configurations: Crystals
		if ( StartsWith(line, "DETECTORSETUP") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORSETUP %s", hfile);
			m_SDetSet = hfile;
			if ( m_SDetSet.length() != 120 ) m_DetSet.assign(120, false);
			else
			{
				int temp;
				for ( int i = 0; i < 120; i++ )
				{
					temp = m_SDetSet.data()[i];
					if ( temp == 48 ) m_DetSet[i] = false;
					else m_DetSet[i] = true;
				}
			}
		}
		if ( StartsWith(line, "DETECTORPOSITIONX") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORPOSITIONX %s", hfile);
			m_SDetPoX = hfile;
			m_DetPoX = std::stod(m_SDetPoX) * mm;
		}
		if ( StartsWith(line, "DETECTORPOSITIONY") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORPOSITIONY %s", hfile);
			m_SDetPoY = hfile;
			m_DetPoY = std::stod(m_SDetPoY) * mm;
		}
		if ( StartsWith(line, "DETECTORPOSITIONZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORPOSITIONZ %s", hfile);
			m_SDetPoZ = hfile;
			m_DetPoZ = std::stod(m_SDetPoZ) * mm;
		}
		if ( StartsWith(line, "DETECTORANGLE") )
		{
			char hfile[1000];
			sscanf(line.data(), "DETECTORANGLE %s", hfile);
			m_SDetAng = hfile;
			m_DetAng = std::stod(m_SDetAng) * mm;
		}
		// Read configurations: GEM
		if ( StartsWith(line, "USEGEMDETECTOR") )
		{
			char hfile[1000];
			sscanf(line.data(), "USEGEMDETECTOR %s", hfile);
			m_SUseGEM = hfile;
			if      ( m_SUseGEM == "ON"  ) m_UseGEM = true;
			else if ( m_SUseGEM == "OFF" ) m_UseGEM = false;
		}
		if ( StartsWith(line, "GEMPOSITIONX") )
		{
			char hfile[1000];
			sscanf(line.data(), "GEMPOSITIONX %s", hfile);
			m_SGEMPoX = hfile;
			m_GEMPoX = std::stod(m_SGEMPoX) * mm;
		}
		if ( StartsWith(line, "GEMPOSITIONY") )
		{
			char hfile[1000];
			sscanf(line.data(), "GEMPOSITIONY %s", hfile);
			m_SGEMPoY = hfile;
			m_GEMPoY = std::stod(m_SGEMPoY) * mm;
		}
		if ( StartsWith(line, "GEMPOSITIONZ") )
		{
			char hfile[1000];
			sscanf(line.data(), "GEMPOSITIONZ %s", hfile);
			m_SGEMPoZ = hfile;
			m_GEMPoZ = std::stod(m_SGEMPoZ) * mm;
		}
	}

	PrintConfiguration();

	return true;
}

void BT2017ConMan::PrintConfiguration()
{
	// Computing
	printf(" BT2017ConMan::Load() => USEMULTITHREADS    %s\n", m_SUseMTD.data());
	printf(" BT2017ConMan::Load() => NTHREADS           %s\n", m_SNofTRD.data());
	// Physics                                          
	printf(" BT2017ConMan::Load() => USEJEDIPHYSICS     %s\n", m_SUseJED.data());
	// World                                            
	printf(" BT2017ConMan::Load() => WORLDX             %s\n", m_SWorldX.data());
	printf(" BT2017ConMan::Load() => WORLDY             %s\n", m_SWorldY.data());
	printf(" BT2017ConMan::Load() => WORLDZ             %s\n", m_SWorldZ.data());
	// Beam                                             
	printf(" BT2017ConMan::Load() => BEAMPOSITIONX      %s\n", m_SBeamPX.data());
	printf(" BT2017ConMan::Load() => BEAMPOSITIONY      %s\n", m_SBeamPY.data());
	printf(" BT2017ConMan::Load() => BEAMDELTAX         %s\n", m_SBeamDX.data());
	printf(" BT2017ConMan::Load() => BEAMDELTAY         %s\n", m_SBeamDY.data());
	printf(" BT2017ConMan::Load() => BEAMKINETICENERGY  %s\n", m_SBeamKE.data());
	// Pipe                                             
	printf(" BT2017ConMan::Load() => PIPEPOSITION       %s\n", m_SPipePZ.data());
	// Target                                           
	printf(" BT2017ConMan::Load() => USETARGET          %s\n", m_SUseTar.data());
	printf(" BT2017ConMan::Load() => TARGETMATERIAL     %s\n", m_STarMat.data());
	printf(" BT2017ConMan::Load() => TARGETTHICKNESS    %s\n", m_STarThi.data());
	// Counters                                         
	printf(" BT2017ConMan::Load() => USESTARTCOUNTER    %s\n", m_SUseStC.data());
	printf(" BT2017ConMan::Load() => STARTCOUNTERLX     %s\n", m_SStCLeX.data());
	printf(" BT2017ConMan::Load() => STARTCOUNTERLY     %s\n", m_SStCLeY.data());
	printf(" BT2017ConMan::Load() => STARTCOUNTERLZ     %s\n", m_SStCLeZ.data());
	printf(" BT2017ConMan::Load() => STARTCOUNTERPX     %s\n", m_SStCPoX.data());
	printf(" BT2017ConMan::Load() => STARTCOUNTERPY     %s\n", m_SStCPoY.data());
	printf(" BT2017ConMan::Load() => STARTCOUNTERPZ     %s\n", m_SStCPoZ.data());
	printf(" BT2017ConMan::Load() => USEDESCINTILLATOR  %s\n", m_SUseDES.data());
	printf(" BT2017ConMan::Load() => DESCINTILLATORT    %s\n", m_SDESThi.data());
	// Crystals
	printf(" BT2017ConMan::Load() => DETECTORSETUP      %s\n", m_SDetSet.data());
	printf(" BT2017ConMan::Load() => DETECTORPOSITIONX  %s\n", m_SDetPoX.data());
	printf(" BT2017ConMan::Load() => DETECTORPOSITIONY  %s\n", m_SDetPoY.data());
	printf(" BT2017ConMan::Load() => DETECTORPOSITIONZ  %s\n", m_SDetPoZ.data());
	printf(" BT2017ConMan::Load() => DETECTORANGLE      %s\n", m_SDetAng.data());
	// GEM
	printf(" BT2017ConMan::Load() => USEGEMDETECTOR     %s\n", m_SUseGEM.data());
	printf(" BT2017ConMan::Load() => GEMPOSITIONX       %s\n", m_SGEMPoX.data());
	printf(" BT2017ConMan::Load() => GEMPOSITIONY       %s\n", m_SGEMPoY.data());
	printf(" BT2017ConMan::Load() => GEMPOSITIONZ       %s\n", m_SGEMPoZ.data());
}


//////////////////////////////////////////////////
//   Set & get configurations                   //
//////////////////////////////////////////////////
// Computing
void BT2017ConMan::SetUseMTD(const G4bool useMTD)
{
	m_UseMTD = useMTD;
}
const G4bool BT2017ConMan::GetUseMTD() const
{	
	return m_UseMTD;
}

void BT2017ConMan::SetNofTRD(const G4int nofTRD)
{
	m_NofTRD = nofTRD;
}
const G4int BT2017ConMan::GetNofTRD() const
{	
	return m_NofTRD;
}

// Physics
void BT2017ConMan::SetUseJED(const G4bool useJED)
{
	m_TarMat = useJED;
}
const G4bool BT2017ConMan::GetUseJED() const
{	
	return m_UseJED;
}

// World
void BT2017ConMan::SetWorldX(const G4double worldX)
{
	m_WorldX = worldX;
}
const G4double BT2017ConMan::GetWorldX() const
{	
	return m_WorldX;
}

void BT2017ConMan::SetWorldY(const G4double worldY)
{
	m_WorldY = worldY;
}
const G4double BT2017ConMan::GetWorldY() const
{	
	return m_WorldY;
}

void BT2017ConMan::SetWorldZ(const G4double worldZ)
{
	m_WorldZ = worldZ;
}
const G4double BT2017ConMan::GetWorldZ() const
{	
	return m_WorldZ;
}

// Beam
void BT2017ConMan::SetBeamPX(const G4double beamPX)
{
	m_BeamPX = beamPX;
}
const G4double BT2017ConMan::GetBeamPX() const
{	
	return m_BeamPX;
}

void BT2017ConMan::SetBeamPY(const G4double beamPY)
{
	m_BeamPY = beamPY;
}
const G4double BT2017ConMan::GetBeamPY() const
{	
	return m_BeamPY;
}

void BT2017ConMan::SetBeamDX(const G4double beamDX)
{
	m_BeamDX = beamDX;
}
const G4double BT2017ConMan::GetBeamDX() const
{	
	return m_BeamDX;
}

void BT2017ConMan::SetBeamDY(const G4double beamDY)
{
	m_BeamDY = beamDY;
}
const G4double BT2017ConMan::GetBeamDY() const
{	
	return m_BeamDY;
}

void BT2017ConMan::SetBeamKE(const G4double beamKE)
{
	m_BeamKE = beamKE;
}
const G4double BT2017ConMan::GetBeamKE() const
{	
	return m_BeamKE;
}

// Pipe
void BT2017ConMan::SetPipePZ(const G4double pipePZ)
{
	m_PipePZ = pipePZ;
}
const G4double BT2017ConMan::GetPipePZ() const
{	
	return m_PipePZ;
}

// Target
void BT2017ConMan::SetUseTar(const G4bool useTar)
{
	m_UseTar = useTar;
}
const G4bool BT2017ConMan::GetUseTar() const
{	
	return m_UseTar;
}

void BT2017ConMan::SetTarMat(const G4String tarMat)
{
	m_TarMat = tarMat;
}
const G4String BT2017ConMan::GetTarMat() const
{	
	return m_TarMat;
}

void BT2017ConMan::SetTarThi(const G4double tarThi)
{
	m_TarMat = tarThi;
}
const G4double BT2017ConMan::GetTarThi() const
{	
	return m_TarThi;
}

// Counters
void BT2017ConMan::SetUseStC(const G4bool useStC)
{
	m_UseStC = useStC;
}
const G4bool BT2017ConMan::GetUseStC() const
{	
	return m_UseStC;
}

void BT2017ConMan::SetStCLeX(const G4double stCLeX)
{
	m_StCLeX = stCLeX;
}
const G4double BT2017ConMan::GetStCLeX() const
{	
	return m_StCLeX;
}

void BT2017ConMan::SetStCLeY(const G4double stCLeY)
{
	m_StCLeY = stCLeY;
}
const G4double BT2017ConMan::GetStCLeY() const
{	
	return m_StCLeY;
}

void BT2017ConMan::SetStCLeZ(const G4double stCLeZ)
{
	m_StCLeZ = stCLeZ;
}
const G4double BT2017ConMan::GetStCLeZ() const
{	
	return m_StCLeZ;
}

void BT2017ConMan::SetStCPoX(const G4double stCPoX)
{
	m_StCPoX = stCPoX;
}
const G4double BT2017ConMan::GetStCPoX() const
{	
	return m_StCPoX;
}

void BT2017ConMan::SetStCPoY(const G4double stCPoY)
{
	m_StCPoY = stCPoY;
}
const G4double BT2017ConMan::GetStCPoY() const
{	
	return m_StCPoY;
}

void BT2017ConMan::SetStCPoZ(const G4double stCPoZ)
{
	m_StCPoZ = stCPoZ;
}
const G4double BT2017ConMan::GetStCPoZ() const
{	
	return m_StCPoZ;
}

void BT2017ConMan::SetUseDES(const G4bool useDES)
{
	m_UseDES = useDES;
}
const G4bool BT2017ConMan::GetUseDES() const
{	
	return m_UseDES;
}

void BT2017ConMan::SetDESThi(const G4double dESThi)
{
	m_DESThi = dESThi;
}
const G4double BT2017ConMan::GetDESThi() const
{	
	return m_DESThi;
}

// Crystals
void BT2017ConMan::SetDetSet(const std::vector<G4bool> detSet)	
{
	m_DetSet = detSet;
}
const std::vector<G4bool> BT2017ConMan::GetDetSet() const
{	
	return m_DetSet;
}

void BT2017ConMan::SetDetPoX(const G4double detPoX)
{
	m_DetPoX = detPoX;
}
const G4double BT2017ConMan::GetDetPoX() const
{	
	return m_DetPoX;
}

void BT2017ConMan::SetDetPoY(const G4double detPoY)
{
	m_DetPoY = detPoY;
}
const G4double BT2017ConMan::GetDetPoY() const
{	
	return m_DetPoY;
}

void BT2017ConMan::SetDetPoZ(const G4double detPoZ)
{
	m_DetPoZ = detPoZ;
}
const G4double BT2017ConMan::GetDetPoZ() const
{	
	return m_DetPoZ;
}

void BT2017ConMan::SetDetAng(const G4double detAng)
{
	m_DetAng = detAng;
}
const G4double BT2017ConMan::GetDetAng() const
{	
	return m_DetAng;
}

// GEM
void BT2017ConMan::SetUseGEM(const G4bool useGEM)
{
	m_UseGEM = useGEM;
}
const G4bool BT2017ConMan::GetUseGEM() const
{	
	return m_UseGEM;
}

void BT2017ConMan::SetGEMPoX(const G4double gemPoX)
{
	m_GEMPoX = gemPoX;
}
const G4double BT2017ConMan::GetGEMPoX() const
{	
	return m_GEMPoX;
}

void BT2017ConMan::SetGEMPoY(const G4double gemPoY)
{
	m_GEMPoY = gemPoY;
}
const G4double BT2017ConMan::GetGEMPoY() const
{	
	return m_GEMPoY;
}

void BT2017ConMan::SetGEMPoZ(const G4double gemPoZ)
{
	m_GEMPoZ = gemPoZ;
}
const G4double BT2017ConMan::GetGEMPoZ() const
{	
	return m_GEMPoZ;
}

//////////////////////////////////////////////////
//   Test whether a line starts with ...        //
//////////////////////////////////////////////////
bool BT2017ConMan::StartsWith(const std::string& text, const std::string& token)
{
	if ( text.length() < token.length() ) return false;
	return ( text.compare(0, token.length(), token) == 0 );
}
