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
  G4double env_sizeXY = 30*cm, env_sizeZ = 95*cm;
  // G4Material* Air = nist->FindOrBuildMaterial("G4_AIR");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  // frontentry = 318.275*mm;
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
  G4Material* Lead = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* Alum = nist->FindOrBuildMaterial("G4_Al");
  G4Material* Copper = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* Steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       1*world_sizeXY, 1*world_sizeXY, 1*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        Air,           //its material
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

// vacuum tube
G4ThreeVector posvac = G4ThreeVector(0*cm, 0*cm, -40*cm);

// Cylinder section shape
G4double vac_rmina =  0*cm, vac_rmaxa = 1.75*cm;
G4double vac_rminb =  0*cm, vac_rmaxb = 1.75*cm;
G4double vac_hz = 400*mm;
G4double vac_phimin = 0.*deg, vac_phimax = 360.*deg;

G4Cons* solidvac =
  new G4Cons("vac",
  vac_rmina, vac_rmaxa, vac_rminb, vac_rmaxb, vac_hz,
  vac_phimin, vac_phimax);

G4LogicalVolume* logicvac =
  new G4LogicalVolume(solidvac,         //its solid
                      Vacuum,          //its material
                      "vac");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posvac,                    //at position
                    logicvac,             //its logical volume
                    "vac",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// steel pipe
// G4Material* test_mat = nist->FindOrBuildMaterial("G4_Cu");
G4ThreeVector pospipe = G4ThreeVector(0*cm, 0*cm, -6.3*cm);

// Cylinder section shape
G4double stest_rmina =  1.6*cm, stest_rmaxa = 1.75*cm;
G4double stest_rminb =  1.6*cm, stest_rmaxb = 1.75*cm;
G4double stest_hz2 = 33.7*cm;
G4double stest_phimin = 0.*deg, stest_phimax = 360.*deg;

G4Cons* solidpipe =
  new G4Cons("pipe",
  stest_rmina, stest_rmaxa, stest_rminb, stest_rmaxb, stest_hz2,
  stest_phimin, stest_phimax);

G4LogicalVolume* logicpipe =
  new G4LogicalVolume(solidpipe,         //its solid
                      Steel,          //its material
                      "pipe");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pospipe,                    //at position
                    logicpipe,             //its logical volume
                    "pipe",                //its name
                    logicvac,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// 7mm copper apature
// G4Material* test_mat = nist->FindOrBuildMaterial("G4_Cu");
G4ThreeVector poshole = G4ThreeVector(0*cm, 0*cm, -36.8*cm);

// Cylinder section shape
G4double stest_rminahole =  .7*cm, stest_rmaxahole = 1.6*cm;
G4double stest_rminbhole =  .7*cm, stest_rmaxbhole = 1.6*cm;
G4double stest_hz2hole = .01*cm;
// G4double stest_phimin = 0.*deg, stest_phimax = 360.*deg;

G4Cons* solidhole =
  new G4Cons("hole",
  stest_rminahole, stest_rmaxahole, stest_rminbhole, stest_rmaxbhole, stest_hz2hole,
  stest_phimin, stest_phimax);

G4LogicalVolume* logichole =
  new G4LogicalVolume(solidhole,         //its solid
                      Copper,          //its material
                      "hole");           //its name

  new G4PVPlacement(0,                       //no rotation
                    poshole,                    //at position
                    logichole,             //its logical volume
                    "hole",                //its name
                    logicvac,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// copper target tube 1
G4Material* test_mat = nist->FindOrBuildMaterial("G4_Cu");
G4ThreeVector postest = G4ThreeVector(0*cm, 0*cm, 29.925*cm);

// Cylinder section shape
// G4double stest_rmina =  1.6*cm, stest_rmaxa = 1.75*cm;
// G4double stest_rminb =  1.6*cm, stest_rmaxb = 1.75*cm;
G4double stest_hz = 25.25*mm;
// G4double stest_phimin = 0.*deg, stest_phimax = 360.*deg;

G4Cons* solidtest =
  new G4Cons("test",
  stest_rmina, stest_rmaxa, stest_rminb, stest_rmaxb, stest_hz,
  stest_phimin, stest_phimax);

G4LogicalVolume* logictest =
  new G4LogicalVolume(solidtest,         //its solid
                      test_mat,          //its material
                      "test");           //its name

  new G4PVPlacement(0,                       //no rotation
                    postest,                    //at position
                    logictest,             //its logical volume
                    "test",                //its name
                    logicvac,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// copper target tube 2
// G4Material* test_mat = nist->FindOrBuildMaterial("G4_Cu");
G4ThreeVector postest2 = G4ThreeVector(0*cm, 0*cm, 35.925*cm);

// Cylinder section shape
G4double stest2_rmina =  1.15*cm, stest2_rmaxa = 1.75*cm;
G4double stest2_rminb =  1.15*cm, stest2_rmaxb = 1.75*cm;
G4double stest2_hz = 34.75*mm;
G4double stest2_phimin = 0.*deg, stest2_phimax = 360.*deg;

G4Cons* solidtest2 =
  new G4Cons("test2",
  stest2_rmina, stest2_rmaxa, stest2_rminb, stest2_rmaxb, stest2_hz,
  stest2_phimin, stest2_phimax);

G4LogicalVolume* logictest2 =
  new G4LogicalVolume(solidtest2,         //its solid
                      test_mat,          //its material
                      "test2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    postest2,                    //at position
                    logictest2,             //its logical volume
                    "test2",                //its name
                    logicvac,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// copper radiator
// G4Material* test_mat = nist->FindOrBuildMaterial("G4_Cu");
G4ThreeVector postest3 = G4ThreeVector(0*cm, 0*cm, 39.7*cm);

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
                    logicvac,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

//*****************************************************************************
//visualization only (collimation)

// // Cylinder section shape
// G4double stest4_rmina =  0*cm, stest4_rmaxa = .4*cm;
// G4double stest4_rminb =  0*cm, stest4_rmaxb = .4*cm;
// // G4double stest3_hz = 3*mm;
// // G4double stest3_phimin = 0.*deg, stest3_phimax = 360.*deg;
//
// G4Cons* solidtest4 =
//   new G4Cons("test4",
//   stest4_rmina, stest4_rmaxa, stest4_rminb, stest4_rmaxb, stest3_hz,
//   stest3_phimin, stest3_phimax);
//
// logictest4 =
//   new G4LogicalVolume(solidtest4,         //its solid
//                       test_mat,          //its material
//                       "test4");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     G4ThreeVector(0,0,0*cm),                    //at position
//                     logictest4,             //its logical volume
//                     "test4",                //its name
//                     logictest3,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// // Cylinder section shape
// G4double stest5_rmina =  .4*cm, stest5_rmaxa = 1.75*cm;
// G4double stest5_rminb =  .4*cm, stest5_rmaxb = 1.75*cm;
// // G4double stest3_hz = 3*mm;
// // G4double stest3_phimin = 0.*deg, stest3_phimax = 360.*deg;
//
// G4Cons* solidtest5 =
//   new G4Cons("test5",
//   stest5_rmina, stest5_rmaxa, stest5_rminb, stest5_rmaxb, stest3_hz,
//   stest3_phimin, stest3_phimax);
//
// logictest5 =
//   new G4LogicalVolume(solidtest5,         //its solid
//                       test_mat,          //its material
//                       "test5");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     G4ThreeVector(0,0,0*cm),                    //at position
//                     logictest5,             //its logical volume
//                     "test5",                //its name
//                     logictest3,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking


//**********************************************************************************
//colimator p1
G4Material* col_mat = nist->FindOrBuildMaterial("G4_Cu");
G4ThreeVector pocol1 = G4ThreeVector(0*cm, 0*cm, 59.775*mm);

// Cylinder section shape
G4double col_rmina =  .4*cm, col_rmaxa = 5*cm;
G4double col_rminb =  .4*cm, col_rmaxb = 5*cm;
G4double col_hz = 49.775*mm;
G4double col_phimin = 0.*deg, col_phimax = 360.*deg;

G4Cons* solidcol =
  new G4Cons("col",
  col_rmina, col_rmaxa, col_rminb, col_rmaxb, col_hz,
  col_phimin, col_phimax);


G4LogicalVolume* logiccol =
  new G4LogicalVolume(solidcol,         //its solid
                      col_mat,          //its material
                      "col");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pocol1,                    //at position
                    logiccol,             //its logical volume
                    "col",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



//field region
G4Box* solidregion =
  new G4Box("FR",                       //its name
  60*mm, 60*mm, 100*mm);     //its size

logicregion =
  new G4LogicalVolume(solidregion,          //its solid
                      Air,           //its material
                      "FR");            //its name

  new G4PVPlacement(0,                     //no rotation
                    G4ThreeVector(0,0,209.775*mm),       //at (0,0,0)
                    logicregion,            //its logical volume
                    "FR",               //its name
                    logicWorld,                     //its mother  volume
                    false,                 //no boolean operation
                    0,                     //copy number
                    checkOverlaps);        //overlaps checking

// colimator p2
// G4Material* col_mat = nist->FindOrBuildMaterial("G4_Cu");
G4ThreeVector pocol2 = G4ThreeVector(0*cm, 0*cm, -76.75*mm);

// Cylinder section shape
G4double col2_rmina =  .4*cm, col2_rmaxa = 5*cm;
G4double col2_rminb =  .4*cm, col2_rmaxb = 5*cm;
G4double col2_hz = 23.25*mm;
G4double col2_phimin = 0.*deg, col2_phimax = 360.*deg;

G4Cons* solidcol2 =
  new G4Cons("col2",
  col2_rmina, col2_rmaxa, col2_rminb, col2_rmaxb, col2_hz,
  col2_phimin, col2_phimax);


G4LogicalVolume* logiccol2 =
  new G4LogicalVolume(solidcol2,         //its solid
                      col_mat,          //its material
                      "col2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pocol2,                    //at position
                    logiccol2,             //its logical volume
                    "col2",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// Scoring Walls
// non physical
G4ThreeVector pos0 = G4ThreeVector(0*cm,0*cm,.1*cm);
G4ThreeVector pos1 = G4ThreeVector(0*cm,0*cm,-5*cm);
G4ThreeVector pos2 = G4ThreeVector(0*cm,0*cm,50*cm);
G4ThreeVector pos3 = G4ThreeVector(0*cm,0*cm,-10*cm);
//
// //wall dimensions
G4double wall_dxa = 8*cm, wall_dxb = 8*cm;
G4double wall_dya = 8*cm, wall_dyb = 8*cm;
G4double wall_dz  = .01*cm;
G4Trd* solidwall =
  new G4Trd("Wall",                      //its name
            0.25*wall_dxa, 0.25*wall_dxb,
            0.25*wall_dya, 0.25*wall_dyb, 0.5*wall_dz); //its size

logicwall =
  new G4LogicalVolume(solidwall,         //its solid
                      Air,          //its material
                      "Wall");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos0,                    //at position
                    logicwall,             //its logical volume
                    "Wall",                //its name
                    logicWorld,                //its mother  volume
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
                    logicregion,                //its mother  volume
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
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4Cons* solidwall3 =
  new G4Cons("Wall3",
  0.9*vac_rmina, 0.9*vac_rmaxa, 0.9*vac_rminb, 0.9*vac_rmaxb, 0.001*cm,
  vac_phimin, vac_phimax);

logicwall3 =
  new G4LogicalVolume(solidwall3,         //its solid
                      Vacuum,          //its material
                      "Wall3");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at position
                    logicwall3,             //its logical volume
                    "Wall3",                //its name
                    logicvac,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


//*********************************************************
// magnet Geometry

// iron center
G4Material* coremat = nist->FindOrBuildMaterial("G4_Fe");
G4ThreeVector poscore = G4ThreeVector(0*cm, 0*cm, 0*cm);

// Cylinder section shape
G4double core_rmina =  0*cm, core_rmaxa = 1.89*cm;
G4double core_rminb =  0*cm, core_rmaxb = 1.89*cm;
G4double core_hz = 25*mm;
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


//side ramps
G4ThreeVector posside = G4ThreeVector(0*cm, 0*cm, 2.83*cm);

// Cylinder section shape
G4double core1_rmina =  0*cm, core1_rmaxa = 1.89*cm;
G4double core1_rminb =  0*cm, core1_rmaxb = 2.55*cm;
G4double core1_hz = 3.3*mm;
// G4double core_phimin = 0.*deg, core_phimax = 360.*deg;

G4Cons* solidside =
  new G4Cons("Side",
  core1_rmina, core1_rmaxa, core1_rminb, core1_rmaxb, core1_hz,
  core_phimin, core_phimax);

logicside =
  new G4LogicalVolume(solidside,         //its solid
                      coremat,          //its material
                      "Side");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posside,                    //at position
                    logicside,             //its logical volume
                    "Side",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posside11 = G4ThreeVector(0*cm, 0*cm, -2.83*cm);

// Cylinder section shape
// G4double core1_rmina =  0*cm, core1_rmaxa = 1.89*cm;
// G4double core1_rminb =  0*cm, core1_rmaxb = 2.55*cm;
// G4double core1_hz = 3.3*mm;
// G4double core_phimin = 0.*deg, core_phimax = 360.*deg;

G4Cons* solidside1 =
  new G4Cons("Side1",
  core1_rmina, core1_rmaxb, core1_rminb, core1_rmaxa, core1_hz,
  core_phimin, core_phimax);

logicside1 =
  new G4LogicalVolume(solidside1,         //its solid
                      coremat,          //its material
                      "Side1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posside11,                    //at position
                    logicside1,             //its logical volume
                    "Side1",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector poscap = G4ThreeVector(0*cm, 0*cm, 3.755*cm);

// Cylinder section shape
G4double cap_rmina =  1.225*cm, cap_rmaxa = 4.45*cm;
G4double cap_rminb =  1.875*cm, cap_rmaxb = 4.45*cm;
G4double cap_hz = 5.95*mm;
// G4double core_phimin = 0.*deg, core_phimax = 360.*deg;

G4Cons* solidcap =
  new G4Cons("cap",
  cap_rmina, cap_rmaxa, cap_rminb, cap_rmaxb, cap_hz,
  core_phimin, core_phimax);

logiccap =
  new G4LogicalVolume(solidcap,         //its solid
                      coremat,          //its material
                      "cap");           //its name

  new G4PVPlacement(0,                       //no rotation
                    poscap,                    //at position
                    logiccap,             //its logical volume
                    "cap",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector poscap1 = G4ThreeVector(0*cm, 0*cm, -3.755*cm);

// Cylinder section shape
// G4double cap_rmina =  1.225*cm, cap_rmaxa = 4.45*cm;
// G4double cap_rminb =  1.875*cm, cap_rmaxb = 4.45*cm;
// G4double cap_hz = 5.95*mm;
// G4double core_phimin = 0.*deg, core_phimax = 360.*deg;

G4Cons* solidcap1 =
  new G4Cons("cap1",
  cap_rminb, cap_rmaxb, cap_rmina, cap_rmaxa, cap_hz,
  core_phimin, core_phimax);

logiccap1 =
  new G4LogicalVolume(solidcap1,         //its solid
                      coremat,          //its material
                      "cap1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    poscap1,                    //at position
                    logiccap1,             //its logical volume
                    "cap1",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector poscoil11 = G4ThreeVector(0*cm, 0*cm, -2.83*cm);

// Cylinder section shape
// G4double core1_rmina =  0*cm, core1_rmaxa = 1.89*cm;
// G4double core1_rminb =  0*cm, core1_rmaxb = 2.55*cm;
// G4double core1_hz = 3.3*mm;
// G4double core_phimin = 0.*deg, core_phimax = 360.*deg;

G4Cons* solidcoil1 =
  new G4Cons("Coil1",
  core1_rmaxb, cap_rmaxb, core1_rmaxa, cap_rmaxa, core1_hz,
  core_phimin, core_phimax);

logiccoil1 =
  new G4LogicalVolume(solidcoil1,         //its solid
                      test_mat,          //its material
                      "Coil1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    poscoil11,                    //at position
                    logiccoil1,             //its logical volume
                    "Coil1",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector poscoil1 = G4ThreeVector(0*cm, 0*cm, 2.83*cm);

// Cylinder section shape
// G4double core1_rmina =  0*cm, core1_rmaxa = 1.89*cm;
// G4double core1_rminb =  0*cm, core1_rmaxb = 2.55*cm;
// G4double core1_hz = 3.3*mm;
// G4double core_phimin = 0.*deg, core_phimax = 360.*deg;

G4Cons* solidcoil =
  new G4Cons("Coil",
  core1_rmaxa, cap_rmaxb, core1_rmaxb, cap_rmaxa, core1_hz,
  core_phimin, core_phimax);

logiccoil =
  new G4LogicalVolume(solidcoil,         //its solid
                      test_mat,          //its material
                      "Coil");           //its name

  new G4PVPlacement(0,                       //no rotation
                    poscoil1,                    //at position
                    logiccoil,             //its logical volume
                    "Coil",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector poscorecoil = G4ThreeVector(0*cm, 0*cm, 0*cm);

// Cylinder section shape
// G4double core_rmina =  0*cm, core_rmaxa = 1.89*cm;
// G4double core_rminb =  0*cm, core_rmaxb = 1.89*cm;
// G4double core_hz = 25*mm;
// G4double core_phimin = 0.*deg, core_phimax = 360.*deg;

G4Cons* solidcorecoil =
  new G4Cons("CoreCoil",
  core_rmaxa, cap_rmaxa, core_rmaxb, cap_rmaxb, core_hz,
  core_phimin, core_phimax);

logiccorecoil =
  new G4LogicalVolume(solidcorecoil,         //its solid
                      test_mat,          //its material
                      "CoreCoil");           //its name

  new G4PVPlacement(0,                       //no rotation
                    poscorecoil,                    //at position
                    logiccorecoil,             //its logical volume
                    "CoreCoil",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4PolarizationManager * polMgr = G4PolarizationManager::GetInstance();
polMgr->SetVolumePolarization(logiccore,G4ThreeVector(0,0,1));
polMgr->SetVolumePolarization(logicside,G4ThreeVector(0,0,1));
polMgr->SetVolumePolarization(logicside1,G4ThreeVector(0,0,1));
polMgr->SetVolumePolarization(logiccap,G4ThreeVector(0,0,1));
polMgr->SetVolumePolarization(logiccap1,G4ThreeVector(0,0,1)); //

// crystal
G4Material* BGOmat = nist->FindOrBuildMaterial("G4_BGO");
G4ThreeVector posBGO = G4ThreeVector(0*cm, 0*cm, 388.275*mm);

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
                    logicWorld,          // its mother  volume
                    false,            // no boolean operation
                    0,                // copy number
                    checkOverlaps);  // checking overlaps


//// blocking Walls
//front
// G4Material* BGOmat = nist->FindOrBuildMaterial("G4_BGO");
G4ThreeVector posBGOfront = G4ThreeVector(0*cm, 0*cm, 315.275*mm);

// G4double BGO_rmina =  0.*cm, BGO_rmaxa = 2.5*cm;
// G4double BGO_rminb =  0.*cm, BGO_rmaxb = 2.5*cm;
G4double BGOf_hz = .1*cm;
// G4double BGO_phimin = 0.*deg, BGO_phimax = 360.*deg;

G4Cons* solidBGOf =
  new G4Cons("BGOf",            // its name
  BGO_rmina, BGO_rmaxa, BGO_rminb, BGO_rmaxb, BGOf_hz,
  BGO_phimin, BGO_phimax); // its size

logicBGOf =
  new G4LogicalVolume(
                      solidBGOf,        // its solid
                      Air,          // its material
                      "BGOf");          // its name

  new G4PVPlacement(
                    0,                // no rotation
                    posBGOfront, //  its position
                    logicBGOf,       // its logical volume
                    "BGOf",           // its name
                    logicWorld,          // its mother  volume
                    false,            // no boolean operation
                    0,                // copy number
                    checkOverlaps);  // checking overlaps

//back
G4ThreeVector posBGOback = G4ThreeVector(0*cm, 0*cm, 461.275*mm);

// G4double BGO_rmina =  0.*cm, BGO_rmaxa = 2.5*cm;
// G4double BGO_rminb =  0.*cm, BGO_rmaxb = 2.5*cm;
// G4double BGOf_hz = .1*cm;
// G4double BGO_phimin = 0.*deg, BGO_phimax = 360.*deg;

G4Cons* solidBGOb =
  new G4Cons("BGOb",            // its name
  BGO_rmina, BGO_rmaxa, BGO_rminb, BGO_rmaxb, BGOf_hz,
  BGO_phimin, BGO_phimax); // its size

logicBGOb =
  new G4LogicalVolume(
                      solidBGOb,        // its solid
                      Air,          // its material
                      "BGOb");          // its name

  new G4PVPlacement(
                    0,                // no rotation
                    posBGOback, //  its position
                    logicBGOb,       // its logical volume
                    "BGOb",           // its name
                    logicWorld,          // its mother  volume
                    false,            // no boolean operation
                    0,                // copy number
                    checkOverlaps);  // checking overlaps

//side
G4ThreeVector posBGOside = G4ThreeVector(0*cm, 0*cm, 388.275*mm);

G4double BGOs_rmina =  2.55*cm, BGOs_rmaxa = 2.6*cm;
G4double BGOs_rminb =  2.55*cm, BGOs_rmaxb = 2.6*cm;
// G4double BGO_hz = 7*cm;
// G4double BGO_phimin = 0.*deg, BGO_phimax = 360.*deg;

G4Cons* solidBGOs =
  new G4Cons("BGOs",            // its name
  BGOs_rmina, BGOs_rmaxa, BGOs_rminb, BGOs_rmaxb, BGO_hz,
  BGO_phimin, BGO_phimax); // its size

logicBGOs =
  new G4LogicalVolume(
                      solidBGOs,        // its solid
                      Air,          // its material
                      "BGOs");          // its name

  new G4PVPlacement(
                    0,                // no rotation
                    posBGOside, //  its position
                    logicBGOs,       // its logical volume
                    "BGOs",           // its name
                    logicWorld,          // its mother  volume
                    false,            // no boolean operation
                    0,                // copy number
                    checkOverlaps);  // checking overlaps

G4Material* copper = nist->FindOrBuildMaterial("G4_Cu");

// absorber 1
//
//wall dimensions
G4double abs_dxa = 11*cm, abs_dxb = 11*cm;
G4double abs_dya = 10.25*cm, abs_dyb = 10.25*cm;
G4double abs_dz  = 1.4*cm;

G4ThreeVector posabs11 = G4ThreeVector(0*cm,.25*cm,88.5*mm);

G4Trd* solidabs11 =
  new G4Trd("abs11",                      //its name
  0.5*abs_dxa, 0.5*abs_dxb,
  0.5*abs_dya, 0.5*abs_dyb, 0.5*abs_dz); //its size

G4LogicalVolume* logicabs11 =
  new G4LogicalVolume(solidabs11,         //its solid
                      copper,          //its material
                      "abs11");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posabs11,                    //at position
                    logicabs11,             //its logical volume
                    "abs11",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// absorber 2
G4ThreeVector posabs2 = G4ThreeVector(0*cm,.25*cm,74.5*mm);

//wall dimensions
// G4double abs_dxa = 11*cm, abs_dxb = 11*cm;
// G4double abs_dya = 10.5*cm, abs_dyb = 10.5*cm;
// G4double abs_dz  = 1.4*cm;
G4Trd* solidabs2 =
  new G4Trd("abs2",                      //its name
  0.5*abs_dxa, 0.5*abs_dxb,
  0.5*abs_dya, 0.5*abs_dyb, 0.5*abs_dz); //its size

G4LogicalVolume* logicabs2 =
  new G4LogicalVolume(solidabs2,         //its solid
                      copper,          //its material
                      "abs2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posabs2,                    //at position
                    logicabs2,             //its logical volume
                    "abs2",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// absorber 3
G4ThreeVector posabs3 = G4ThreeVector(0*cm,.25*cm,60.5*mm);

//wall dimensions
// G4double abs_dxa = 11*cm, abs_dxb = 11*cm;
// G4double abs_dya = 10.5*cm, abs_dyb = 10.5*cm;
// G4double abs_dz  = 1.4*cm;
G4Trd* solidabs3 =
  new G4Trd("abs3",                      //its name
  0.5*abs_dxa, 0.5*abs_dxb,
  0.5*abs_dya, 0.5*abs_dyb, 0.5*abs_dz); //its size

G4LogicalVolume* logicabs3 =
  new G4LogicalVolume(solidabs3,         //its solid
                      copper,          //its material
                      "abs3");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posabs3,                    //at position
                    logicabs3,             //its logical volume
                    "abs3",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


//******************************************************************* case bgo
G4Material* Brass = nist->FindOrBuildMaterial("G4_BRASS");

// inner wall front side
G4ThreeVector posiwallz1 = G4ThreeVector(0*cm,.125*cm,313.025*mm);
//
// // wall dimensions
G4double iwall1_dxa = 8.5*cm, iwall1_dxb = 8.5*cm;
G4double iwall1_dya = 8.5*cm, iwall1_dyb = 8.5*cm;
G4double iwall1_dz  = .25*cm;
G4Trd* solidiwall1 =
  new G4Trd("iWall1",                      //its name
  0.5*iwall1_dxa, 0.5*iwall1_dxb,
  0.5*iwall1_dya, 0.5*iwall1_dyb, 0.5*iwall1_dz); //its size

G4LogicalVolume* logiciwall1 =
  new G4LogicalVolume(solidiwall1,         //its solid
                      Brass,          //its material
                      "iWall1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posiwallz1,                    //at position
                    logiciwall1,             //its logical volume
                    "iWall1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


// outer wall front side in region
G4ThreeVector posowallz1 = G4ThreeVector(0*cm,.125*cm,99.75*mm);
//
//wall dimensions
G4double owall1_dxa = 11*cm, owall1_dxb = 11*cm;
G4double owall1_dya = 10*cm, owall1_dyb = 10*cm;
G4double owall1_dz  = .025*cm;
G4Trd* solidowall1 =
  new G4Trd("oWall1",                      //its name
  0.5*owall1_dxa, 0.5*owall1_dxb,
  0.5*owall1_dya, 0.5*owall1_dyb, 0.5*owall1_dz); //its size

G4LogicalVolume* logicowall1 =
  new G4LogicalVolume(solidowall1,         //its solid
                      Brass,          //its material
                      "oWall1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz1,                    //at position
                    logicowall1,             //its logical volume
                    "oWall1",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// outer wall front side
G4ThreeVector posowallz12 = G4ThreeVector(0*cm,.125*cm,310.775*mm);
//
//wall dimensions
// G4double owall1_dxa = 11*cm, owall1_dxb = 11*cm;
// G4double owall1_dya = 10*cm, owall1_dyb = 10*cm;
G4double owall1_dz2  = .2*cm;
G4Trd* solidowall12 =
  new G4Trd("oWall12",                      //its name
  0.5*owall1_dxa, 0.5*owall1_dxb,
  0.5*owall1_dya, 0.5*owall1_dyb, 0.5*owall1_dz2); //its size

G4LogicalVolume* logicowall12 =
  new G4LogicalVolume(solidowall12,         //its solid
                      Brass,          //its material
                      "oWall12");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz12,                    //at position
                    logicowall12,             //its logical volume
                    "oWall12",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
// //
// outer wall top side
G4ThreeVector posowallz222 = G4ThreeVector(0*cm,5.25*cm,506.525*mm);

//wall dimensions
G4double owall2_dxa = 11*cm, owall2_dxb = 11*cm;
G4double owall2_dya = .25*cm, owall2_dyb = .25*cm;
G4double owall2_dz22  = 393.5*mm;
G4Trd* solidowall222 =
  new G4Trd("oWall222",                      //its name
  0.5*owall2_dxa, 0.5*owall2_dxb,
  0.5*owall2_dya, 0.5*owall2_dyb, 0.5*owall2_dz22); //its size

G4LogicalVolume* logicowall222 =
  new G4LogicalVolume(solidowall222,         //its solid
                      Brass,          //its material
                      "oWall222");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz222,                    //at position
                    logicowall222,             //its logical volume
                    "oWall22",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// outer wall top side upper bit outside region
G4ThreeVector posowallz2222 = G4ThreeVector(0*cm,5.5*cm,316.525*mm);

//wall dimensions
// G4double owall2_dxa = 11*cm, owall2_dxb = 11*cm;
// G4double owall2_dya = .25*cm, owall2_dyb = .25*cm;
G4double owall2_dz222  = 13.5*mm;
G4Trd* solidowall2222 =
  new G4Trd("oWall2222",                      //its name
  0.5*owall2_dxa, 0.5*owall2_dxb,
  0.5*owall2_dya, 0.5*owall2_dyb, 0.5*owall2_dz222); //its size

G4LogicalVolume* logicowall2222 =
  new G4LogicalVolume(solidowall2222,         //its solid
                      Brass,          //its material
                      "oWall2222");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz2222,                    //at position
                    logicowall2222,             //its logical volume
                    "oWall222",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// outer wall top side in region
G4ThreeVector posowallz2 = G4ThreeVector(0*cm,5.25*cm,99.75*mm);

//wall dimensions
// G4double owall2_dxa = 11*cm, owall2_dxb = 11*cm;
// G4double owall2_dya = .25*cm, owall2_dyb = .25*cm;
G4double owall2_dz  = .05*cm;
G4Trd* solidowall2 =
  new G4Trd("oWall2",                      //its name
  0.5*owall2_dxa, 0.5*owall2_dxb,
  0.5*owall2_dya, 0.5*owall2_dyb, 0.5*owall2_dz); //its size

G4LogicalVolume* logicowall2 =
  new G4LogicalVolume(solidowall2,         //its solid
                      Brass,          //its material
                      "oWall2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz2,                    //at position
                    logicowall2,             //its logical volume
                    "oWall2",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// toppiece above absorbers

G4ThreeVector posowallz22 = G4ThreeVector(0*cm,5.5*cm,76.75*mm);

//wall dimensions
// G4double owall2_dxa = 11*cm, owall2_dxb = 11*cm;
// G4double owall2_dya = .25*cm, owall2_dyb = .25*cm;
G4double owall2_dz2  = 46.5*mm;
G4Trd* solidowall22 =
  new G4Trd("oWall22",                      //its name
  0.5*owall2_dxa, 0.5*owall2_dxb,
  0.5*owall2_dya, 0.5*owall2_dyb, 0.5*owall2_dz2); //its size

G4LogicalVolume* logicowall22 =
  new G4LogicalVolume(solidowall22,         //its solid
                      Brass,          //its material
                      "oWall22");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz22,                    //at position
                    logicowall22,             //its logical volume
                    "oWall22",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// // outer wall bottom side
G4ThreeVector posowallz32 = G4ThreeVector(0*cm,-5*cm,506.525*mm);

//wall dimensions
G4double owall3_dxa = 11*cm, owall3_dxb = 11*cm;
G4double owall3_dya = .25*cm, owall3_dyb = .25*cm;
G4double owall3_dz2  = 393.5*mm;
G4Trd* solidowall32 =
  new G4Trd("oWall32",                      //its name
  0.5*owall3_dxa, 0.5*owall3_dxb,
  0.5*owall3_dya, 0.5*owall3_dyb, 0.5*owall3_dz2); //its size

G4LogicalVolume* logicowall32 =
  new G4LogicalVolume(solidowall32,         //its solid
                      Brass,          //its material
                      "oWall32");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz32,                    //at position
                    logicowall32,             //its logical volume
                    "oWall32",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

// // outer wall bottom side in region
G4ThreeVector posowallz3 = G4ThreeVector(0*cm,-5*cm,76.75*mm);

//wall dimensions
// G4double owall3_dxa = 11*cm, owall3_dxb = 11*cm;
// G4double owall3_dya = .25*cm, owall3_dyb = .25*cm;
G4double owall3_dz  = 46.5*mm;
G4Trd* solidowall3 =
  new G4Trd("oWall3",                      //its name
  0.5*owall3_dxa, 0.5*owall3_dxb,
  0.5*owall3_dya, 0.5*owall3_dyb, 0.5*owall3_dz); //its size

G4LogicalVolume* logicowall3 =
  new G4LogicalVolume(solidowall3,         //its solid
                      Brass,          //its material
                      "oWall3");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz3,                    //at position
                    logicowall3,             //its logical volume
                    "oWall3",                //its name
                    logicregion,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
//
// outer wall back side
G4ThreeVector posowallz4 = G4ThreeVector(0*cm,.125*cm,702.05*mm);

G4Trd* solidowall4 =
  new G4Trd("oWall4",                      //its name
  0.5*owall1_dxa, 0.5*owall1_dxb,
  0.5*owall1_dya, 0.5*owall1_dyb, .125*cm); //its size

G4LogicalVolume* logicowall4 =
  new G4LogicalVolume(solidowall4,         //its solid
                      Brass,          //its material
                      "oWall4");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz4,                    //at position
                    logicowall4,             //its logical volume
                    "oWall4",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

//
// outer wall right side
G4ThreeVector posowallz6 = G4ThreeVector(-5.375*cm,.125*cm,506.275*mm);

//wall dimensions
G4double owall6_dxa = .25*cm, owall6_dxb = .25*cm;
G4double owall6_dya = 10*cm, owall6_dyb = 10*cm;
G4double owall6_dz  = 389*mm;
G4Trd* solidowall6 =
  new G4Trd("oWall6",                      //its name
  0.5*owall6_dxa, 0.5*owall6_dxb,
  0.5*owall6_dya, 0.5*owall6_dyb, 0.5*owall6_dz); //its size

G4LogicalVolume* logicowall6 =
  new G4LogicalVolume(solidowall6,         //its solid
                      Brass,          //its material
                      "oWall6");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz6,                    //at position
                    logicowall6,             //its logical volume
                    "oWall6",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

//
// outer wall left side
G4ThreeVector posowallz5 = G4ThreeVector(5.375*cm,.125*cm,506.275*mm);

//wall dimensions
G4double owall5_dxa = .25*cm, owall5_dxb = .25*cm;
G4double owall5_dya = 10*cm, owall5_dyb = 10*cm;
G4double owall5_dz  = 389*mm;
G4Trd* solidowall5 =
  new G4Trd("oWall5",                      //its name
  0.5*owall5_dxa, 0.5*owall5_dxb,
  0.5*owall5_dya, 0.5*owall5_dyb, 0.5*owall5_dz); //its size

G4LogicalVolume* logicowall5 =
  new G4LogicalVolume(solidowall5,         //its solid
                      Brass,          //its material
                      "oWall5");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posowallz5,                    //at position
                    logicowall5,             //its logical volume
                    "oWall5",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

//********************************************************************************** lead

// G4ThreeVector posileadback = G4ThreeVector(0*cm,5.4375*cm,792.175*mm);
// //
// // // wall dimensions
// G4double iwall1l_dxa = 50.8*cm, iwall1l_dxb = 50.8*cm;
// G4double iwall1l_dya = 25.4*cm, iwall1l_dyb = 25.4*cm;
// G4double iwall1l_dz  = 5.08*cm;
// G4Trd* solidlead1 =
//   new G4Trd("lead1",                      //its name
//   0.5*iwall1l_dxa, 0.5*iwall1l_dxb,
//   0.5*iwall1l_dya, 0.5*iwall1l_dyb, 0.5*iwall1l_dz); //its size
//
// G4LogicalVolume* logiclead1 =
//   new G4LogicalVolume(solidlead1,         //its solid
//                       Lead,          //its material
//                       "lead1");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadback,                    //at position
//                     logiclead1,             //its logical volume
//                     "lead1",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadleft = G4ThreeVector(-20.32*cm,5.4375*cm,360.375*mm);
//
// // wall dimensions
// G4double iwall1ll_dxa = 10.16*cm, iwall1ll_dxb = 10.16*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz  = 81.28*cm;
// G4Trd* solidlead2 =
//   new G4Trd("lead2",                      //its name
//   0.5*iwall1ll_dxa, 0.5*iwall1ll_dxb,
//   0.5*iwall1ll_dya, 0.5*iwall1ll_dyb, 0.5*iwall1ll_dz); //its size
//
// G4LogicalVolume* logiclead2 =
//   new G4LogicalVolume(solidlead2,         //its solid
//                       Lead,          //its material
//                       "lead2");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadleft,                    //at position
//                     logiclead2,             //its logical volume
//                     "lead2",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadright = G4ThreeVector(20.32*cm,5.4375*cm,360.375*mm);
//
// // wall dimensions
// // G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz  = 91.44*cm;
// G4Trd* solidlead3 =
//   new G4Trd("lead3",                      //its name
//   0.5*iwall1ll_dxa, 0.5*iwall1ll_dxb,
//   0.5*iwall1ll_dya, 0.5*iwall1ll_dyb, 0.5*iwall1ll_dz); //its size
//
// G4LogicalVolume* logiclead3 =
//   new G4LogicalVolume(solidlead3,         //its solid
//                       Lead,          //its material
//                       "lead3");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadright,                    //at position
//                     logiclead3,             //its logical volume
//                     "lead3",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadtop = G4ThreeVector(0*cm,21.9475*cm,360.375*mm);
//
// // wall dimensions
// // G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz2  = 91.44*cm;
// G4Trd* solidlead4 =
//   new G4Trd("lead4",                      //its name
//   25.4*cm, 25.4*cm,
//   2.54*cm, 2.54*cm, 0.5*iwall1ll_dz2); //its size
//
// G4LogicalVolume* logiclead4 =
//   new G4LogicalVolume(solidlead4,         //its solid
//                       Lead,          //its material
//                       "lead4");           //its name
//   new G4PVPlacement(0,                       //no rotation
//                     posileadtop,                    //at position
//                     logiclead4,             //its logical volume
//                     "lead4",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadbottom = G4ThreeVector(0*cm,-19.605*cm,360.375*mm);
// // wall dimensions
// // G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
//
// G4Trd* solidlead5 =
//   new G4Trd("lead5",                      //its name
//   15.24*cm, 15.24*cm,
//   2.54*cm, 2.54*cm, 0.5*iwall1ll_dz); //its size
//
// G4LogicalVolume* logiclead5 =
//   new G4LogicalVolume(solidlead5,         //its solid
//                       Lead,          //its material
//                       "lead5");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadbottom,                    //at position
//                     logiclead5,             //its logical volume
//                     "lead5",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posisheettop = G4ThreeVector(0*cm,18.7725*cm,360.375*mm);
// // wall dimensions
// G4double iwall1ll_dxa2 = 1*cm, iwall1ll_dxb2 = 1*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
// G4Trd* solidsheet =
//   new G4Trd("sheet",                      //its name
//   26.4*cm, 26.4*cm,
//   0.6*iwall1ll_dxa2, 0.6*iwall1ll_dxb2, 0.5*iwall1ll_dz2); //its size
//
// G4LogicalVolume* logicsheet =
//   new G4LogicalVolume(solidsheet,         //its solid
//                       Alum,          //its material
//                       "sheet");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posisheettop,                    //at position
//                     logicsheet,             //its logical volume
//                     "sheet",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadfrontb = G4ThreeVector(0*cm,-4.725*cm,-71.425*mm);
// // wall dimensions
// // G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
// G4Trd* solidfb =
//   new G4Trd("fb",                      //its name
//   0.5*iwall1l_dxa, 0.5*iwall1l_dxb,
//   2.54*cm, 2.54*cm, 0.5*iwall1l_dz); //its size
//
// G4LogicalVolume* logicfb =
//   new G4LogicalVolume(solidfb,         //its solid
//                       Lead,          //its material
//                       "fb");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadfrontb,                    //at position
//                     logicfb,             //its logical volume
//                     "fb",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadfrontt = G4ThreeVector(0*cm,10.5175*cm,-71.425*mm);
// // wall dimensions
// // G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
// G4Trd* solidft =
//   new G4Trd("ft",                      //its name
//   0.5*iwall1l_dxa, 0.5*iwall1l_dxb,
//   7.62*cm, 7.62*cm, 0.5*iwall1l_dz); //its size
//
// G4LogicalVolume* logicft =
//   new G4LogicalVolume(solidft,         //its solid
//                       Lead,          //its material
//                       "ft");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadfrontt,                    //at position
//                     logicft,             //its logical volume
//                     "ft",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadfrontl = G4ThreeVector(-15.24*cm,.3575*cm,-71.425*mm);
// // wall dimensions
// // G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
// G4Trd* solidfl =
//   new G4Trd("fl",                      //its name
//   10.16*cm, 10.16*cm,
//   2.54*cm, 2.54*cm, 0.5*iwall1l_dz); //its size
//
// G4LogicalVolume* logicfl =
//   new G4LogicalVolume(solidfl,         //its solid
//                       Lead,          //its material
//                       "fl");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadfrontl,                    //at position
//                     logicfl,             //its logical volume
//                     "fl",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);
//
// G4ThreeVector posileadfrontr = G4ThreeVector(15.24*cm,.3575*cm,-71.425*mm);
// // wall dimensions
// // G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
// G4Trd* solidfr =
//   new G4Trd("fr",                      //its name
//   10.16*cm, 10.16*cm,
//   2.54*cm, 2.54*cm, 0.5*iwall1l_dz); //its size
//
// G4LogicalVolume* logicfr =
//   new G4LogicalVolume(solidfr,         //its solid
//                       Lead,          //its material
//                       "fr");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadfrontr,                    //at position
//                     logicfr,             //its logical volume
//                     "fr",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//

/////////////////////////////////////////////////////////////////////////////////////////////////

//********************************************************************************** lead open config


// G4ThreeVector posileadback = G4ThreeVector(0*cm,-9.8025*cm,766.775*mm);
// //
// // // wall dimensions
// G4double iwall1l_dxa = 50.8*cm, iwall1l_dxb = 50.8*cm;
// G4double iwall1l_dya = 10.16*cm, iwall1l_dyb = 10.16*cm;
// G4double iwall1l_dz  = 10.16*cm;
// G4Trd* solidlead1 =
//   new G4Trd("lead1",                      //its name
//   0.5*iwall1l_dxa, 0.5*iwall1l_dxb,
//   0.5*iwall1l_dya, 0.5*iwall1l_dyb, 0.5*iwall1l_dz); //its size
//
// G4LogicalVolume* logiclead1 =
//   new G4LogicalVolume(solidlead1,         //its solid
//                       Lead,          //its material
//                       "lead1");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadback,                    //at position
//                     logiclead1,             //its logical volume
//                     "lead1",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadleft = G4ThreeVector(-20.32*cm,-9.8025*cm,347.675*mm);
//
// // wall dimensions
// G4double iwall1ll_dxa = 10.16*cm, iwall1ll_dxb = 10.16*cm;
// G4double iwall1ll_dya = 10.16*cm, iwall1ll_dyb = 10.16*cm;
// G4double iwall1ll_dz  = 73.66*cm;
// G4Trd* solidlead2 =
//   new G4Trd("lead2",                      //its name
//   0.5*iwall1ll_dxa, 0.5*iwall1ll_dxb,
//   0.5*iwall1ll_dya, 0.5*iwall1ll_dyb, 0.5*iwall1ll_dz); //its size
//
// G4LogicalVolume* logiclead2 =
//   new G4LogicalVolume(solidlead2,         //its solid
//                       Lead,          //its material
//                       "lead2");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadleft,                    //at position
//                     logiclead2,             //its logical volume
//                     "lead2",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadright = G4ThreeVector(20.32*cm,-9.8025*cm,347.675*mm);
//
// // wall dimensions
// // G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz  = 91.44*cm;
// G4Trd* solidlead3 =
//   new G4Trd("lead3",                      //its name
//   0.5*iwall1ll_dxa, 0.5*iwall1ll_dxb,
//   0.5*iwall1ll_dya, 0.5*iwall1ll_dyb, 0.5*iwall1ll_dz); //its size
//
// G4LogicalVolume* logiclead3 =
//   new G4LogicalVolume(solidlead3,         //its solid
//                       Lead,          //its material
//                       "lead3");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadright,                    //at position
//                     logiclead3,             //its logical volume
//                     "lead3",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector posileadinside = G4ThreeVector(0*cm,-12.3425*cm,347.675*mm);
// // wall dimensions
// // G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
//
// G4Trd* solidlead7 =
//   new G4Trd("lead7",                      //its name
//   5.08*cm, 5.08*cm,
//   2.54*cm, 2.54*cm, 0.5*iwall1ll_dz); //its size
//
// G4LogicalVolume* logiclead7 =
//   new G4LogicalVolume(solidlead7,         //its solid
//                       Lead,          //its material
//                       "lead7");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadinside,                    //at position
//                     logiclead7,             //its logical volume
//                     "lead7",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
//
// G4ThreeVector posileadbottom = G4ThreeVector(0*cm,-25.0425*cm,347.675*mm);
// // wall dimensions
// // G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
//
// G4Trd* solidlead5 =
//   new G4Trd("lead5",                      //its name
//   15.24*cm, 15.24*cm,
//   2.54*cm, 2.54*cm, 0.5*iwall1ll_dz+2.54*cm); //its size
//
// G4LogicalVolume* logiclead5 =
//   new G4LogicalVolume(solidlead5,         //its solid
//                       Lead,          //its material
//                       "lead5");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadbottom,                    //at position
//                     logiclead5,             //its logical volume
//                     "lead5",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
//
// G4ThreeVector posileadfrontb = G4ThreeVector(0*cm,-9.8205*cm,-71.425*mm);
// // wall dimensions
// // G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// // G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// // G4double iwall1ll_dz2  = 101.6*cm;
// G4Trd* solidfb =
//   new G4Trd("fb",                      //its name
//   0.5*iwall1l_dxa, 0.5*iwall1l_dxb,
//   5.08*cm, 5.08*cm, 0.5*iwall1l_dz); //its size
//
// G4LogicalVolume* logicfb =
//   new G4LogicalVolume(solidfb,         //its solid
//                       Lead,          //its material
//                       "fb");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     posileadfrontb,                    //at position
//                     logicfb,             //its logical volume
//                     "fb",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking
//
// G4ThreeVector positable = G4ThreeVector(0*cm,-17.5225*cm,347.675*mm);
// G4double iwall1ll_dz2  = 93.98*cm;
//
// G4Trd* solidtable =
//   new G4Trd("table",                      //its name
//   27.4*cm, 27.4*cm,
//   2.54*cm, 2.54*cm, 0.53*iwall1ll_dz2); //its size
//
// G4LogicalVolume* logictable =
//   new G4LogicalVolume(solidtable,         //its solid
//                       Alum,          //its material
//                       "table");           //its name
//
//   new G4PVPlacement(0,                       //no rotation
//                     positable,                    //at position
//                     logictable,             //its logical volume
//                     "table",                //its name
//                     logicWorld,                //its mother  volume
//                     false,                   //no boolean operation
//                     0,                       //copy number
//                     checkOverlaps);          //overlaps checking

//

/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

//********************************************************************************** lead closed config


G4ThreeVector posileadback = G4ThreeVector(0*cm,-2.1825*cm,766.775*mm);
//
// // wall dimensions
G4double iwall1l_dxa = 50.8*cm, iwall1l_dxb = 50.8*cm;
G4double iwall1l_dya = 25.4*cm, iwall1l_dyb = 25.4*cm;
G4double iwall1l_dz  = 10.16*cm;
G4Trd* solidlead1 =
  new G4Trd("lead1",                      //its name
  0.5*iwall1l_dxa, 0.5*iwall1l_dxb,
  0.5*iwall1l_dya, 0.5*iwall1l_dyb, 0.5*iwall1l_dz); //its size

G4LogicalVolume* logiclead1 =
  new G4LogicalVolume(solidlead1,         //its solid
                      Lead,          //its material
                      "lead1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadback,                    //at position
                    logiclead1,             //its logical volume
                    "lead1",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posileadleft = G4ThreeVector(-20.32*cm,-2.1825*cm,347.675*mm);

// wall dimensions
G4double iwall1ll_dxa = 10.16*cm, iwall1ll_dxb = 10.16*cm;
G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
G4double iwall1ll_dz  = 73.66*cm;
G4Trd* solidlead2 =
  new G4Trd("lead2",                      //its name
  0.5*iwall1ll_dxa, 0.5*iwall1ll_dxb,
  0.5*iwall1ll_dya, 0.5*iwall1ll_dyb, 0.5*iwall1ll_dz); //its size

G4LogicalVolume* logiclead2 =
  new G4LogicalVolume(solidlead2,         //its solid
                      Lead,          //its material
                      "lead2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadleft,                    //at position
                    logiclead2,             //its logical volume
                    "lead2",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posileadleftinside = G4ThreeVector(-12.7*cm,-2.1825*cm,347.675*mm);

// wall dimensions
// G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz  = 91.44*cm;
G4Trd* solidlead9 =
  new G4Trd("lead9",                      //its name
  0.25*iwall1ll_dxa, 0.25*iwall1ll_dxb,
  0.5*iwall1ll_dya, 0.5*iwall1ll_dyb, 0.25*iwall1ll_dz); //its size

G4LogicalVolume* logiclead9 =
  new G4LogicalVolume(solidlead9,         //its solid
                      Lead,          //its material
                      "lead9");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadleftinside,                    //at position
                    logiclead9,             //its logical volume
                    "lead9",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


G4ThreeVector posileadright = G4ThreeVector(20.32*cm,-2.1825*cm,347.675*mm);

// wall dimensions
// G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz  = 91.44*cm;
G4Trd* solidlead3 =
  new G4Trd("lead3",                      //its name
  0.5*iwall1ll_dxa, 0.5*iwall1ll_dxb,
  0.5*iwall1ll_dya, 0.5*iwall1ll_dyb, 0.5*iwall1ll_dz); //its size

G4LogicalVolume* logiclead3 =
  new G4LogicalVolume(solidlead3,         //its solid
                      Lead,          //its material
                      "lead3");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadright,                    //at position
                    logiclead3,             //its logical volume
                    "lead3",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posileadrightinside = G4ThreeVector(12.7*cm,-2.1825*cm,347.675*mm);

// wall dimensions
// G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz  = 91.44*cm;
G4Trd* solidlead8 =
  new G4Trd("lead8",                      //its name
  0.25*iwall1ll_dxa, 0.25*iwall1ll_dxb,
  0.5*iwall1ll_dya, 0.5*iwall1ll_dyb, 0.25*iwall1ll_dz); //its size

G4LogicalVolume* logiclead8 =
  new G4LogicalVolume(solidlead8,         //its solid
                      Lead,          //its material
                      "lead8");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadrightinside,                    //at position
                    logiclead8,             //its logical volume
                    "lead8",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posileadinside = G4ThreeVector(0*cm,-12.3425*cm,347.675*mm);
// wall dimensions
// G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz2  = 101.6*cm;

G4Trd* solidlead7 =
  new G4Trd("lead7",                      //its name
  5.08*cm, 5.08*cm,
  2.54*cm, 2.54*cm, 0.5*iwall1ll_dz); //its size

G4LogicalVolume* logiclead7 =
  new G4LogicalVolume(solidlead7,         //its solid
                      Lead,          //its material
                      "lead7");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadinside,                    //at position
                    logiclead7,             //its logical volume
                    "lead7",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


G4ThreeVector posileadbottom = G4ThreeVector(0*cm,-25.0425*cm,347.675*mm);
// wall dimensions
// G4double iwall1ll_dxa = 5.08*cm, iwall1ll_dxb = 5.08*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz2  = 101.6*cm;

G4Trd* solidlead5 =
  new G4Trd("lead5",                      //its name
  15.24*cm, 15.24*cm,
  2.54*cm, 2.54*cm, 0.5*iwall1ll_dz+2.54*cm); //its size

G4LogicalVolume* logiclead5 =
  new G4LogicalVolume(solidlead5,         //its solid
                      Lead,          //its material
                      "lead5");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadbottom,                    //at position
                    logiclead5,             //its logical volume
                    "lead5",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


G4ThreeVector posileadfrontb = G4ThreeVector(0*cm,-9.8205*cm,-71.425*mm);
// wall dimensions
// G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz2  = 101.6*cm;
G4Trd* solidfb =
  new G4Trd("fb",                      //its name
  0.5*iwall1l_dxa, 0.5*iwall1l_dxb,
  5.08*cm, 5.08*cm, 0.5*iwall1l_dz); //its size

G4LogicalVolume* logicfb =
  new G4LogicalVolume(solidfb,         //its solid
                      Lead,          //its material
                      "fb");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadfrontb,                    //at position
                    logicfb,             //its logical volume
                    "fb",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posisheettop = G4ThreeVector(0*cm,11.1175*cm,347.675*mm);
// wall dimensions
G4double iwall1ll_dxa2 = 1*cm, iwall1ll_dxb2 = 1*cm;
G4double iwall1ll_dz2  = 93.98*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz2  = 101.6*cm;
G4Trd* solidsheet =
  new G4Trd("sheet",                      //its name
  26.4*cm, 26.4*cm,
  0.6*iwall1ll_dxa2, 0.6*iwall1ll_dxb2, 0.5*iwall1ll_dz2); //its size

G4LogicalVolume* logicsheet =
  new G4LogicalVolume(solidsheet,         //its solid
                      Alum,          //its material
                      "sheet");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posisheettop,                    //at position
                    logicsheet,             //its logical volume
                    "sheet",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posileadtop = G4ThreeVector(0*cm,14.2575*cm,347.675*mm);

G4Trd* solidlead4 =
  new G4Trd("lead4",                      //its name
  25.4*cm, 25.4*cm,
  2.54*cm, 2.54*cm, 0.5*iwall1ll_dz2); //its size

G4LogicalVolume* logiclead4 =
  new G4LogicalVolume(solidlead4,         //its solid
                      Lead,          //its material
                      "lead4");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadtop,                    //at position
                    logiclead4,             //its logical volume
                    "lead4",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posileadfrontt = G4ThreeVector(0*cm,7.9595*cm,-71.425*mm);
// wall dimensions
// G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz2  = 101.6*cm;
G4Trd* solidft =
  new G4Trd("ft",                      //its name
  0.5*iwall1l_dxa, 0.5*iwall1l_dxb,
  2.54*cm, 2.54*cm, 0.5*iwall1l_dz); //its size

G4LogicalVolume* logicft =
  new G4LogicalVolume(solidft,         //its solid
                      Lead,          //its material
                      "ft");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadfrontt,                    //at position
                    logicft,             //its logical volume
                    "ft",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector posileadfrontl = G4ThreeVector(-15.24*cm,0.3395*cm,-71.425*mm);
// wall dimensions
// G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz2  = 101.6*cm;
G4Trd* solidfl =
  new G4Trd("fl",                      //its name
  10.16*cm, 10.16*cm,
  5.08*cm, 5.08*cm, 0.5*iwall1l_dz); //its size

G4LogicalVolume* logicfl =
  new G4LogicalVolume(solidfl,         //its solid
                      Lead,          //its material
                      "fl");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadfrontl,                    //at position
                    logicfl,             //its logical volume
                    "fl",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);

G4ThreeVector posileadfrontr = G4ThreeVector(15.24*cm,0.3395*cm,-71.425*mm);
// wall dimensions
// G4double iwall1ll_dxa2 = 1.27*cm, iwall1ll_dxb2 = 1.27*cm;
// G4double iwall1ll_dya = 25.4*cm, iwall1ll_dyb = 25.4*cm;
// G4double iwall1ll_dz2  = 101.6*cm;
G4Trd* solidfr =
  new G4Trd("fr",                      //its name
  10.16*cm, 10.16*cm,
  5.08*cm, 5.08*cm, 0.5*iwall1l_dz); //its size

G4LogicalVolume* logicfr =
  new G4LogicalVolume(solidfr,         //its solid
                      Lead,          //its material
                      "fr");           //its name

  new G4PVPlacement(0,                       //no rotation
                    posileadfrontr,                    //at position
                    logicfr,             //its logical volume
                    "fr",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

G4ThreeVector positable = G4ThreeVector(0*cm,-17.5225*cm,347.675*mm);

G4Trd* solidtable =
  new G4Trd("table",                      //its name
  27.4*cm, 27.4*cm,
  2.54*cm, 2.54*cm, 0.53*iwall1ll_dz2); //its size

G4LogicalVolume* logictable =
  new G4LogicalVolume(solidtable,         //its solid
                      Alum,          //its material
                      "table");           //its name

  new G4PVPlacement(0,                       //no rotation
                    positable,                    //at position
                    logictable,             //its logical volume
                    "table",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

/////////////////////////////////////////////////////////////////////////////////////////////////

//
G4VisAttributes* BGOVisAttributes =
  new G4VisAttributes(G4Colour(1,0,1));
G4VisAttributes* CoreVisAttributes =
  new G4VisAttributes(G4Colour(1,0,0));
G4VisAttributes* radVisAttributes =
  new G4VisAttributes(G4Colour(1,1,0));
G4VisAttributes* magVisAttributes =
  new G4VisAttributes(G4Colour(0,1,1));
G4VisAttributes* Blue =
  new G4VisAttributes(G4Colour(0,0,1));
G4VisAttributes* Lgreen =
  new G4VisAttributes(G4Colour(.2,.8,.2));
// G4VisAttributes* Norange =
//   new G4VisAttributes(G4Colour(1,.31,.21));

logicBGO->SetVisAttributes(BGOVisAttributes);
logiccore->SetVisAttributes(Lgreen);
logicside->SetVisAttributes(Lgreen);
logicside1->SetVisAttributes(Lgreen);
logiccap->SetVisAttributes(Lgreen);
logiccap1->SetVisAttributes(Lgreen);
logictest3->SetVisAttributes(radVisAttributes);
logictest2->SetVisAttributes(radVisAttributes);
logictest->SetVisAttributes(radVisAttributes);
logicregion->SetVisAttributes(magVisAttributes);
logichole->SetVisAttributes(CoreVisAttributes);
logicwall3->SetVisAttributes(Lgreen);
logiclead1->SetVisAttributes(Blue);
logiclead2->SetVisAttributes(Blue);
logiclead3->SetVisAttributes(Blue);
logiclead4->SetVisAttributes(Blue); // comment out for open
logiclead5->SetVisAttributes(Blue);
logiclead7->SetVisAttributes(Blue);
logiclead8->SetVisAttributes(Blue); //
logiclead9->SetVisAttributes(Blue); //
logicfb->SetVisAttributes(Blue);
logicfl->SetVisAttributes(Blue); //
logicft->SetVisAttributes(Blue); //
logicfr->SetVisAttributes(Blue); //
logicsheet->SetVisAttributes(Lgreen); //
logictable->SetVisAttributes(Lgreen);
logiccol->SetVisAttributes(CoreVisAttributes);
logiccol2->SetVisAttributes(CoreVisAttributes);
logicabs11->SetVisAttributes(CoreVisAttributes);
logicabs2->SetVisAttributes(CoreVisAttributes);
logicabs3->SetVisAttributes(CoreVisAttributes);
logiciwall1->SetVisAttributes(radVisAttributes);
logicowall1->SetVisAttributes(radVisAttributes);
logicowall12->SetVisAttributes(radVisAttributes);
logicowall222->SetVisAttributes(radVisAttributes);
logicowall2222->SetVisAttributes(radVisAttributes);
logicowall22->SetVisAttributes(radVisAttributes);
logicowall2->SetVisAttributes(radVisAttributes);
logicowall32->SetVisAttributes(radVisAttributes);
logicowall3->SetVisAttributes(radVisAttributes);
logicowall4->SetVisAttributes(radVisAttributes);
logicowall5->SetVisAttributes(radVisAttributes);
logicowall6->SetVisAttributes(radVisAttributes);

  return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
  //4-.35
  // G4double zOffset = -3.65*cm;
  G4double zOffset = -20.9775*cm;
  G4MagneticField* magField = new TabulatedField3D("steel1010.table", zOffset);
  // // magField->GetFieldValue();
  //
  // G4MagneticField* magField = new G4UniformMagField(G4ThreeVector(0.*tesla,0,1*tesla));
  auto localpFieldManager = new G4FieldManager(magField);
  logicregion->SetFieldManager(localpFieldManager,true);
}
