// different_dimensions.C
#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <vector>
#include <string>

void different_dimensions() {
    // Nomi dei file e colori/marker
  std::vector<std::string> dim = {"5", "10", "15", "20", "25"};  
  std::vector<Color_t> colors = {kBlue, kRed, kGreen+2, kOrange, kBlack};
  std::vector<Style_t> markers = {24, 24, 24, 24, 24}; // cerchio, quadrato, triangolo, croce, asterisco
  int num_events = 1e6;

    // Canvas
  TCanvas* c = new TCanvas("c", "EAbs da diverse dimensioni", 800, 600);

    // Legend
  TLegend* leg = new TLegend(0.80,0.65,0.92,0.88);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
for (size_t i = 0; i < dim.size(); ++i) {
    std::string file_name = "gammaQGSP_BIC_EMZ" + dim[i] + "_4.root";
    TFile* f = TFile::Open(file_name.c_str(), "READ");

    TDirectory* dir = dynamic_cast<TDirectory*>(f->Get("histo"));
    TH1D* h = dynamic_cast<TH1D*>(dir->Get("EAbs"));
    h->Rebin(40);

    // Costruzione del TGraphErrors
    std::vector<double> x, y, ex, ey;
    for (int bin = 1; bin <= h->GetNbinsX(); ++bin) {
        double content = h->GetBinContent(bin);
        if (content == 0) continue;

        x.push_back((h->GetBinCenter(bin))*1000);
        y.push_back(content/num_events);
        ex.push_back(0); // niente errore orizzontale
        ey.push_back((h->GetBinError(bin))/num_events);
    }

    TGraphErrors* g = new TGraphErrors(x.size(), x.data(), y.data(), ex.data(), ey.data());
    g->GetXaxis()->SetTitle("Energy [keV]");
    g->GetXaxis()->SetRangeUser(0, 700);
    g->SetMarkerStyle(8);
    g->SetMarkerColor(colors[i]);
    g->SetLineColor(colors[i]);
    g->SetMarkerSize(1);

    if (i == 0) {
        g->Draw("APE");  // Assi + punti
        g->GetYaxis()->SetRangeUser(0,0.055);
    } else {
        g->Draw("PE SAME");
    }

    leg->AddEntry(g, (dim[i] + " cm").c_str(), "PE");
 }

  leg->Draw();
   // Aggiorna canvas
  c->Update();
}
