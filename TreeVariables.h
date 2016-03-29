//
// variables for the tree
//
const Int_t ntrg=17;
Int_t fRunNum;
UInt_t fPerNum, fOrbNum;

Bool_t fTrigger[ntrg];
Bool_t fTriggerInputsMC[4];
UInt_t fL0inputs, fL1inputs;
  
Double_t fPIDTPCMuon[4];
Double_t fPIDTPCElectron[4];
Double_t fPIDTPCPion[4];
Double_t fPIDTPCKaon[4];
Double_t fPIDTPCProton[4];

Double_t fPIDTOFMuon[4];
Double_t fPIDTOFElectron[4];
Double_t fPIDTOFPion[4];
Double_t fPIDTOFKaon[4];
Double_t fPIDTOFProton[4];

Int_t fVtxContrib;
Int_t fSpdVtxContrib;
Double_t fVtxPos[3];
Double_t fSpdVtxPos[3];
Double_t fVtxErr[3];
Double_t fVtxChi2,fVtxNDF;
Double_t fKfVtxPos[3];
UShort_t fBCrossNum, fNtracklets, fNLooseTracks;

//vzero, zdc
Double_t        fZNAenergy;
Double_t        fZNCenergy;
Double_t        fZPAenergy;
Double_t        fZPCenergy;
Double_t        fZDCAtime;
Double_t        fZDCCtime;

Int_t fV0Adecision, fV0Cdecision;

//tracks
TClonesArray *fAODTracks;

// MC particles
TClonesArray *fGenPart;

// the tree
TTree *TwoTracksTree;
