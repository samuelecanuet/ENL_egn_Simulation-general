/// ENLegnSimSteppingAction.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLegnSimSteppingAction.hh"
#include "G4DynamicParticle.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ProcessManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4OpticalPhoton.hh"
#include "ENLegnSimRunAction.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "ENLegnSimEventAction.hh"
#include <iostream>
#include <fstream>
#include "G4Material.hh"
#include "G4Trajectory.hh"
#include "ENLegnSimGeometry.hh"
#include "G4StepPoint.hh"
#include "TRandom3.h"
#include "TF1.h"


using namespace CLHEP;

const G4String ENLegnSimSteppingAction::path = "../simulation_input_files/";

ENLegnSimSteppingAction::ENLegnSimSteppingAction()
{}

  ENLegnSimSteppingAction::~ENLegnSimSteppingAction(){}
  void ENLegnSimSteppingAction::UserSteppingAction(const G4Step *aStep){


    //###################################
    // Déclaration of functions/variables
    //###################################
    G4EventManager *evtman = G4EventManager::GetEventManager();
    ENLegnSimEventAction *evtac = (ENLegnSimEventAction*)evtman->GetUserEventAction();
    G4int Parent_ID = aStep->GetTrack()->GetParentID();
    G4float kineticenergy = aStep->GetPreStepPoint()->GetKineticEnergy();
    G4float depositenergy = aStep->GetTotalEnergyDeposit();
    G4float length = aStep->GetStepLength();
    G4String ProcessName = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4String PreVolume = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    //#######################################################################
    //#######################################################################
    //###########################START EM INFOS PART#########################
    //#######################################################################
    //#######################################################################

    if (Parent_ID==0)
    {
      evtac->FillEPart(kineticenergy/MeV);
      //G4cout<<"EPart="<<aStep->GetPreStepPoint()->GetKineticEnergy()/MeV<<G4endl;
      evtac->FillEdepPart(depositenergy/MeV);
      //G4cout<<"EdepPart="<<aStep->GetTotalEnergyDeposit()/MeV<<G4endl;
      evtac->FillLPart(length/cm);
      //G4cout<<"Length="<<aStep->GetStepLength()/cm<<G4endl;
      evtac->FillProcessPart(ProcessName);
      //G4cout<<"Process="<<ProcessName<<G4endl;
    }
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);



  }
