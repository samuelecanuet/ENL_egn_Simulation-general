/// ENLegnSimEventAction.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLegnSimEventAction_h
#define ENLegnSimEventAction_h 1
#include "G4ParticleGun.hh"
#include "G4UserEventAction.hh"
#include "TH1F.h"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFile.h"
#include "TCanvas.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include <vector>
#include "TVector.h"

class G4Event;


//This struct carries statistics for the whole Run
struct RunTally {

  std::vector<float> EProton;
  std::vector<float> EdepProton;
  std::vector<float> LProton;

  inline int operator ==(const RunTally& right) const
  {return (this==&right);}
};



class ENLegnSimEventAction : public G4UserEventAction
{
public:
  ENLegnSimEventAction(char*);
  ~ENLegnSimEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void FillEProton(G4float e){Statistics.EProton.push_back(e);}
  void FillEdepProton(G4float e){Statistics.EdepProton.push_back(e);}
  void FillLProton(G4float e){Statistics.LProton.push_back(e);}

private:

  TTree *EventTree;
  TBranch *EventBranch;
  RunTally Statistics;

  G4String suffixe;





};


#endif
