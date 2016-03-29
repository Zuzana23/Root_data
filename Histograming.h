


//-------------------------------------------------------
// Save histograms used in the analysis
//-------------------------------------------------------

void SaveHistrograms()

{
  TFile *HistosOut = new TFile("HistogramOutputData.root","recreate");
  HistosOut->cd();

  Mass_H->Write();
  Pt_H->Write();
  Pt2_H->Write();
  Phi_H->Write();
  Y_H->Write();
  dedx_H->Write();
  vtx_x_H->Write();
  vtx_z_H->Write();
  vtx_y_H->Write();
  vtx_xy_H->Write();
  vtx_xz_H->Write();
  vtx_yz_H->Write();
  vtx_zx_H->Write();
  pid_muon_H->Write();
  vtx_x_error_H->Write();

  HistosOut->Close();
}



//-------------------------------------------------------
// Fill histos with kinematics
//-------------------------------------------------------

void Histos_Kinematics()
{
  // get tracks
  AliAODTrack *trk0 = (AliAODTrack*) fAODTracks->At(0);
  AliAODTrack *trk1 = (AliAODTrack*) fAODTracks->At(1);

  // create four momenta
  Double_t MassMuon = 0.1056;
  TLorentzVector lv0, lv1;
  lv0.SetPtEtaPhiM(trk0->Pt(), trk0->Eta(), trk0->Phi(), MassMuon);
  lv1.SetPtEtaPhiM(trk1->Pt(), trk1->Eta(), trk1->Phi(), MassMuon);
  TLorentzVector lvSum = lv0+lv1;

  // fill histograms
  Mass_H->Fill(lvSum.M());
  Pt_H->Fill(lvSum.Pt()); 
  Pt2_H->Fill(lvSum.Pt()*lvSum.Pt()); 
  Phi_H->Fill(lvSum.Phi());
  Y_H->Fill(lvSum.Rapidity());

  dedx_H->Fill(trk0->GetTPCsignal(),trk1->GetTPCsignal());
  vtx_x_H->Fill(fVtxPos[0]);
  vtx_z_H->Fill(fVtxPos[2]);
  vtx_y_H->Fill(fVtxPos[1]);
  vtx_xy_H->Fill(fVtxPos[0],fVtxPos[1]);
  vtx_xz_H->Fill(fVtxPos[0],fVtxPos[2]);
  vtx_x_error_H->Fill(fVtxPos[0],fVtxErr[0]);
  vtx_yz_H->Fill(fVtxPos[1],fVtxPos[2]);
  vtx_zx_H->Fill(fVtxPos[2],fVtxPos[0]);
  pid_muon_H->Fill(fPIDTPCMuon[0],fPIDTPCMuon[1]);
}

