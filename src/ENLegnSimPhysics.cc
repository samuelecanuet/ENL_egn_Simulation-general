/// ENLegnSimPhysics.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLegnSimPhysics.hh"
//#include "G4MuNuclearInteraction.hh"
#include "G4KokoulinMuonNuclearXS.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ShortLivedConstructor.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ios.hh"
#include "G4OpWLS.hh"
#include "G4GenericIon.hh"
#include "G4Decay.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4ParticleDefinition.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"
//#include "NeutronHPphysics.hh"
// Processes

#include "G4HadronElasticProcess.hh"
#include "G4ParticleHPElasticData.hh"
#include "G4ParticleHPThermalScatteringData.hh"
#include "G4ParticleHPElastic.hh"
#include "G4ParticleHPThermalScattering.hh"

#include "G4HadronInelasticProcess.hh"
#include "G4ParticleHPInelasticData.hh"
#include "G4ParticleHPInelastic.hh"

#include "G4NeutronCaptureProcess.hh"
#include "G4ParticleHPCaptureData.hh"
#include "G4ParticleHPCapture.hh"

#include "G4NeutronFissionProcess.hh"
#include "G4ParticleHPFissionData.hh"
#include "G4ParticleHPFission.hh"
#include "G4EmExtraPhysics.hh"
#include "G4HadronInelasticProcess.hh"
#include "G4LENDorBERTModel.hh"
#include "G4LENDCombinedCrossSection.hh"
#include "G4PhotoNuclearCrossSection.hh"
#include "G4LowEGammaNuclearModel.hh"
#include "G4CascadeInterface.hh"
#include "G4LENDorBERTModel.hh"
#include "G4LENDCombinedCrossSection.hh"

#include "G4eIonisation.hh"

using namespace CLHEP;

ENLegnSimPhysics::ENLegnSimPhysics():  G4VModularPhysicsList(), fThermal(true)
{

  defaultCutValue =10*um;
  SetVerboseLevel(1);

  //default physics
  particleList = new G4DecayPhysics();

  // EM physics
  emPhysicsList = new G4EmStandardPhysics_option4();

}

ENLegnSimPhysics::~ENLegnSimPhysics()
{
  delete emPhysicsList;
}

void ENLegnSimPhysics::ConstructParticle()
{
  particleList->ConstructParticle();
}

void ENLegnSimPhysics::ConstructProcess()
{
  // Transportation, electromagnetic and general processes
  AddTransportation();
  emPhysicsList->ConstructProcess();
  particleList->ConstructProcess();

}
