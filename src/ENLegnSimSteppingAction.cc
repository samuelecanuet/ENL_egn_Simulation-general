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
    G4String processname = aStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4String volume = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    G4String partname = aStep->GetTrack()->GetDefinition()->GetParticleName();

    //#######################################################################
    //#######################################################################
    //###########################START EM INFOS PART#########################
    //#######################################################################
    //#######################################################################

    if (Parent_ID == 0 && depositenergy != 0)
    {
      evtac->FillEPart(kineticenergy/keV);
      //G4cout<<"EPart="<<kineticenergy/MeV<<G4endl;
      evtac->FillEdepPart(depositenergy/keV);
      //G4cout<<"EdepPart="<<depositenergy/MeV<<G4endl;
      evtac->FillLPart(length/cm);
      //G4cout<<"Length="<<length/cm<<G4endl;
      evtac->SetName(partname);
      //G4cout<<"Particle Name : "<<partname<<G4endl;
      evtac->FillNameVolume(volume);
      //G4cout<<"Volume : "<<volume<<G4endl;
      if (partname == "gamma")
      {
        if (processname == "conv"){evtac->SetProcess(1);}
        if (processname == "phot"){evtac->SetProcess(2);}
        if (processname == "compt"){evtac->SetProcess(3);}
        if (processname == "Rayl"){evtac->SetProcess(4);}
        aStep->GetTrack()->SetTrackStatus(fStopAndKill);

      }

    }



  }
