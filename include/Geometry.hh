/// Geometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

// This class is used to create a Silicon Detector.

#ifndef Geometry_h
#define Geometry_h

#include "G4LogicalVolume.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class ENLOpticalSimMaterials;
class Geometry

{
public:

  //constructor, builds from keys specified in buildfile
  Geometry(G4String buildfile);
  ~Geometry();


public:

  G4LogicalVolume *GetStackIP();

  G4double GetPlaqueLength(){return PlaqueLength;}
  G4double GetPlaqueThickness(){return PlaqueThickness;}
  G4double GetsubPlaqueThickness(){return subPlaqueThickness;}
  G4double Getgap(){return gap;}
  G4int GetnbPlaque(){return nbPlaque;}

private:


  Geometry *Geom;
  ENLegnSimMaterials* detecProp;

  static const G4String path_bin;


  // Materials
  G4Material *Material;

  // Logical Volumes
  G4LogicalVolume *LogicalVolume;
  G4double PlaqueLength;
  G4double PlaqueThickness;
  G4double subPlaqueThickness;
  G4double gap;
  G4int nbPlaque;



  // Other
  G4VisAttributes *clear;

};
#endif
