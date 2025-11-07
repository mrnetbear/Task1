#ifndef G4_BREMS_DETECTOR_CONSTRUCTION_H
#define G4_BREMS_DETECTOR_CONSTRUCTION_H 1

#include "G4VUserDetectorConstruction.hh"

class G4UserLimits;

namespace TASK1
{
	class DetectorConstruction : public G4VUserDetectorConstruction
	{
	public:
		DetectorConstruction() = default;
		~DetectorConstruction() override = default;

		G4VPhysicalVolume* Construct() override;

		G4LogicalVolume* GetDetector() const { return fDetector; }
		G4LogicalVolume* GetPlate() const { return fPlate; }

	private:
		G4LogicalVolume* fDetector = nullptr;
		G4LogicalVolume* fPlate = nullptr;
		G4UserLimits* fStepLimit;
	};
}


#endif