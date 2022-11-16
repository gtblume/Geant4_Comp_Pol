#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"
#include "G4MagneticField.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    G4VPhysicalVolume* Construct();

    const G4LogicalVolume* GetBGO() const;
    const G4LogicalVolume* GetCORE() const;
    const G4LogicalVolume* GetW0() const;
    const G4LogicalVolume* GetW1() const;
    const G4LogicalVolume* GetW2() const;
    const G4LogicalVolume* GetW3() const;
    const G4LogicalVolume* GetFrontBlock() const;
    const G4LogicalVolume* GetSideBlock() const;
    const G4LogicalVolume* GetBackBlock() const;
    // const G4double* frontentry() const;
    // const G4LogicalVolume* GetRadCore() const;
    // const G4LogicalVolume* GetRadShell() const;

  private:
    G4LogicalVolume *logiccore;
    G4LogicalVolume *logicside;
    G4LogicalVolume *logicside1;
    G4LogicalVolume *logiccap;
    G4LogicalVolume *logiccap1;
    G4LogicalVolume *logiccoil1;
    G4LogicalVolume *logiccoil;
    G4LogicalVolume *logiccorecoil;
    G4LogicalVolume *logictest4;
    G4LogicalVolume *logictest5;
    G4LogicalVolume *logicBGO;
    G4LogicalVolume *logicBGOf;
    G4LogicalVolume *logicBGOb;
    G4LogicalVolume *logicBGOs;
    G4LogicalVolume *logicwall;
    G4LogicalVolume *logicwall1;
    G4LogicalVolume *logicwall2;
    G4LogicalVolume *logicwall3;
    G4LogicalVolume *logicregion;
    // G4double* frontentry;
    // G4Cache<G4MagneticField*> fField;
    virtual void ConstructSDandField();
};

inline const G4LogicalVolume* DetectorConstruction::GetCORE() const {
  return logiccore;
}

inline const G4LogicalVolume* DetectorConstruction::GetBGO() const {
  return logicBGO;
}

inline const G4LogicalVolume* DetectorConstruction::GetW0() const {
  return logicwall;
}

inline const G4LogicalVolume* DetectorConstruction::GetW1() const {
  return logicwall1;
}

inline const G4LogicalVolume* DetectorConstruction::GetW2() const {
  return logicwall2;
}

inline const G4LogicalVolume* DetectorConstruction::GetW3() const {
  return logicwall3;
}

inline const G4LogicalVolume* DetectorConstruction::GetFrontBlock() const {
  return logicBGOf;
}

inline const G4LogicalVolume* DetectorConstruction::GetSideBlock() const {
  return logicBGOs;
}

inline const G4LogicalVolume* DetectorConstruction::GetBackBlock() const {
  return logicBGOb;
}

// inline void G4double* DetectorConstruction::frontentry() const {
//   return frontentry;
// }

// inline const G4LogicalVolume* DetectorConstruction::GetRadCore() const {
//   return logictest4;
// }
//
// inline const G4LogicalVolume* DetectorConstruction::GetRadShell() const {
//   return logictest5;
// }

#endif
