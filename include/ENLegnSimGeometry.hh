/// ENLegnSimGeometry.hh
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#ifndef ENLegnSimGeometry_h
#define ENLegnSimGeometry_h  1

#include "G4MaterialPropertiesTable.hh"

class Geometry;
class ENLegnSimMaterials;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "Geometry.hh"


class  ENLegnSimGeometry:  public G4VUserDetectorConstruction
{
public:
  ENLegnSimGeometry();
  ~ENLegnSimGeometry();

public:
  G4VPhysicalVolume* Construct();
  G4LogicalVolume* GetLWorld() {return LogicalWorld;}

private:
  static const G4String path_bin;
  static const G4String path;
  // Classes for building various components
  //     LogicalHolder *holder;
  ENLegnSimMaterials *detecProp;
  Geometry *Geom;
  G4Material *Vacuum;
  G4Material *VacuumWorld;
  G4Material *Air;
  G4Material *Si;


  // Colors for visualizations
  G4VisAttributes *invis;
  G4VisAttributes *white;
  G4VisAttributes *gray;
  G4VisAttributes *gray_bis;
  G4VisAttributes *black;
  G4VisAttributes *black_bis;
  G4VisAttributes *red;
  G4VisAttributes *red_hot;
  G4VisAttributes *orange;
  G4VisAttributes *yellow;
  G4VisAttributes *green;
  G4VisAttributes *green_hot;
  G4VisAttributes *cyan;
  G4VisAttributes *blue;
  G4VisAttributes *magenta;

  // Logical Volumes
  G4LogicalVolume *LogicalWorld;
  G4LogicalVolume *LogicalStackIP;


  // Physical volumes
  G4VPhysicalVolume *PhysicalWorld;


  G4double PlaqueLength;
  G4double PlaqueThickness;
  G4double subPlaqueThickness;
  G4double gap;
  G4int nbPlaque;
  G4VPhysicalVolume *physiStackIP[10];



};
#endif
