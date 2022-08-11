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

  private:
    G4LogicalVolume *logiccore;
    G4LogicalVolume *logicBGO;
    G4LogicalVolume *logicwall;
    G4LogicalVolume *logicwall1;
    G4LogicalVolume *logicwall2;
    G4LogicalVolume *logicregion;
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

#endif
