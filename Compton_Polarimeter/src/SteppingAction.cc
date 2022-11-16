#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

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
  // G4StepPoint* prePoint = aStep->GetPreStepPoint();
  G4double Edep = aStep->GetTotalEnergyDeposit();
  G4double kineticEnergy = postPoint->GetKineticEnergy();
  G4String ParticleName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4StepPoint* prePoint = aStep->GetPreStepPoint();
  G4double charge = prePoint->GetCharge();
  // G4bool front = aStep->IsFirstStepInVolume();
  G4double trackerEdep = aStep->GetTotalEnergyDeposit();
  // G4int a = 0;
  // G4bool test = false;
  //.........................................................................
  G4double x = aStep->GetPostStepPoint()->GetPosition().x();
  G4double y = aStep->GetPostStepPoint()->GetPosition().y();
  // G4double z = aStep->GetPostStepPoint()->GetPosition().z();
  // G4double frontwall = 318.275*mm;
  G4ThreeVector momemtum = aStep->GetPostStepPoint()->GetMomentum();
  G4double pz = momemtum.z();
  // G4double px = momemtum.x();
  // G4double py = momemtum.y();

/// this is broken ///
if (volume == fDetConstruction->GetBGO())
{
     if(aStep->IsFirstStepInVolume() && aStep->GetTrack()->GetParentID()==1)
     // if(aStep->IsFirstStepInVolume())
     {
         G4cout << "step number = " << aStep->GetTrack()->GetCurrentStepNumber() << " location = " << aStep->GetPreStepPoint()->GetPosition().z() << " edep = " << aStep->GetTotalEnergyDeposit() << " parent id " << aStep->GetTrack()->GetParentID() << G4endl;
     }

     if (aStep->GetPreStepPoint()->GetPosition().z() == 318.275*mm )
     {
       fEventAction->AddEdepCorefront(trackerEdep);
     }
}

////////////////////////////

  // if ( volume == fDetConstruction->GetW0() )
  //  {
  //    analysisManager->FillH1(1,kineticEnergy);
  //    if (ParticleName=="gamma")
  //     {
  //       analysisManager->FillH2(1,x,y);
  //       analysisManager->FillH1(6,y);
  //       analysisManager->FillH1(7,y);
  //     }
  //    if (ParticleName=="e+")
  //     {
  //       analysisManager->FillH1(8,kineticEnergy);
  //     }
  //...........................................................................
  //
  
  if ( volume == fDetConstruction->GetW3())
    {
     if (ParticleName=="e-" && pz > 0)
      {
        analysisManager->FillH2(2,x,y);
      }
    }

  if ( volume == fDetConstruction->GetW0() )
   {
     analysisManager->FillH1(1,kineticEnergy);
     if (ParticleName=="gamma")
      {
        analysisManager->FillH1(6,kineticEnergy);
        analysisManager->FillH2(1,x,y);
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

  if ( volume == fDetConstruction->GetBGO())
  {
    fEventAction->AddEdepBGO(Edep);
    // G4cout << "astep number = " << aStep->GetTrack()->GetCurrentStepNumber() << " location = " << aStep->GetPreStepPoint()->GetPosition().z() << " edep = " << aStep->GetTotalEnergyDeposit() << G4endl;
    // fEventAction->AddEdepCorefront(trackerEdep);
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

       // if (pz <= 0.)
       // {
       // aStep->GetTrack()->SetTrackStatus(fStopAndKill);
       // }
// if (ParticleName=="gamma")
// {
//        if (abs(py) <= pz/8)
//        {
//        aStep->GetTrack()->SetTrackStatus(fStopAndKill);
//        }
//        if (abs(px) <= pz/8)
//        {
//        aStep->GetTrack()->SetTrackStatus(fStopAndKill);
//        }
// }

    // if ( volume == fDetConstruction->GetRadCore() )
    //  {
    //    if (pz <= 0.)
    //    {
    //    aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    //    }
    //  }
    //
    //  if ( volume == fDetConstruction->GetRadShell() )
    //   {
    //     aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    //   }

}
