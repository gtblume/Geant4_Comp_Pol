#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4LogicalVolume;

class EventAction;
class DetectorConstruction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(const DetectorConstruction* detectorConstruction, EventAction* eventAction);
    virtual ~SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step* aStep);
    // void SetFirstStepFlag(const G4Step* aStep);
    // void UserEventID(const G4Event*);

  private:
    const DetectorConstruction* fDetConstruction;
    EventAction* fEventAction;
};

#endif
