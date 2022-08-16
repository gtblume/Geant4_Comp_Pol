#include "G4Version.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4Material.hh"
#include "G4ios.hh"
#include "G4EmLowEPPhysics.hh"

#include "G4EnergyLossTables.hh"

#include "PhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList()
: G4VUserPhysicsList()
{
  defaultCutValue = 1.0*mm;
  // SetVerboseLevel(1);
}

PhysicsList::~PhysicsList()
{}

void PhysicsList::ConstructParticle()
{
  ConstructBosons();
  ConstructLeptons();
  G4GenericIon::GenericIonDefinition();
}

void PhysicsList::ConstructBosons()
{
  G4Gamma::GammaDefinition();
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void PhysicsList::ConstructLeptons()
{
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
}

void PhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructGeneral();
}

#include "G4PhysicsListHelper.hh"

#include "G4ComptonScattering.hh"
#include "G4PolarizedGammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4PolarizedPhotoElectric.hh"
#include "G4PolarizedCompton.hh"

#include "G4eMultipleScattering.hh"

#include "G4PolarizedIonisation.hh"
#include "G4PolarizedBremsstrahlung.hh"
#include "G4PolarizedAnnihilation.hh"
// #include "G4LowECapture.hh"

void PhysicsList::ConstructEM()
{
  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {

      pmanager->AddDiscreteProcess(new G4PolarizedPhotoElectric);
      pmanager->AddDiscreteProcess(new G4PolarizedCompton);
      pmanager->AddDiscreteProcess(new G4PolarizedGammaConversion);
      // pmanager->AddDiscreteProcess(new G4LowECapture);

      } else if (particleName == "e-") {

      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4PolarizedIonisation, -1,2,2);
      pmanager->AddProcess(new G4PolarizedBremsstrahlung,      -1,3,3);

    } else if (particleName == "e+") {

      pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4PolarizedIonisation, -1, 2, 2);
      pmanager->AddProcess(new G4PolarizedBremsstrahlung,    -1, 3, 3);
      pmanager->AddProcess(new G4PolarizedAnnihilation,   0,-1, 4);
      }
  }
}

// Optical Processes
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"

// void PhysicsList::ConstructOp() {
//
//
// }

#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"
#include "G4IonTable.hh"
#include "G4Ions.hh"

void PhysicsList::ConstructGeneral()
{

}

void PhysicsList::SetCuts()
{
  if (verboseLevel >0){
    G4cout << "PhysicsList::SetCuts:";
    G4cout << "CutLength : " << defaultCutValue/mm << " (mm)" << G4endl;
  }

  SetCutsWithDefault();

  if (verboseLevel>0) DumpCutValuesTable();
}
