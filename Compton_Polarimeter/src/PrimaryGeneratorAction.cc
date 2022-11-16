#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(5*MeV);
  fParticleGun->SetParticlePolarization(G4ThreeVector(0,0,-1));

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

// this can be adjusted to be whatever distribution wanted
  G4double envSizeXY =20*cm;

  G4double x0 = 0.04 * envSizeXY * (G4UniformRand()-0.5);
  G4double y0 = 0.04 * envSizeXY * (G4UniformRand()-0.5);

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,-80*cm));

  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
