/// ENLegnSimEventAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
/// Copyright: 2017 (C) Projet BADGE - CARMELEC -P2R

#include "G4SteppingManager.hh"
#include "ENLegnSimSteppingAction.hh"
#include "G4Run.hh"
#include "ENLegnSimEventAction.hh"
#include "G4RunManager.hh"
#include "ENLegnSimRunAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include "G4PrimaryVertex.hh"
#include <math.h>
#include "TRandom3.h"
#include "TGraph.h"

using namespace CLHEP;

ENLegnSimEventAction::ENLegnSimEventAction(char* suff):suffixe(suff){}

ENLegnSimEventAction::~ENLegnSimEventAction(){}


// Initialize all counters and set up the event branches for
// filling histograms with ROOT
void ENLegnSimEventAction::BeginOfEventAction(const G4Event* evt){

  G4int event_id = evt->GetEventID();

  //G4cout << "EVENT : " << event_id << G4endl;

  Statistics.EPart.clear();
  Statistics.EdepPart.clear();
  Statistics.LPart.clear();
  Statistics.ProcessPart=0;
  //Statistics.NamePart="Unknown";
  Statistics.Volume.clear();
  Statistics.z.clear();
}


// Get the number of stored trajectories and calculate the statistics
void ENLegnSimEventAction::EndOfEventAction(const G4Event* evt){
  G4int event_id = evt->GetEventID();

  ENLegnSimRunAction *runac = (ENLegnSimRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());

  if (Statistics.NamePart == "gamma")
  {
    if (Statistics.ProcessPart != 0)
    {runac->UpdateStatistics(Statistics);}
  }

  if (Statistics.NamePart != "gamma")
  {
    runac->UpdateStatistics(Statistics);
  }

}
