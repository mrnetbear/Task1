// Task1.cc : Defines the entry point for the application.
//

//#include <G4StepLimiter.hh>
//#include <G4UserLimits.hh>
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "QBBC.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"

#include "include/DetectorConstruction.hh"

#include "include/ActionInit.hh"
//#include <G4Types.hh>
//#include <globals.hh>

#include <random>
#include <unistd.h>
#include "Randomize.hh"


#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"//Многопоточный
#else
#include "G4RunManager.hh"//Непараллельный, однопоточное моделирование
#endif


using namespace TASK1;

// for printing
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine); 
	CLHEP::HepRandom::setTheSeed(time(NULL) + getpid()); 

	// Initialize (or don't) a UI
	G4UIExecutive* ui = nullptr;
	if (argc == 1) {
		ui = new G4UIExecutive(argc, argv);
	}


#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
	//Выбор максимального числа потоков в выполняемой системе (на компьютере)
	// либо можно вручную задать число потоков
	runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
#else
	G4RunManager* runManager = new G4RunManager;
#endif

	
	// set 3 required initialization classes
	//auto physicsList = new FTFP_BERT;
	auto physicsList = new QBBC;
 	physicsList->RegisterPhysics(new G4StepLimiterPhysics());
	runManager->SetUserInitialization(new DetectorConstruction());
	runManager->SetUserInitialization(physicsList);
	runManager->SetUserInitialization(new ActionInit());

	// ======================================================================
	// OTHER CLASSES:
	// Vismanager, scoringmanager, etc.
	// ======================================================================

	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();

	// START UI =============================================================

	// get pointer to UI manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// Run macro or start UI
	if (!ui) {
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}
	else {
		// run visualization
		UImanager->ApplyCommand("/control/execute vis.mac");

		// use UI
		ui->SessionStart();
		delete ui;
	}

	// clean up
	delete visManager;
	delete runManager;


	return 0;
}
