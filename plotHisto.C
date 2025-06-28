void plotHisto(const char* filename = "AnaEx01.root"){
  
  // Draw histos filled by Geant4 simulation 
  //   
  TFile* f = new TFile(filename);  
  TCanvas* c1 = new TCanvas("c1", "  ");
  
  TDirectory* dir = dynamic_cast<TDirectory*>(f->Get("histo"));
    
  TH1D* hist1 = dynamic_cast<TH1D*>(dir->Get("EAbs"));
  double NEntries = hist1->GetEntries();
  hist1->Scale(1.0/NEntries);
  hist1->SetTitle("Spectrum of energy absorbed by the polystyrene");
  hist1->GetXaxis()->SetTitle("Energy (keV)");
  hist1->Draw("HIST");
  std::cout << "GetEntries(): " << hist1->GetEntries() << std::endl;
std::cout << "Integral():   " << hist1->Integral() << std::endl;


}
