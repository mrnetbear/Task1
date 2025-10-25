
#include "../include/EventAction.hh"
#include "G4AnalysisManager.hh"

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

	void EventAction::EndOfEventAction(const G4Event* anEvent) {
		// if there was any energy deposited, tell the analysis manager.

		unsigned int particleCounter = 0;
		if (fEnergy > 80 * keV) {

			auto analysisManager = G4AnalysisManager::Instance();
			// add all the info to the analysis nTuples
			// set the column id's (see runaction)
			G4int energyColumnId = 0;
			G4int cosThetaColumnId = 1;
			//G4double r = sqrt(pow(fPosition.getX(), 2) + pow(fPosition.getY(), 2) + pow(fPosition.getZ(), 2));
			G4double r = fPosition.getR();
			G4double y = fPosition.getY();

			analysisManager->FillNtupleDColumn(energyColumnId, fEnergy);
			analysisManager->FillNtupleDColumn(cosThetaColumnId, y/r);

			// finally, go to the next ntuple row
			analysisManager->AddNtupleRow();
			//G4cout << "Number of particles in this event: " << fParticleCount << G4endl;
			//fParticleCount++;

		}
	}

}