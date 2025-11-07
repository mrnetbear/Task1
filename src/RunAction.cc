
#include "../include/RunAction.hh"
#include "G4ThreeVector.hh"
#include "../include/PrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include <random>

namespace TASK1 {
	RunAction::RunAction() {

		// access analysis manager
		auto analysisManager = G4AnalysisManager::Instance();

		// set default settings
		analysisManager->SetDefaultFileType("root");
		analysisManager->SetNtupleMerging(true);
		analysisManager->SetVerboseLevel(1);
		analysisManager->SetFileName("NTuples");

		// create nTuple to store the data:
		analysisManager->CreateNtuple("Reserford", "Hits");
		// The letters D, I, S, F correspond to types
		analysisManager->CreateNtupleDColumn("Energy"); //   id = 0
		analysisManager->CreateNtupleDColumn("CosTheta"); //id = 1
		analysisManager->CreateNtupleDColumn("CosTheta1"); //id = 2
		analysisManager->CreateNtupleDColumn("ZScore"); //id = 3

		analysisManager->FinishNtuple();

	}

	RunAction::~RunAction() {
	}

	void RunAction::BeginOfRunAction(const G4Run* aRun) {
		auto analysisManager = G4AnalysisManager::Instance();

		analysisManager->OpenFile();
	}

	void RunAction::EndOfRunAction(const G4Run* aRun) {

		auto analysisManager = G4AnalysisManager::Instance();

		// write to output file
		analysisManager->Write();
		analysisManager->CloseFile();

	}

}