#include "../include/PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4CoulombScattering.hh"
#include "G4Alpha.hh"
#include "QBBC.hh"

namespace TASK1
{
	PhysicsList::PhysicsList() : G4VModularPhysicsList() {
		// Get the standard EM particles
		RegisterPhysics(new G4EmStandardPhysics());
		//RegisterPhysics(new G4EmExtraPhysics());           // доп. EM процессы (γ-nuclear и т.п.)
    	//RegisterPhysics(new G4IonPhysics());               // ионы (α)
		//RegisterPhysics(new G4HadronElasticPhysics());
	}
	PhysicsList::~PhysicsList() {}

	void PhysicsList::ConstructParticle() {
		// Construct particle here
		G4VModularPhysicsList::ConstructParticle();
		
	}
	void PhysicsList::ConstructProcess() {
		// Construct processes here
		G4VModularPhysicsList::ConstructProcess();
		//G4ParticleDefinition* alpha = G4Alpha::Alpha();
    	//G4ProcessManager* pman = alpha->GetProcessManager();
    	//pman->AddDiscreteProcess(new G4CoulombScattering("CoulombScat"));

	}
}