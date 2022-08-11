#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4AnalysisManager.hh"

SteppingAction::SteppingAction(const DetectorConstruction* detectorConstruction, EventAction* eventAction)
: G4UserSteppingAction(),
  fDetConstruction(detectorConstruction),
  fEventAction(eventAction)
{ }

SteppingAction::~SteppingAction()
{ }

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  auto analysisManager = G4AnalysisManager::Instance();
  G4LogicalVolume* volume
    = aStep->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
  G4StepPoint* postPoint = aStep->GetPostStepPoint();
  G4double Edep = aStep->GetTotalEnergyDeposit();
  G4double kineticEnergy = postPoint->GetKineticEnergy();
  G4String ParticleName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4StepPoint* prePoint = aStep->GetPreStepPoint();
  G4double charge = prePoint->GetCharge();

  if ( volume == fDetConstruction->GetW0() )
   {
     analysisManager->FillH1(1,kineticEnergy);
     if (ParticleName=="gamma")
      {
        analysisManager->FillH1(6,kineticEnergy);
      }
     if (ParticleName=="e-")
      {
        analysisManager->FillH1(7,kineticEnergy);
      }
     if (ParticleName=="e+")
      {
        analysisManager->FillH1(8,kineticEnergy);
      }

   }
  if ( volume == fDetConstruction->GetBGO() )
  {
    fEventAction->AddEdepBGO(Edep);
    if (charge==0)
    {
    fEventAction->AddEdepBGOPhoton(Edep);
    }
    if (charge==-1)
    {
    fEventAction->AddEdepBGOEMIN(Edep);
    }
    if (charge==1)
    {
    fEventAction->AddEdepBGOEPLUS(Edep);
    }
         // if (Edep != 0.) analysisManager->FillH1(2,Edep);
    }

    if ( volume == fDetConstruction->GetW1() )
     {
       analysisManager->FillH1(3,kineticEnergy);
       if (ParticleName=="gamma")
        {
          analysisManager->FillH1(12,kineticEnergy);
        }
       if (ParticleName=="e-")
        {
          analysisManager->FillH1(13,kineticEnergy);
        }
       if (ParticleName=="e+")
        {
          analysisManager->FillH1(14,kineticEnergy);
        }
          // analysisManager->FillH1(3,kineticEnergy);
     }

  if ( volume == fDetConstruction->GetCORE() )
   {
     fEventAction->AddEdepCore(Edep);
     if (charge == 0)
     {
     fEventAction->AddEdepCorePhoton(Edep);
     }
     if (charge == -1)
     {
     fEventAction->AddEdepCoreEMIN(Edep);
     }
     if (charge == 1)
     {
     fEventAction->AddEdepCoreEPLUS(Edep);
     }
     // fEventAction->AddEdepCore(Edep);
        // if (Edep != 0.) analysisManager->FillH1(4,Edep);
   }
   if ( volume == fDetConstruction->GetW2() )
    {
      analysisManager->FillH1(5,kineticEnergy);
      if (ParticleName=="gamma")
       {
         analysisManager->FillH1(18,kineticEnergy);
       }
      if (ParticleName=="e-")
       {
         analysisManager->FillH1(19,kineticEnergy);
       }
      if (ParticleName=="e+")
       {
         analysisManager->FillH1(20,kineticEnergy);
       }
         // analysisManager->FillH1(5,kineticEnergy);

    }
}
