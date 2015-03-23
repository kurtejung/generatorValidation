#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

using namespace std;

void genValidation(std::string filelist){

  std::string filename;
  std::ifstream inss(filelist.c_str(), std::ifstream::in);

  TFile *fout = new TFile("output.root","recreate");

  TH1D *multVsEta = new TH1D("multVsEta","",50,-5,5); multVsEta->Sumw2();
  TH1D *hadronPt = new TH1D("hadronPt","",100,0,100); hadronPt->Sumw2();
  TH1D *genJetPt = new TH1D("genJetPt","",100,0,500); genJetPt->Sumw2();
  TH1D *nMultDivnPart = new TH1D("nMultDivnPart","",50,-5,5); nMultDivnPart->Sumw2();
  TH1D *cent = new TH1D("cent","",100,0,100); cent->Sumw2();

  float partEta[50000], partPt[50000];
  int partChg[50000]; 
  int partMult, nref, bin;
  float npart;
  float refpt[200];
  int ifile=0;
  int totalEvents=0;
  double totalnpart=0;
  while(inss>>filename && ifile<100){
    
    cout << "opening file " << ifile++ << ": " << filename << endl;
    TFile *f1 = new TFile(filename.c_str());

    TTree *genPart = (TTree*)f1->Get("HiGenParticleAna/hi");
    TTree *jet = (TTree*)f1->Get("akPu3PFJetAnalyzer/t");
    TTree *evt = (TTree*)f1->Get("hiEvtAnalyzer/HiTree");

    if(!genPart || !jet){ cout << "warning! Tree not found!" << endl; continue; }

    genPart->SetBranchAddress("eta",partEta);
    genPart->SetBranchAddress("chg",partChg);
    genPart->SetBranchAddress("pt",partPt);
    genPart->SetBranchAddress("mult",&partMult);
    evt->SetBranchAddress("hiBin",&bin);
    evt->SetBranchAddress("Npart",&npart);

    jet->SetBranchAddress("nref",&nref);
    jet->SetBranchAddress("refpt",refpt);

    for(int ientry=0; ientry<genPart->GetEntries(); ientry++){
      totalEvents++;
      
      genPart->GetEntry(ientry);
      jet->GetEntry(ientry);
      evt->GetEntry(ientry);
      cent->Fill((float)bin/2.);
      // cout << "event: " << ientry << endl;
      //cout << "multiplicity" << partMult << endl;
      totalnpart += npart;
      for(int imult=0; imult<partMult; imult++){
	if(partChg[imult]){
	  multVsEta->Fill(partEta[imult]);
	  if(npart>0) nMultDivnPart->Fill(partEta[imult],(1./(float)npart/2.));
	  hadronPt->Fill(partPt[imult]);
	}
      }
      // cout << "Njets: " << nref << endl;
      for(int iref=0; iref<nref; iref++){
	genJetPt->Fill(refpt[iref]);
      }
    }
    f1->Close();
  }
  totalnpart/=(double)totalEvents;
  fout->cd();
  //multVsEta->Scale(1./(double)totalEvents);
  multVsEta->Write();
  hadronPt->Write();
  genJetPt->Write();
  //nMultDivnPart->Scale(1./totalnpart);
  //nMultDivnPart->Scale(1./(double)totalEvents);
  //nMultDivnPart->Scale(5.);
  nMultDivnPart->Write();
  cent->Write();
  fout->Close();

  cout << "Total Events: "<< totalEvents << endl;
  cout << "average npart: "<< totalnpart <<endl;
}
