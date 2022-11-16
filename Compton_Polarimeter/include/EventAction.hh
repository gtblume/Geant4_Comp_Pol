#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4Step.hh"
// class SteppingAction;

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
   ~EventAction();

  public:
    // virtual void BeginOfEventAction(const G4Event*, const G4Step* aStep);
    // virtual void   EndOfEventAction(const G4Event*, const G4Step* aStep);
    virtual void BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);

    void AddEdepBGO(G4double Edep);
    void AddEdepCore(G4double Edep);
    void AddEdepBGOPhoton(G4double Edep);
    void AddEdepCorePhoton(G4double Edep);
    void AddEdepBGOEMIN(G4double Edep);
    void AddEdepCoreEMIN(G4double Edep);
    void AddEdepBGOEPLUS(G4double Edep);
    void AddEdepCoreEPLUS(G4double Edep);
    void AddEdepCorefront(G4double trackerEdep);
    void AddKin(G4double kineticEnergy);

  private:
    G4double fTotalEnergyDepositBGO;
    G4double fTotalEnergyDepositCORE;
    G4double fTotalEnergyDepositBGOPhoton;
    G4double fTotalEnergyDepositCOREPhoton;
    G4double fTotalEnergyDepositBGOEMIN;
    G4double fTotalEnergyDepositCOREEMIN;
    G4double fTotalEnergyDepositBGOEPLUS;
    G4double fTotalEnergyDepositCOREEPLUS;
    G4double fTotalEnergyDepositBGOfront;
    G4double fKin;

};

    inline void EventAction::AddEdepBGO(G4double Edep) {
      fTotalEnergyDepositBGO += Edep;}
    inline void EventAction::AddEdepCore(G4double Edep) {
      fTotalEnergyDepositCORE += Edep;}
    inline void EventAction::AddEdepBGOPhoton(G4double Edep) {
      fTotalEnergyDepositBGOPhoton += Edep;}
    inline void EventAction::AddEdepCorePhoton(G4double Edep) {
      fTotalEnergyDepositCOREPhoton += Edep;}
    inline void EventAction::AddEdepBGOEMIN(G4double Edep) {
      fTotalEnergyDepositBGOEMIN += Edep;}
    inline void EventAction::AddEdepCoreEMIN(G4double Edep) {
      fTotalEnergyDepositCOREEMIN += Edep;}
    inline void EventAction::AddEdepBGOEPLUS(G4double Edep) {
      fTotalEnergyDepositBGOEPLUS += Edep;}
    inline void EventAction::AddEdepCoreEPLUS(G4double Edep) {
      fTotalEnergyDepositCOREEPLUS += Edep;}
    inline void EventAction::AddEdepCorefront(G4double trackerEdep) {
      fTotalEnergyDepositBGOfront += trackerEdep;}
    inline void EventAction::AddKin(G4double kineticEnergy) {
      fKin += kineticEnergy;}

#endif
