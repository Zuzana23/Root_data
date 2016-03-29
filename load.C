void load()
{
  // gROOT->ProcessLine(".include $ALICE_ROOT");
  gROOT->ProcessLine(".include $ALICE_ROOT/include");
  // gROOT->ProcessLine(".include $ALICE_ROOT/EVGEN");
  // gSystem->Load("libANALYSISalice");
  //gSystem->Load("libCORRFW");
  // gSystem->Load("libPWGmuon");

  gROOT->ProcessLine(".x AnalysisCharmonium.C+g");

}
