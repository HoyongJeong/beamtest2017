///////////////////////////////////////////////////////////////////////////////
//   beamtest2017.cc for beamtest2017 of JEDI                                 //
//                                                                            //
//   This is main function of the simulation program.                         //
//                                                                            //
//                    - 20. Nov. 2017. Hoyong Jeong (hyjeong@hep.korea.ac.kr) //
////////////////////////////////////////////////////////////////////////////////

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"

#include "BT2017DetCon.hh"
#include "BT2017PriGenAct.hh"
#include "BT2017ActIni.hh"
#include "BT2017ConMan.hh"

#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4String.hh"
#include "Randomize.hh"

#include "QGSP_BERT.hh"
#include "JediPhysicsListFactory.hh"


int main (int argc, char** argv)
{
	// Randomizer
	CLHEP::RanluxEngine defaultEngine(1234567, 4);
	G4Random::setTheEngine(&defaultEngine);
	G4int seed = time(NULL);
	G4Random::setTheSeed(seed);

	// Detect interactive mode (if any arguments) and define UI session
	G4UIExecutive* UI = 0;
	// argc means how many argument when you execute a program.
	// argv is a array of argument data in character.
	// You should find more information about these.
	if ( argc != 1 ) UI = new G4UIExecutive(argc, argv);

	// Get configuration from file
	// File is in the same path with binary
	char buff[128]; getcwd(buff, 128);
	TString cfgFileName = Form("%s/config.cfg", buff);
	BT2017ConMan* BT2017CM = new BT2017ConMan(cfgFileName);
	
	// Run manager
	G4MTRunManager* RM = new G4MTRunManager();
	G4int nofTRD = BT2017CM -> GetNofTRD();
	RM -> SetNumberOfThreads(nofTRD);

	// Detector construction from configuration (Geometry)
	// We define everything about geomtrical setup in this class.
	BT2017DetCon* BT2017DC = new BT2017DetCon(BT2017CM);
	RM -> SetUserInitialization(BT2017DC);

	// Physics list to be used
	if ( BT2017CM -> GetUseJED() )
	{
		G4VModularPhysicsList* PL = JediPhysicsListFactory::Create();
		RM -> SetUserInitialization(PL);
	}
	else
	{
		G4VModularPhysicsList* PL = new QGSP_BERT;
		PL -> SetVerboseLevel(0);
		RM -> SetUserInitialization(PL);
	}

	// User actions
	RM -> SetUserInitialization(new BT2017ActIni(BT2017CM));

	// Initialize
	RM -> Initialize();

	// Visualization manger
	G4VisManager* VM = new G4VisExecutive();
	VM -> Initialize();

	// Get the pointer to the user interface manager
	G4UImanager* UM = G4UImanager::GetUIpointer();

	// Process macro or start UI session
	if ( !UI )
	{
		// batch mode
		G4UIsession* US = new G4UIterminal(new G4UItcsh);
		US -> SessionStart();

		delete US;
	}

	else
	{
		// Interactive mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UM -> ApplyCommand(command + fileName);
		UI -> SessionStart();

		delete UI;
	}

	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	// owned and deleted by the run manager, so they should not be deleted 
	// in the main() program.
	delete VM;
	delete RM;

	return 0;
}
