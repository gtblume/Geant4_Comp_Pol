#include "DetectorConstruction.hh"
#include "ComptonTabulatedField3D.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Colour.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4PolarizationManager.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4Tubs.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include <string>

DetectorConstruction::DetectorConstruction()
{
  // fField.Put(0);
}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 8*cm, env_sizeZ = 30*cm;
  // G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.*env_sizeXY;
  G4double world_sizeZ  = 1.*env_sizeZ;
  G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");
  G4double z1 = 1.;
  G4double vacuum_mass_of_mole = 1.008*g/mole;
  G4double vacuum_density = 1.e-25*g/cm3;
  G4double vacuum_temp = 2.73*kelvin;
  G4double vacuum_pressure = 3.e-18*pascal;
  G4Material* Vacuum = new G4Material("Vacuum",z1,vacuum_mass_of_mole,vacuum_density,kStateGas,
                                       vacuum_temp,vacuum_pressure);

  // G4Material* plastic = new G4Material("Plastic",)
  // here we acquire PVC
  // G4Material* PVCPlastic = nist->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
  //here we define brass
  // G4Material* Brass = nist->FindOrBuildMaterial("G4_BRASS");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       1*world_sizeXY, 1*world_sizeXY, 1*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        Vacuum,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(0,0,0*cm),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

G4Box* solidAir =
  new G4Box("Air",                       //its name
  1*world_sizeXY, 1*world_sizeXY, 26*cm);     //its size

G4LogicalVolume* logicAir =
  new G4LogicalVolume(solidAir,          //its solid
                      Air,           //its material
                      "Air");            //its name

G4VPhysicalVolume* physAir =
  new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(0,0,4*cm),       //at (0,0,0)
                    logicAir,            //its logical volume
                    "Air",               //its name
                    logicWorld,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

// copper radiator
G4Material* test_mat = nist->FindOrBuildMaterial("G4_Cu");
G4ThreeVector postest3 = G4ThreeVector(0*cm, 0*cm, -22.3*cm);

// Cylinder section shape
G4double stest3_rmina =  0*cm, stest3_rmaxa = 1.75*cm;
G4double stest3_rminb =  0*cm, stest3_rmaxb = 1.75*cm;
G4double stest3_hz = 3*mm;
G4double stest3_phimin = 0.*deg, stest3_phimax = 360.*deg;

G4Cons* solidtest3 =
  new G4Cons("test3",
  stest3_rmina, stest3_rmaxa, stest3_rminb, stest3_rmaxb, stest3_hz,
  stest3_phimin, stest3_phimax);

G4LogicalVolume* logictest3 =
  new G4LogicalVolume(solidtest3,         //its solid
                      test_mat,          //its material
                      "test3");           //its name

  new G4PVPlacement(0,                       //no rotation
                    postest3,                    //at position
                    logictest3,             //its logical volume
                    "test3",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

//field region
G4Box* solidregion =
  new G4Box("FR",                       //its name
  61*mm, 61*mm, 101*mm);     //its size

logicregion =
  new G4LogicalVolume(solidregion,          //its solid
                      Air,           //its material
                      "FR");            //its name

  new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(0,0,-.35*cm),       //at (0,0,0)
                    logicregion,            //its logical volume
                    "FR",               //its name
                    logicAir,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

// Scoring Walls
// non physical
G4ThreeVector pos0 = G4ThreeVector(0*cm,0*cm,-10.8*cm);
G4ThreeVector pos1 = G4ThreeVector(0*cm,0*cm,10.1*cm);
G4ThreeVector pos2 = G4ThreeVector(0*cm,0*cm,24.8*cm);
//
// //wall dimensions
G4double wall_dxa = 16*cm, wall_dxb = 16*cm;
G4double wall_dya = 16*cm, wall_dyb = 16*cm;
G4double wall_dz  = .01*cm;
G4Trd* solidwall =
  new G4Trd("Wall",                      //its name
            0.5*wall_dxa, 0.5*wall_dxb,
            0.5*wall_dya, 0.5*wall_dyb, 0.5*wall_dz); //its size

logicwall =
  new G4LogicalVolume(solidwall,         //its solid
                      Air,          //its material
                      "Wall");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos0,                    //at position
                    logicwall,             //its logical volume
                    "Wall",                //its name
                    logicAir,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4Trd* solidwall1 =
  new G4Trd("Wall",                      //its name
  0.5*wall_dxa, 0.5*wall_dxb,
  0.5*wall_dya, 0.5*wall_dyb, 0.5*wall_dz); //its size

logicwall1 =
  new G4LogicalVolume(solidwall1,         //its solid
                      Air,          //its material
                      "Wall1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicwall1,             //its logical volume
                    "Wall1",                //its name
                    logicAir,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4Trd* solidwall2 =
  new G4Trd("Wall2",                      //its name
  0.5*wall_dxa, 0.5*wall_dxb,
  0.5*wall_dya, 0.5*wall_dyb, 0.5*wall_dz); //its size

logicwall2 =
  new G4LogicalVolume(solidwall2,         //its solid
                      Air,          //its material
                      "Wall2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicwall2,             //its logical volume
                    "Wall2",                //its name
                    logicAir,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// iron target
G4Material* coremat = nist->FindOrBuildMaterial("G4_Fe");
G4ThreeVector poscore = G4ThreeVector(0*cm, 0*cm, 0*cm);

// Cylinder section shape
G4double core_rmina =  0*cm, core_rmaxa = 2.2*cm;
G4double core_rminb =  0*cm, core_rmaxb = 2.2*cm;
G4double core_hz = 43.5*mm;
G4double core_phimin = 0.*deg, core_phimax = 360.*deg;

G4Cons* solidcore =
  new G4Cons("Core",
  core_rmina, core_rmaxa, core_rminb, core_rmaxb, core_hz,
  core_phimin, core_phimax);

logiccore =
  new G4LogicalVolume(solidcore,         //its solid
                      coremat,          //its material
                      "Core");           //its name

  new G4PVPlacement(0,                       //no rotation
                    poscore,                    //at position
                    logiccore,             //its logical volume
                    "Core",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4PolarizationManager * polMgr = G4PolarizationManager::GetInstance();
polMgr->SetVolumePolarization(logiccore,G4ThreeVector(0,0,1)); //

// crystal
G4Material* BGOmat = nist->FindOrBuildMaterial("G4_BGO");
G4ThreeVector posBGO = G4ThreeVector(0*cm, 0*cm, 17.45*cm);

G4double BGO_rmina =  0.*cm, BGO_rmaxa = 2.5*cm;
G4double BGO_rminb =  0.*cm, BGO_rmaxb = 2.5*cm;
G4double BGO_hz = 7*cm;
G4double BGO_phimin = 0.*deg, BGO_phimax = 360.*deg;

G4Cons* solidBGO =
  new G4Cons("BGO",            // its name
  BGO_rmina, BGO_rmaxa, BGO_rminb, BGO_rmaxb, BGO_hz,
  BGO_phimin, BGO_phimax); // its size

logicBGO =
  new G4LogicalVolume(
                      solidBGO,        // its solid
                      BGOmat,          // its material
                      "BGO");          // its name

  new G4PVPlacement(
                    0,                // no rotation
                    posBGO, //  its position
                    logicBGO,       // its logical volume
                    "BGO",           // its name
                    logicAir,          // its mother  volume
                    false,            // no boolean operation
                    0,                // copy number
                    checkOverlaps);  // checking overlaps
//
//
G4VisAttributes* BGOVisAttributes =
  new G4VisAttributes(G4Colour(1,0,1));
G4VisAttributes* CoreVisAttributes =
  new G4VisAttributes(G4Colour(1,0,0));
G4VisAttributes* radVisAttributes =
  new G4VisAttributes(G4Colour(1,1,0));
G4VisAttributes* magVisAttributes =
  new G4VisAttributes(G4Colour(0,1,1));
logicBGO->SetVisAttributes(BGOVisAttributes);
logiccore->SetVisAttributes(CoreVisAttributes);
logictest3->SetVisAttributes(radVisAttributes);
logicregion->SetVisAttributes(magVisAttributes);

  return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
  //4-.35
  G4double zOffset = -3.65*cm;
  G4MagneticField* magField = new TabulatedField3D("B_Field_Full_cm.TABLE", zOffset);
  // // magField->GetFieldValue();
  //
  // G4MagneticField* magField = new G4UniformMagField(G4ThreeVector(0.*tesla,0,1*tesla));
  auto localpFieldManager = new G4FieldManager(magField);
  logicregion->SetFieldManager(localpFieldManager,true);
}
