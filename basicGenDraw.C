#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TH1D.h"
#include <string>
#include "TChain.h"

using namespace std;

void basicGenDraw(std::string filelist="pythiaGenTest.txt", int startfile=0){

  std::string filename;
  std::ifstream inss(filelist.c_str(), std::ifstream::in);
  
  TChain *ch = new TChain("Events");
  while(inss>>filename){
    
    cout << "opening " << filename << endl;
    ch->Add(filename.c_str());
    
  }
  
  TH1D *trkPt = new TH1D("trkPt","",50,0,100); trkPt->Sumw2();
  TH1D *trkEta = new TH1D("trkEta","",50,-5,5); trkEta->Sumw2();
  TH1D *impactPar = new TH1D("impactPar","",50,1000,2000); impactPar->Sumw2();

  ch->SetAlias("HepMC","edmHepMCProduct_generator__HLT.obj");
  ch->SetAlias("genParticles","recoGenParticles_genParticles__HLT.obj");

  //project "draws" without actually drawing...
  ch->Project("trkPt","genParticles.pt()","genParticles.status()==1 && genParticles.pdgId()==13 && genParticles.pt()>0.4");
  ch->Project("trkEta","genParticles.eta()","genParticles.status()==1 && genParticles.pdgId()==13 && genParticles.pt()>0.4");
  ch->Project("impactPar","HepMC.GetEvent()->heavy_ion()->Ncoll()");

  TFile *fout = new TFile(Form("validationHistos_%d.root",startfile),"recreate");
  fout->cd();
  trkPt->Write();
  trkEta->Write();
  impactPar->Write();

}
