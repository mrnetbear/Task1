#ifndef G4_BREMS_DETECTOR_CONSTRUCTION_H
#define G4_BREMS_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"

namespace TASK1
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() override = default;

		G4VPhysicalVolume* Construct() override;

		G4LogicalVolume* GetDetector() const { return fDetector; }

	private:
		G4LogicalVolume* fDetector = nullptr;
	};
}


#endif