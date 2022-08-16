#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

RunAction::RunAction()
 : G4UserRunAction()
{
  // G4int runID = run->GetRunID();
  //
  // std::stringstream strRunID;
  // strRunID << runID;
  // G4String fileName = "edep"+strRunID.str();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
  // analysisManager->SetFileName(fileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);     // start histogram numbering from 1
  analysisManager->SetActivation(true);    // enable inactivation of histograms

  // Define histograms
// analysisManager->CreateH1("Prior to Core", "Kinetic Energy Prior to Core;Kinetic Energy;Particles", 1000, 0, 5.1); //1
// analysisManager->CreateH1("In Core", "Energy Deposited in Core", 1000, 0, 5.1); //2
// analysisManager->CreateH1("Prior to Crystal", "Kinetic Energy Prior to Crystal", 1000, 0, 5.1); //3
// // analysisManager->CreateH1("In Crystal", "Energy Deposited in BGO", 1000, 0, 5.1); //4
// analysisManager->CreateH1("After Crystal", "Kinetic Energy Remaining", 1000, 0, 5.1); //5
// analysisManager->CreateH1("First Wall X", "X Position Strikes in first Wall", 500, -80, 80); //6
// analysisManager->CreateH1("First Wall Y", "Y Position Strikes in first Wall", 500, -80, 80); //7
// // analysisManager->CreateH1("Core Z", "Location of Strikes (Z) in Core with respect to World", 500, -78, 12); //8
// analysisManager->CreateH1("Second Wall X", "X Position Strikes in second Wall", 500, -80, 80); //9
// analysisManager->CreateH1("Second Wall Y", "Y Position Strikes in second Wall", 500, -80, 80); //10
// analysisManager->CreateH1("Crystal Z", "Location of Strikes (Z) in Core with respect to World", 500, 66, 214); //11
// analysisManager->CreateH1("Third Wall X", "X Position Strikes in third Wall", 500, -80, 80); //12
// analysisManager->CreateH1("Third Wall Y", "Y Position Strikes in third Wall", 500, -80, 80); //13
// analysisManager->CreateH1("First Wall Momentum X", "X Momentum in first Wall", 1000, -5.1, 5.1); //14
// analysisManager->CreateH1("First Wall Momentum Y", "Y Momentum in first Wall", 1000, -5.1, 5.1); //15
// analysisManager->CreateH1("First Wall Momentum Z", "Z Momentum in first Wall", 1000, -5.1, 5.1); //16
// analysisManager->CreateH1("Second Wall Momentum X", "X Momentum in second Wall", 1000, -5.1, 5.1); //17
// analysisManager->CreateH1("Second Wall Momentum Y", "Y Momentum in second Wall", 1000, -5.1, 5.1); //18
// analysisManager->CreateH1("Second Wall Momentum Z", "Z Momentum in second Wall", 1000, -5.1, 5.1); //19
// analysisManager->CreateH1("Third Wall Momentum X", "X Momentum in third Wall", 1000, -5.1, 5.1); //20
// analysisManager->CreateH1("Third Wall Momentum Y", "Y Momentum in third Wall", 1000, -5.1, 5.1); //21
// analysisManager->CreateH1("Third Wall Momentum Z", "Z Momentum in third Wall", 1000, -5.1, 5.1); //22
// // analysisManager->CreateH1("Polarization in Core", "Z Polarization in Core", 1000, -1.05, 1.05); //23
// // analysisManager->CreateH1("Polarization in Crystal", "Z Polarization in Crystal", 1000, -1.05, 1.05); //24

analysisManager->CreateH1("Prior to Core", "Kinetic Energy Prior to Core", 1000, 0, 5.1); //1
analysisManager->CreateH1("In BGO", "Energy Deposited in BGO", 51, 0, 5.1); //2
analysisManager->CreateH1("Prior to Crystal", "Kinetic Energy Prior to Crystal", 1000, 0, 5.1); //3
analysisManager->CreateH1("In Core", "Energy Deposited in Core", 51, 0, 5.1); //2
analysisManager->CreateH1("After Crystal", "Kinetic Energy Remaining", 1000, 0, 5.1); //4
analysisManager->CreateH1("Prior to Core (P)", "Kinetic Energy Prior to Core Photon Only", 3000, 0, 5.1); //1
analysisManager->CreateH1("Prior to Core (e-)", "Kinetic Energy Prior to Core Electron Only", 1000, 0, 5.1); //2
analysisManager->CreateH1("Prior to Core (e+)", "Kinetic Energy Prior to Core Positron Only", 1000, 0, 5.1); //3
analysisManager->CreateH1("In BGO (P)", "Energy Deposited in BGO Photon Only", 51, 0, 5.1); //2
analysisManager->CreateH1("In BGO (e-)", "Energy Deposited in BGO Electron Only", 51, 0, 5.1); //4
analysisManager->CreateH1("In BGO (e+)", "Energy Deposited in BGO Position Only", 51, 0, 5.1); //1
analysisManager->CreateH1("Prior to Crystal (P)", "Kinetic Energy Prior to Crystal Photon Only", 3000, 0, 5.1); //2
analysisManager->CreateH1("Prior to Crystal (e-)", "Kinetic Energy Prior to Crystal Electron Only", 1000, 0, 5.1); //3
analysisManager->CreateH1("Prior to Crystal (e+)", "Kinetic Energy Prior to Crystal Position Only", 1000, 0, 5.1); //2
analysisManager->CreateH1("In Core (P)", "Energy Deposited in Core Photon Only", 51, 0, 5.1); //4
analysisManager->CreateH1("In Core (e-)", "Energy Deposited in Core Electron Only", 51, 0, 5.1); //1
analysisManager->CreateH1("In Core (e+)", "Energy Deposited in Core Positron Only", 51, 0, 5.1); //2
analysisManager->CreateH1("After Crystal (P)", "Kinetic Energy Remaining Photon Only", 3000, 0, 5.1); //3
analysisManager->CreateH1("After Crystal (e-)", "Kinetic Energy Remaining Electron Only", 1000, 0, 5.1); //2
analysisManager->CreateH1("After Crystal (e+)", "Kinetic Energy Remaining Positron Only", 1000, 0, 5.1); //4
}

RunAction::~RunAction()
{ }

void RunAction::BeginOfRunAction(const G4Run* run)
{
   // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  G4int runID = run->GetRunID();

  std::stringstream strRunID;
  strRunID << runID;
  // G4String fileName = "edep"+strRunID.str();
  analysisManager->OpenFile("edep"+strRunID.str());
}

void RunAction::EndOfRunAction(const G4Run*)
{
  // show Rndm status
  // if (isMaster) G4Random::showEngineStatus();

  //save histograms
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
