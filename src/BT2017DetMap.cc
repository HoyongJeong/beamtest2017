////////////////////////////////////////////////////////////////////////////////
//   BT2017DetMap.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   Definitions of BT2017DetMap class's member functions                     //
//                                                                            //
//                    - 22. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "BT2017DetMap.hh"

//////////////////////////////////////////////////
//   Constructors and destructor                //
//////////////////////////////////////////////////
BT2017DetMap::BT2017DetMap()
{
	Init();
}

BT2017DetMap::~BT2017DetMap()
{
}


//////////////////////////////////////////////////
//   Initialization                             //
//////////////////////////////////////////////////
void BT2017DetMap::Init()
{
	m_DetNameFromDetID.clear();
	m_DetIDFromDetName.clear();

	// Mapping from ID to name
	m_DetNameFromDetID[0]   = "U5_1_5"; m_DetNameFromDetID[1]   = "U5_2_5";
	m_DetNameFromDetID[2]   = "U5_3_5"; m_DetNameFromDetID[3]   = "U5_4_5";
	m_DetNameFromDetID[4]   = "U5_5_5"; m_DetNameFromDetID[5]   = "U4_1_7";
	m_DetNameFromDetID[6]   = "U4_2_7"; m_DetNameFromDetID[7]   = "U4_3_7";
	m_DetNameFromDetID[8]   = "U4_4_7"; m_DetNameFromDetID[9]   = "U4_5_7";
	m_DetNameFromDetID[10]  = "U4_6_7"; m_DetNameFromDetID[11]  = "U4_7_7";
	m_DetNameFromDetID[12]  = "C3_1_4"; m_DetNameFromDetID[13]  = "U3_1_7";
	m_DetNameFromDetID[14]  = "U3_2_7"; m_DetNameFromDetID[15]  = "U3_3_7";
	m_DetNameFromDetID[16]  = "U3_4_7"; m_DetNameFromDetID[17]  = "U3_5_7";
	m_DetNameFromDetID[18]  = "U3_6_7"; m_DetNameFromDetID[19]  = "U3_7_7";
	m_DetNameFromDetID[20]  = "C3_2_4"; m_DetNameFromDetID[21]  = "L4_7_7";
	m_DetNameFromDetID[22]  = "L3_7_7"; m_DetNameFromDetID[23]  = "C2_1_4";
	m_DetNameFromDetID[24]  = "U2_1_5"; m_DetNameFromDetID[25]  = "U2_2_5";
	m_DetNameFromDetID[26]  = "U2_3_5"; m_DetNameFromDetID[27]  = "U2_4_5";
	m_DetNameFromDetID[28]  = "U2_5_5"; m_DetNameFromDetID[29]  = "C2_2_4";
	m_DetNameFromDetID[30]  = "R3_1_7"; m_DetNameFromDetID[31]  = "R4_1_7";
	m_DetNameFromDetID[32]  = "L3_5_5"; m_DetNameFromDetID[33]  = "L4_6_7";
	m_DetNameFromDetID[34]  = "L3_6_7"; m_DetNameFromDetID[35]  = "L2_5_5";
	m_DetNameFromDetID[36]  = "C1_1_4"; m_DetNameFromDetID[37]  = "U1_1_3";
	m_DetNameFromDetID[38]  = "U1_2_3"; m_DetNameFromDetID[39]  = "U1_3_3";
	m_DetNameFromDetID[40]  = "C1_2_4"; m_DetNameFromDetID[41]  = "R2_1_5";
	m_DetNameFromDetID[42]  = "R3_2_7"; m_DetNameFromDetID[43]  = "R4_2_7";
	m_DetNameFromDetID[44]  = "R5_1_5"; m_DetNameFromDetID[45]  = "L3_4_5";
	m_DetNameFromDetID[46]  = "L4_5_7"; m_DetNameFromDetID[47]  = "L3_5_7";
	m_DetNameFromDetID[48]  = "L2_4_5"; m_DetNameFromDetID[49]  = "L1_3_3";
	m_DetNameFromDetID[50]  = "R1_1_3"; m_DetNameFromDetID[51]  = "R2_2_5";
	m_DetNameFromDetID[52]  = "R3_3_7"; m_DetNameFromDetID[53]  = "R4_3_7";
	m_DetNameFromDetID[54]  = "R5_2_5"; m_DetNameFromDetID[55]  = "L5_3_5";
	m_DetNameFromDetID[56]  = "L4_4_7"; m_DetNameFromDetID[57]  = "L3_4_7";
	m_DetNameFromDetID[58]  = "L2_3_5"; m_DetNameFromDetID[59]  = "L1_2_3";
	m_DetNameFromDetID[60]  = "R1_2_3"; m_DetNameFromDetID[61]  = "R2_3_5";
	m_DetNameFromDetID[62]  = "R3_4_7"; m_DetNameFromDetID[63]  = "R4_4_7";
	m_DetNameFromDetID[64]  = "R5_3_5"; m_DetNameFromDetID[65]  = "L5_2_5";
	m_DetNameFromDetID[66]  = "L4_3_7"; m_DetNameFromDetID[67]  = "L3_3_7";
	m_DetNameFromDetID[68]  = "L2_2_5"; m_DetNameFromDetID[69]  = "L1_1_3";
	m_DetNameFromDetID[70]  = "R1_3_3"; m_DetNameFromDetID[71]  = "R2_4_5";
	m_DetNameFromDetID[72]  = "R3_5_7"; m_DetNameFromDetID[73]  = "R4_5_7";
	m_DetNameFromDetID[74]  = "R5_4_5"; m_DetNameFromDetID[75]  = "L5_1_5";
	m_DetNameFromDetID[76]  = "L4_2_7"; m_DetNameFromDetID[77]  = "L3_2_7";
	m_DetNameFromDetID[78]  = "L2_1_5"; m_DetNameFromDetID[79]  = "C1_4_4";
	m_DetNameFromDetID[80]  = "D1_3_3"; m_DetNameFromDetID[81]  = "D1_2_3";
	m_DetNameFromDetID[82]  = "D1_1_3"; m_DetNameFromDetID[83]  = "C1_3_4";
	m_DetNameFromDetID[84]  = "R2_5_5"; m_DetNameFromDetID[85]  = "R3_6_7";
	m_DetNameFromDetID[86]  = "R4_6_7"; m_DetNameFromDetID[87]  = "R5_5_5";
	m_DetNameFromDetID[88]  = "L4_1_7"; m_DetNameFromDetID[89]  = "L3_1_7";
	m_DetNameFromDetID[90]  = "C2_4_4"; m_DetNameFromDetID[91]  = "D2_5_5";
	m_DetNameFromDetID[92]  = "D2_4_5"; m_DetNameFromDetID[93]  = "D2_3_5";
	m_DetNameFromDetID[94]  = "D2_2_5"; m_DetNameFromDetID[95]  = "D2_1_5";
	m_DetNameFromDetID[96]  = "C2_3_4"; m_DetNameFromDetID[97]  = "R3_7_7";
	m_DetNameFromDetID[98]  = "R4_7_7"; m_DetNameFromDetID[99]  = "C3_4_4";
	m_DetNameFromDetID[100] = "D3_7_7"; m_DetNameFromDetID[101] = "D3_6_7";
	m_DetNameFromDetID[102] = "D3_5_7"; m_DetNameFromDetID[103] = "D3_4_7";
	m_DetNameFromDetID[104] = "D3_3_7"; m_DetNameFromDetID[105] = "D3_2_7";
	m_DetNameFromDetID[106] = "D3_1_7"; m_DetNameFromDetID[107] = "C3_3_4";
	m_DetNameFromDetID[108] = "D4_7_7"; m_DetNameFromDetID[109] = "D4_6_7";
	m_DetNameFromDetID[110] = "D4_5_7"; m_DetNameFromDetID[111] = "D4_4_7";
	m_DetNameFromDetID[112] = "D4_3_7"; m_DetNameFromDetID[113] = "D4_2_7";
	m_DetNameFromDetID[114] = "D4_1_7"; m_DetNameFromDetID[115] = "D5_5_5";
	m_DetNameFromDetID[116] = "D5_4_5"; m_DetNameFromDetID[117] = "D5_3_5";
	m_DetNameFromDetID[118] = "D5_2_5"; m_DetNameFromDetID[119] = "D5_1_5";

	// Mapping from name to ID
	for ( int i = 0; i < 120; i++ ) m_DetIDFromDetName[m_DetNameFromDetID[i]] = i;
}


//////////////////////////////////////////////////
//   Get                                        //
//////////////////////////////////////////////////
const G4String BT2017DetMap::GetDetNameFromDetID(G4int id)
{
	return m_DetNameFromDetID[id];
}

const G4int BT2017DetMap::GetDetIDFromDetName(G4String name)
{
	return m_DetIDFromDetName[name];
}
