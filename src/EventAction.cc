
#include "../include/EventAction.hh"
#include "../include/PrimaryGeneratorAction.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"

namespace TASK1 {

	G4int fParticleCount;
	//G4int counts = 0;
	EventAction::EventAction() {
		fEnergy = 0.;
	//	fParticleCount = 0;
	}

	void EventAction::BeginOfEventAction(const G4Event* anEvent) {
		// begin of event actions here
		fEnergy = 0.;
	//	fParticleCount = 0;
	}
	
	// setting energy and position
	void EventAction::AddEnergy(G4double e) { fEnergy += e; }
	
	void EventAction::SetPosition(G4ThreeVector p) { fPosition = p; }

	void EventAction::SetLaunchPosition(G4ThreeVector p) { fLaunchPosition= p; }

	void EventAction::SetSource(G4bool src) { fSource = src; }

	void EventAction::EndOfEventAction(const G4Event* anEvent) {
		// if there was any energy deposited, tell the analysis manager.

		unsigned int particleCounter = 0;
		if (fEnergy) {

			auto analysisManager = G4AnalysisManager::Instance();
			const auto primaryGenerator = static_cast<const PrimaryGeneratorAction*>(
			G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction()
			);
			
			fSource = primaryGenerator->GetParticleSource();
			// add all the info to the analysis nTuples
			// set the column id's (see runaction)
			G4int energyColumnId = 0;
			G4int cosThetaColumnId = 1;
			G4int cosThetaColumnId1 = 2;
			G4int zColumnId = 3;
			//G4double r = sqrt(pow(fPosition.getX(), 2) + pow(fPosition.getY(), 2) + pow(fPosition.getZ(), 2));
			G4double r = sqrt(pow((fLaunchPosition.getX() - fPosition.getX()), 2) 
				+ pow((fLaunchPosition.getY() - fPosition.getY()), 2)
				+ pow((fLaunchPosition.getZ() - fPosition.getZ()), 2));
			G4double z = fLaunchPosition.getZ() - fPosition.getZ();

			analysisManager->FillNtupleDColumn(energyColumnId, fEnergy);
			if (fSource)
				analysisManager->FillNtupleDColumn(cosThetaColumnId, z/r);
			else
				analysisManager->FillNtupleDColumn(cosThetaColumnId1, z/r);
			analysisManager->FillNtupleDColumn(zColumnId, z);

			// finally, go to the next ntuple row
			analysisManager->AddNtupleRow();
			//G4cout << "Number of particles in this event: " << fParticleCount << G4endl;
			//fParticleCount++;

		}
	}

}