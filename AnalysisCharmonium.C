

//-------------------------------------------------------
// Header files
//-------------------------------------------------------

// c++ headers
#include <iostream>
#include <fstream>

// root headers
#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLorentzVector.h>

// aliroot headers
#include <AliAODTrack.h>
#include <AliESDtrack.h>

// my headers
  TH1F *Mass_H = new TH1F("Mass_H","Mass_H",200,2.,4.);
  TH1F *Pt_H = new TH1F("Pt_H","Pt_H",200,0.,1.);
  TH1F *Pt2_H = new TH1F("Pt2_H","Pt2_H",500,0,0.5);
  TH1F *Phi_H = new TH1F("Phi_H","Phi_H",350,-3.5,3.5);
  TH1F *Y_H = new TH1F("Y_H","Y_H",100,-2,2);
  TH2F *dedx_H = new TH2F("dEdx","Ionization loss in TPC",100,0.,100.,100,0.,100.);
  TH1F *vtx_x_H = new TH1F("vtx_x","Primary vertex in x",100,-.02,.1);
  TH1F *vtx_z_H = new TH1F("vtx_z","Primary vertex in z",100,-10.,10.);
  TH1F *vtx_y_H = new TH1F("vtx_y","Primary vertex in y",100,.04,.2);
  TH2F *vtx_xy_H = new TH2F("vtx_xy","Primary vertex in x,y; x axis; y axis",100,-.04,.07,100,.04,.14);
  TH2F *vtx_xz_H = new TH2F("vtx_xz","Primary vertex in x,z; x axis; z axis",100,-.06,.15,100,-25.,25.);
  TH2F *vtx_yz_H = new TH2F("vtx_yz","Primary vertex in y,z; y axis; z axis",100,.04,.8,100,-20.,20.);
  TH2F *vtx_zx_H = new TH2F("vtx_zx","Primary vertex in z,x; z axix; x axis",100,-20.,20.,100,-.1,.17);
  TH2F *pid_muon_H = new TH2F("pid_muon_H","PID for #mu; First track; Second track",100,-10.,20.,100,-10.,20.);
  TH2F *vtx_x_error_H = new TH2F("vtx_x_error_H","Secondary vertex for x with error; position; eroor",100,-10.,10.,100,-4.,4.);
#include "TreeVariables.h"
#include "Utilities.h"
#include "Histograming.h"

using namespace std;


//-------------------------------------------------------
// Main program
//-------------------------------------------------------

void AnalysisCharmonium()

{
  // open input file 
  TFile *InputFile = new TFile("AnalysisResults_UD_PbPb_AOD_44_20150730.root");

  // get the tree
  InputFile->GetObject("Psi2sCentral/fJPsiTree;1",TwoTracksTree);
  ConnectTwoTracksTree();

  // Loop over the tree entries and do the analysis
  Double_t nEntries = (Double_t) TwoTracksTree->GetEntries();
  cout << " Entries = " << nEntries << endl;

  Int_t nSelEv = 0;
  for (Int_t iEntry = 0; iEntry<nEntries;iEntry++) {
    // get entry
    TwoTracksTree->GetEntry(iEntry);

    // count ccup4 triggers
    if (!EventSelected()) { continue;}
    nSelEv++;
    Histos_Kinematics();
  }

  cout << " There are " << nSelEv << " triggers in tree " << endl;
  SaveHistrograms();
  
}
