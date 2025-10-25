#include "../include/PrimaryGeneratorAction.hh"
#include "Randomize.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include <random>
#include "G4RandomDirection.hh"

namespace TASK1
{

	PrimaryGeneratorAction::PrimaryGeneratorAction() { //executes once

		static const double pi = 3.14159265358979323846;

	
	//---------------------particle parameters---------------------
		G4int nParticles = 1; //particles ammount
		fParticleGun = new G4ParticleGun(nParticles);

		const G4String& particleName = "alpha"; //particle

		G4double posZ = 4.5 * mm;
		G4ThreeVector position = G4ThreeVector(0, 0, posZ); //particle gun position

		G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
		G4ParticleDefinition* particle  = particleTable->FindParticle(particleName);
		fParticleGun->SetParticleDefinition(particle);
		fParticleGun->SetParticlePosition(position);
		
	}

	PrimaryGeneratorAction::~PrimaryGeneratorAction() {
		delete fParticleGun;
	}
     
	void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event){ //this function is called at the begining of each event
		

		G4ThreeVector momentumDirection = G4ThreeVector(0, 0, -1); //partcle momentum direction

		
		G4double energy1 = 5.5 * MeV, energy2 = 22. * MeV; //particle energy

		if ((double)rand() / RAND_MAX > .5)
			fParticleGun->SetParticleEnergy(energy1);
		else
			fParticleGun->SetParticleEnergy(energy2);
		fParticleGun->SetParticleMomentumDirection(momentumDirection); 
		fParticleGun->GeneratePrimaryVertex(event); 
	} 
	
}