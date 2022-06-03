/// ENLegnSimPhysics.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef  ENLegnSimPhysics_h
#define   ENLegnSimPhysics_h  1

#include "G4VUserPhysicsList.hh"
#include "G4VModularPhysicsList.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
class  ENLegnSimPhysics:  public G4VModularPhysicsList
{      public:
  ENLegnSimPhysics();
  virtual ~ENLegnSimPhysics();

protected:
  virtual void ConstructProcess();
  virtual void ConstructParticle();
  // virtual void SetCuts();

private:
  G4VPhysicsConstructor*  emPhysicsList;
  G4VPhysicsConstructor*  particleList;
  //G4VPhysicsConstructor*  raddecayList;
  G4bool              fThermal;
};
#endif
