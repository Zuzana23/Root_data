//-------------------------------------------------------
// Relate tree entries to global variables
//-------------------------------------------------------

void ConnectTwoTracksTree() {
  // general information
  TwoTracksTree ->SetBranchAddress("fRunNum", &fRunNum);
  TwoTracksTree ->SetBranchAddress("fBCrossNum", &fBCrossNum);
  TwoTracksTree ->SetBranchAddress("fNtracklets", &fNtracklets);
  TwoTracksTree ->SetBranchAddress("fNLooseTracks", &fNLooseTracks);

  // trigger information
  // --> fTrigger[1] = CCUP2-B, fTrigger[2] = CCUP7-B, fTrigger[3] = CINT1-B
  TwoTracksTree ->SetBranchAddress("fTrigger", &fTrigger); 
  TwoTracksTree ->SetBranchAddress("fL0inputs", &fL0inputs);
  TwoTracksTree ->SetBranchAddress("fL1inputs", &fL1inputs);

  // vertex information
  TwoTracksTree ->SetBranchAddress("fVtxContrib", &fVtxContrib);
  TwoTracksTree ->SetBranchAddress("fVtxPos", &fVtxPos);
  TwoTracksTree ->SetBranchAddress("fVtxChi2", &fVtxChi2);
  TwoTracksTree ->SetBranchAddress("fVtxNDF", &fVtxNDF);
  TwoTracksTree ->SetBranchAddress("fSpdVtxContrib", &fSpdVtxContrib);
  //TwoTracksTree ->SetBranchAddress("fVtxPos", &fVtxPos);
  TwoTracksTree ->SetBranchAddress("fSpdVtxPos", &fSpdVtxPos);  
  //TwoTracksTree ->SetBranchAddress("fVtxChi2", &fVtxChi2);
  //TwoTracksTree ->SetBranchAddress("fVtxNDF", &fVtxNDF);

  // ZDC information
  TwoTracksTree->SetBranchAddress("fZNAenergy", &fZNAenergy);
   TwoTracksTree->SetBranchAddress("fZNCenergy", &fZNCenergy);
   TwoTracksTree->SetBranchAddress("fZPAenergy", &fZPAenergy);
   TwoTracksTree->SetBranchAddress("fZPCenergy", &fZPCenergy);
   TwoTracksTree->SetBranchAddress("fZDCAtime", &fZDCAtime);
   TwoTracksTree->SetBranchAddress("fZDCCtime", &fZDCCtime);


  // V0 information
  // -> kInvalid = -1, kEmpty =0, kBB =1, kBG =2, kFake =3
  TwoTracksTree ->SetBranchAddress("fV0Adecision", &fV0Adecision);
  TwoTracksTree ->SetBranchAddress("fV0Cdecision", &fV0Cdecision); 

  // number of sigmas away from the hypothesis for each track
  TwoTracksTree ->SetBranchAddress("fPIDTPCMuon", &fPIDTPCMuon);
  TwoTracksTree ->SetBranchAddress("fPIDTPCElectron", &fPIDTPCElectron);
  TwoTracksTree ->SetBranchAddress("fPIDTPCPion", &fPIDTPCPion);
  TwoTracksTree ->SetBranchAddress("fPIDTPCKaon", &fPIDTPCKaon);
  TwoTracksTree ->SetBranchAddress("fPIDTPCProton", &fPIDTPCProton);
  TwoTracksTree ->SetBranchAddress("fPIDTOFMuon", &fPIDTOFMuon);
  TwoTracksTree ->SetBranchAddress("fPIDTOFElectron", &fPIDTOFElectron);
  TwoTracksTree ->SetBranchAddress("fPIDTOFPion", &fPIDTOFPion);
  TwoTracksTree ->SetBranchAddress("fPIDTOFKaon", &fPIDTOFKaon);
  TwoTracksTree ->SetBranchAddress("fPIDTOFProton", &fPIDTOFProton);

  // tracks
  TwoTracksTree ->SetBranchAddress("fJPsiAODTracks", &fAODTracks);
}

//-------------------------------------------------------
// Criteria to select one good track
//-------------------------------------------------------

Bool_t IsGoodTrack(AliAODTrack *trk)
{
  // track exists
  if( !trk ) return kFALSE;
  // has filter bit 0 set
  if(!(trk->TestFilterBit(1<<0))) return kFALSE;
  // has been refitted with TPC and ITS
  if(!(trk->GetStatus() & AliESDtrack::kTPCrefit) ) return kFALSE;
  if(!(trk->GetStatus() & AliESDtrack::kITSrefit) ) return kFALSE;
  // it has at least 50 clusters
  if(trk->GetTPCNcls() < 50) return kFALSE;
  // is has at most chi2 of 2 per degree of freedom (two degrees of freedom)
  if(trk->Chi2perNDF() > 4) return kFALSE;
  // it has a point in SPD (layers 0 or  1)
  if(!(trk->HasPointOnITSLayer(0) || trk->HasPointOnITSLayer(1))) return kFALSE;

  // is a good track
  return kTRUE;
}


//-------------------------------------------------------
// Criteria to select the tracks of one event
//-------------------------------------------------------
Bool_t TracksSelected()
{
  // two tracks
  if (fAODTracks->GetEntries() != 2) return kFALSE;

  //get tracks
  AliAODTrack *trk0 = (AliAODTrack*) fAODTracks->At(0);
  AliAODTrack *trk1 = (AliAODTrack*) fAODTracks->At(1);

  // both tracks have opposite chargefAODTracks->At(0);
  Double_t ch0 = trk0->Charge();
  Double_t ch1 = trk1->Charge();
  if ((ch0*ch1) > 0) return kFALSE;

  // select each track
  if (!IsGoodTrack(trk0)) return kFALSE;
  if (!IsGoodTrack(trk1)) return kFALSE;

  // tracks passed selection
  return kTRUE;
}



//-------------------------------------------------------
// Criteria to select an event
//-------------------------------------------------------

Bool_t EventSelected()
{
  // has been triggered
  // --> fTrigger[0] = CCUP4
  if (fTrigger[0] != 1) return kFALSE;

  // nothing in VZERO
  if (fV0Adecision != 0) return kFALSE;
  if (fV0Cdecision != 0) return kFALSE;

  // Events with good vertex
  // ---> event has an SPD vertex
  if (fSpdVtxContrib<1) return kFALSE;
  // ---> SPD vtx is close to the primary vertex
  if (TMath::Abs(fSpdVtxPos[2]-fVtxPos[2])>0.04)  return kFALSE;

  
  // tracks pass selection
  if (!TracksSelected()) return kFALSE;

  // PID: both muon according to the TPC within 4 sigmas
  Double_t pid = fPIDTPCMuon[0]*fPIDTPCMuon[0]+fPIDTPCMuon[1]*fPIDTPCMuon[1];
  if (pid>16) return kFALSE;

  // event passed selection
  return kTRUE;
}

