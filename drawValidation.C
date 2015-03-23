{

  TFile *hyd276 = new TFile("Hydjet_2p76TeV_53x.root");
  TFile *hyd502 = new TFile("Hydjet_5p02_74x.root");

  TH1D *hPt276 = (TH1D*)hyd276->Get("hadronPt")->Clone("hPt276");
  TH1D *hPt502 = (TH1D*)hyd502->Get("hadronPt")->Clone("hPt502");

  TH1D *jPt276 = (TH1D*)hyd276->Get("genJetPt")->Clone("jPt276");
  TH1D *jPt502 = (TH1D*)hyd502->Get("genJetPt")->Clone("jPt502");

  TH1D *cent276 = (TH1D*)hyd276->Get("cent")->Clone("cent276");
  TH1D *cent502 = (TH1D*)hyd502->Get("cent")->Clone("cent502");

  TH1D *mve276 = (TH1D*)hyd276->Get("multVsEta")->Clone("mve276");
  TH1D *mve502 = (TH1D*)hyd502->Get("multVsEta")->Clone("mve502");

  TCanvas *c1 = new TCanvas("c1","",800,600);
  c1->cd();
  hPt276->Scale(1./119648.);
  hPt276->SetXTitle("Hadron p_{T}");
  hPt276->SetYTitle("d#sigma/dp_{T}");
  hPt276->Draw();
  hPt502->SetMarkerStyle(20);
  hPt502->Scale(1./30000.);
  hPt502->SetMarkerColor(kRed+2);
  hPt502->SetLineColor(kRed+2);
  hPt502->Draw("same");

  TLegend *l1 = new TLegend(0.5,0.75,0.9,0.92);
  l1->AddEntry(hPt276,"Hydjet 2.76 TeV (53x)");
  l1->AddEntry(hPt502,"Hydjet 5.02 TeV (74x)");
  l1->Draw();

  TCanvas *c2 = new TCanvas("c2","",800,600);
  c2->cd();
  jPt276->Scale(1./119648.);
  jPt276->SetXTitle("Gen-jet p_{T}");
  jPt276->SetYTitle("d#sigma/dp_{T}");
  jPt276->Draw();
  jPt502->SetMarkerStyle(20);
  jPt502->Scale(1./30000.);
  jPt502->SetMarkerColor(kRed+2);
  jPt502->SetLineColor(kRed+2);
  jPt502->Draw("same");
  l1->Draw();

  TCanvas *c3 = new TCanvas("c3","",800,600);
  c3->cd();
  cent276->Scale(1./119648.);
  cent276->SetXTitle("Centrality (%)");
  cent276->SetYTitle("Event Fraction");
  cent276->Draw();
  cent502->SetMarkerStyle(20);
  cent502->Scale(1./30000.);
  cent502->SetMarkerColor(kRed+2);
  cent502->SetLineColor(kRed+2);
  cent502->Draw("same");
  l1->Draw();

  TCanvas *c4 = new TCanvas("c4","",800,600);
  c4->cd();
  mve276->Scale(1./119648.);
  mve276->Scale(5.);
  mve276->SetXTitle("#eta");
  mve276->SetYTitle("1/N dN/d#eta");
  mve276->Draw();
  mve502->SetMarkerStyle(20);
  mve502->Scale(1./30000.);
  mve502->Scale(5.);
  mve502->SetMarkerColor(kRed+2);
  mve502->SetLineColor(kRed+2);
  mve502->Draw("same");
  l1->Draw();

  TCanvas *c5 = new TCanvas("c5","",800,600);
  c5->cd();
  TH1D *ratio = (TH1D*)mve502->Clone("ratio");
  mve502->Divide(mve276);
  mve502->SetXTitle("#eta");
  mve502->SetYTitle("Hydjet 5.02 / 2.76");
  mve502->Draw();
}
