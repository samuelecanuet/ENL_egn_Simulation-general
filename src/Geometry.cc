// Geometry.cc
//// Auteur: Arnaud HUBER for ENL group <huber@cenbg.in2p3.fr>
//// Copyright: 2022 (C) Projet RATP - ENL [LP2IB] - CELIA

#include "ENLegnSimMaterials.hh"
#include "Geometry.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Transform3D.hh"
#include "G4UnionSolid.hh"
#include <fstream>
#include <iostream>
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Polyhedra.hh"
#include <G4Polycone.hh>
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4UnitsTable.hh"
#include <math.h>

#include "G4GDMLParser.hh"



using namespace CLHEP;

// ***********************
// Constructor
// ***********************
const G4String Geometry::path_bin = "../bin/";


Geometry::Geometry(G4String buildfile){

  // Read keys and values from file buildfile defined in x_blockGeometry.cc
  // Some of these variables may not be needed.
  std::ifstream config;
  config.open(buildfile);
  if ( !config.is_open() )
    G4cout << "Error opening file " << buildfile << G4endl;
  else{
    while( config.is_open() ){
      G4String variable;
      G4String unit;
      G4double value;

      config >> variable;
      if(!config.good()) break;
      //####################### COMMON variables ###########################
      if(variable == "PlaqueLength"){
  	config >> value >> unit;
  	PlaqueLength = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "PlaqueThickness"){
  	config >> value >> unit;
  	PlaqueThickness = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "subPlaqueThickness"){
    config >> value >> unit;
    subPlaqueThickness = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "gap"){
    config >> value >> unit;
    gap = value*G4UnitDefinition::GetValueOf(unit);
      }
      else if(variable == "nbPlaque"){
    config >> value;
    nbPlaque = value;
      }
    }
  }
  config.close();



    G4cout << "\n The Variables that we read in are: "
    << "\n PlaqueLength = " << PlaqueLength
    << "\n PlaqueThickness = " << PlaqueThickness
    << "\n subPlaqueThickness = " << subPlaqueThickness
    << "\n PlaqueNumber = " << nbPlaque
    << "\n " << G4endl;

}
// ***********************
// Destructor
// ***********************
Geometry::~Geometry()
{
  if(detecProp) { delete detecProp; detecProp = 0; }
  if(clear) { delete clear; clear = 0; }
}

G4LogicalVolume *Geometry::GetStackIP()
{
    Material = detecProp->GetMaterial("G4_Si");
    G4Box *Box = new G4Box("Stack_IP", PlaqueLength/2, PlaqueLength/2, PlaqueThickness);
    LogicalVolume = new G4LogicalVolume(Box, Material, "Stack_IP");
    return LogicalVolume;
}
