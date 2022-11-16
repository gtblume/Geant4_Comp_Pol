#include "EventAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction()
:G4UserEventAction(),
 fTotalEnergyDepositBGO(0.),
 fTotalEnergyDepositCORE(0.),
 fTotalEnergyDepositBGOPhoton(0.),
 fTotalEnergyDepositCOREPhoton(0.),
 fTotalEnergyDepositBGOEMIN(0.),
 fTotalEnergyDepositCOREEMIN(0.),
 fTotalEnergyDepositBGOEPLUS(0.),
 fTotalEnergyDepositCOREEPLUS(0.),
 fTotalEnergyDepositBGOfront(0.),
 fKin(0.)
{ }

EventAction::~EventAction()
{ }

// G4EventManager::GetEventManager(const G4Event* eve)
// {->KeepTheCurrentEvent();

// void EventAction::BeginOfEventAction( const G4Event*, const G4Step* aStep)
void EventAction::BeginOfEventAction( const G4Event*)
{
 //initializations
 fTotalEnergyDepositBGO = 0.;
 fTotalEnergyDepositCORE = 0.;
 fTotalEnergyDepositBGOPhoton = 0.;
 fTotalEnergyDepositCOREPhoton = 0.;
 fTotalEnergyDepositBGOEMIN = 0.;
 fTotalEnergyDepositCOREEMIN = 0.;
 fTotalEnergyDepositBGOEPLUS = 0.;
 fTotalEnergyDepositCOREEPLUS = 0.;
 fTotalEnergyDepositBGOfront = 0.;
 fKin = 0.;
}

// void EventAction::EndOfEventAction( const G4Event*, const G4Step* aStep)
void EventAction::EndOfEventAction( const G4Event*)
{
  // G4String ParticleName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // if (fKin != 0.) analysisManager->FillH1(1, fKin/MeV);
  if (fTotalEnergyDepositBGO != 0.) analysisManager->FillH1(2, fTotalEnergyDepositBGO/MeV);
  if (fTotalEnergyDepositBGOPhoton != 0.) analysisManager->FillH1(9, fTotalEnergyDepositBGOPhoton/MeV);
  if (fTotalEnergyDepositBGOEMIN != 0.) analysisManager->FillH1(10, fTotalEnergyDepositBGOEMIN/MeV);
  if (fTotalEnergyDepositBGOEPLUS != 0.) analysisManager->FillH1(11, fTotalEnergyDepositBGOEPLUS/MeV);
  // if (fKin != 0.) analysisManager->FillH1(3, fKin/MeV);
  if (fTotalEnergyDepositCORE != 0.) analysisManager->FillH1(4, fTotalEnergyDepositCORE/MeV);
  if (fTotalEnergyDepositCOREPhoton != 0.) analysisManager->FillH1(15, fTotalEnergyDepositCOREPhoton/MeV);
  if (fTotalEnergyDepositCOREEMIN != 0.) analysisManager->FillH1(16, fTotalEnergyDepositCOREEMIN/MeV);
  if (fTotalEnergyDepositCOREEPLUS != 0.) analysisManager->FillH1(17, fTotalEnergyDepositCOREEPLUS/MeV);
  if (fTotalEnergyDepositBGOfront != 0.) analysisManager->FillH1(21, fTotalEnergyDepositBGOfront/MeV);
  // if (fKin != 0.) analysisManager->FillH1(5, fKin/MeV);
}
