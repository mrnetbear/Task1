#ifndef G4_BREMS_PRIMARY_GENERATOR_ACTION_H
#define G4_BREMS_PRIMARY_GENERATOR_ACTION_H 1


#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"



namespace TASK1
{

	class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
	{
	public:
		PrimaryGeneratorAction();
		~PrimaryGeneratorAction();

		virtual void GeneratePrimaries(G4Event*);
		G4bool GetParticleSource(void) const { return fSource; };

		G4ParticleGun* fParticleGun;
		G4bool fSource = true;
		
	};
}


#endif 
