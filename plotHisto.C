void plotHisto(const char* filename = "AnaEx01.root"){

  // Apre il file ROOT e ottiene l'istogramma originale (in MeV)
  TFile* f = new TFile(filename);
  if (!f || f->IsZombie()) {
    std::cerr << "Errore: Impossibile aprire il file " << filename << std::endl;
    return;
  }
  
  TDirectory* dir = dynamic_cast<TDirectory*>(f->Get("histo"));
  TH1D* hist_MeV = dynamic_cast<TH1D*>(dir->Get("EAbs"));
  
  if (!hist_MeV) {
    std::cout << "Istogramma 'EAbs' non trovato!" << std::endl;
    return;
  }

  // --- Conversione dell'asse da MeV a keV ---

  // 1. Ottiene i parametri dell'istogramma originale
  int nbins = hist_MeV->GetNbinsX();
  double cont, bin;
  double previous_cont=0;
  double delta=0;
  double tmp=0;
  double xmin_MeV = hist_MeV->GetXaxis()->GetXmin();
  double xmax_MeV = hist_MeV->GetXaxis()->GetXmax();

  // 2. Crea un nuovo istogramma con l'asse in keV (1 MeV = 1000 keV)
  TH1D* hist_keV = new TH1D("EAbs_keV", "Spectrum of energy absorbed by the polystyrene", nbins, xmin_MeV * 1000.0, xmax_MeV * 1000.0);

  // 3. Copia i dati dal vecchio istogramma a quello nuovo
  for (int i = 1; i <= nbins; ++i) {
      cont=hist_MeV->GetBinContent(i);
      hist_keV->SetBinContent(i, cont);
      hist_keV->SetBinError(i, hist_MeV->GetBinError(i));
      if(i>2){//Parte da i=3 poiché altrimenti prenderebbe energie prossime allo 0 con uno scarto maggiore di quello compton
	tmp = cont-previous_cont;
	previous_cont=cont;
	if(tmp<delta){
	  delta=tmp;
	  bin = hist_keV->GetBinCenter(i-1);
	}
      }	
  }
  hist_keV->SetEntries(hist_MeV->GetEntries());

  // --- Disegna il nuovo istogramma in keV ---
  TCanvas* c1 = new TCanvas("c1", "Energy Spectrum");
  
  double NEntries = hist_keV->GetEntries();
  hist_keV->Rebin(6);
  if (NEntries > 0) {
      hist_keV->Scale(1.0 / NEntries);
  }
  
  hist_keV->GetXaxis()->SetTitle("Energy [keV]");
  hist_keV->GetYaxis()->SetRangeUser(0, 0.0071);
  hist_keV->SetLineColor(kBlack);
  hist_keV->Draw("HISTE");
  double error_sq12 = 0.5/std::sqrt(12);
  std::cout << "Delta Compton: "<< delta << std::endl;
  std::cout<<"Compton Edge: "<<bin<<"+-"<<error_sq12<<std::endl;
}
