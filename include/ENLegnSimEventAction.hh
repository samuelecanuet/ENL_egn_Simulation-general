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

  std::vector<float> EPart;
  std::vector<float> EdepPart;
  std::vector<float> LPart;
  std::vector<std::string> ProcessPart;

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
  void FillEPart(G4float e){Statistics.EPart.push_back(e);}
  void FillEdepPart(G4float e){Statistics.EdepPart.push_back(e);}
  void FillLPart(G4float e){Statistics.LPart.push_back(e);}
  void FillProcessPart(G4String e){Statistics.ProcessPart.push_back(e);}

private:

  TTree *EventTree;
  TBranch *EventBranch;
  RunTally Statistics;

  G4String suffixe;





};


#endif
