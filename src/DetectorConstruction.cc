
#include "../include/DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Scintillation.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"


#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"

#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"


#include "G4SubtractionSolid.hh"
#include "G4BooleanSolid.hh"


namespace TASK1
{
	G4VPhysicalVolume* DetectorConstruction::Construct()
	{



		// construct our detectors here

        // Get nist material manager
        G4NistManager* nist = G4NistManager::Instance();


		// Start with constructing the world:
        G4double worldSize = 10 * cm;
        G4Material* vacuum = nist->FindOrBuildMaterial("G4_Galactic");
        //G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

        auto solidWorld = new G4Box("World",
            worldSize / 2,
            worldSize / 2,
            worldSize / 2);

        auto logicWorld = new G4LogicalVolume(solidWorld,
            vacuum,
            "World");

        auto physWorld = new G4PVPlacement(nullptr,
            G4ThreeVector(), 
            logicWorld, 
            "World", 
            nullptr, 
            false, 
            0);

        //---------------------Detector construction------------------------

        // golden plate
        G4ThreeVector posPlate = G4ThreeVector(0, 0, 0);
        G4double shape0_XY = 1.*cm, width = 2.*um;
        auto plate = new G4Box("plate", 
            0.5 * shape0_XY, 
            0.5 * shape0_XY, 
            0.5 * width);
        
        auto logicPlate = new G4LogicalVolume(plate, nist->FindOrBuildMaterial("G4_Au"), "plate");
        new G4PVPlacement(0, posPlate, logicPlate, "plate", logicWorld, false, 0);


        G4double tubeShapeD = 10 * cm, tubeHeightZ = 5 * cm;
        auto tube = new G4Tubs("tube",
            tubeShapeD / 2.0 - 4 * mm, 
            tubeShapeD / 2.0,
            tubeHeightZ / 2.0,
            0.0 * deg,
            360.0 * deg);

        auto logicTube = new G4LogicalVolume(tube, nist->FindOrBuildMaterial("G4_Pb"), "tube");

        G4RotationMatrix* tubeRotation = new G4RotationMatrix();
        tubeRotation -> rotateX(90 * deg);

        new G4PVPlacement(tubeRotation, posPlate, logicTube, "tube", logicWorld, false, 0);
        //---------------------colourization---------------------  

        G4Colour grey(0.5, 0.5, 0.5);
        G4Colour yellow(1.0, 1.0, 0.0);

        G4VisAttributes* VisAtt_1 = new G4VisAttributes(yellow);
        G4VisAttributes* VisAtt_2 = new G4VisAttributes(grey);
        VisAtt_1->SetForceSolid(true);
        VisAtt_2->SetForceSolid(true);
        logicPlate->SetVisAttributes(VisAtt_1);
        logicTube->SetVisAttributes(VisAtt_2);

        //setting plate as scoring volume
        fDetector = logicTube;

        return physWorld;
    }

}