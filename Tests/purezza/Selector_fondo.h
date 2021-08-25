//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar  7 14:44:34 2019 by ROOT version 6.14/04
// from TTree Wgamma/
// found on file: mc16a_Vgamma_gammajet_36.4fb.root
//////////////////////////////////////////////////////////


/* 
TAGLI

SR
Preselected: trigger_HLT_g140_loose
MET cut: met_tst_et>150000
ph cut: ph_pt>150000&&fabs(ph_eta2)<2.37 && (fabs(ph_eta2)<1.37 || fabs(ph_eta2)>1.52)
MET sig: met_tst_sig_old>8.5
Dphi(MET,ph): fabs(ph_met_dphi) > 0.4
Z vertex: fabs(ph_ZVtx<250)
jet veto: n_jet==0 ||(n_jet==1 && n_jet_good==n_jet)
lep veto: n_el_baseline==0 && n_mu_baseline==0"
tight ph: ph_isTight==1
isolation: ph_topoetcone40/1000. < (0.022*(ph_pt/1000)+2.45) &&
ph_ptcone20/ph_pt<0.05

Per le CR vanno eliminati i tagli in MET significance e Z vertex. Poi
bisogna sostituire alla met la met_nomu per le MuCR e la met_noelectron
per la 2EleCR, sia nel taglio di MET che in Dphi(MET,ph) (quindi dovrai
usare ph_met_nomuon_dphi o ph_met_noelectron_dphi). Infine bisogna
sostituire il lepton veto con
- 1MuCR n_el_baseline==0 && n_mu==1
- 2MuCR n_el_baseline==0 && n_mu==2 && mumu_m>10000
- 2EleCR n_mu_baseline==0 && n_el==2 && ee_m>10000

PhJetCR = (
         {"name": "Presel", "cut": "trigger_HLT_g140_loose == 1"},
         {"name": "MET ", "cut": "met_tst_et > 85000.&&met_tst_et<110000"},
         {"name": "ph_pt>150GeV", "cut": "(ph_pt > 150000. && fabs(ph_eta2) <
2.37 && (fabs(ph_eta2) < 1.37 || fabs(ph_eta2) > 1.52))"},
         {"name": "DPhi(ph,MET)", "cut": "fabs(ph_met_wmuon_dphi)>
0.4&&fabs(ph_met_wmuon_dphi)<3"},
         {"name": "Jet Veto", "cut": "(n_jet==0 ||(n_jet==1 &&
n_jet_good==n_jet))"},
         {"name": "Lep veto", "cut": "n_el_baseline==0 && n_mu_baseline==0"},
         {"name": "Ph Tight ", "cut": "ph_isTight == 1"},
         {"name": "Ph Iso", "cut": "(ph_topoetcone40/1000. <
(0.022*(ph_pt/1000)+2.45) && ph_ptcone20/ph_pt<0.05)"},

)


per le tightness-x sono a 1 le va variabili che non si vogliono controllare
(1,11,12,13,14,15,16 sono sempre a 1)

tight2 18,19,22
tight3 19,22
tight4 19
tight5 


*/




#ifndef Selector_fondo_h
#define Selector_fondo_h

// -------------- MASCHERE ---------------- //

#define tight3 0x65fc01
#define tight4 0x45fc01
#define tight5 0x41fc01
#define luminosity 140000.
#define PATH_OUT "root_files/puro_fondo_pesato.root"


#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2F.h>
#include <fstream>
// Headers needed by this particular selector
#include <vector>



class Selector_fondo : public TSelector {
public :
   TTreeReader    fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   

   //------------------------------LEAFS USATE------------------------------
   TTreeReaderValue<Int_t> run = {fReader, "run"};
   TTreeReaderValue<Int_t> trigger_HLT_g140_loose = {fReader, "trigger_HLT_g140_loose"};
   TTreeReaderValue<Float_t> met_tst_et = {fReader, "met_tst_et"};
   TTreeReaderArray<float> ph_pt = {fReader, "ph_pt"};
   TTreeReaderArray<float> ph_eta2 = {fReader, "ph_eta2"};
   TTreeReaderValue<Float_t> met_tst_sig_old = {fReader, "met_tst_sig_old"};
//   TTreeReaderArray<float> ph_met_dphi = {fReader, "ph_met_dphi"};
   TTreeReaderArray<float> ph_met_wmuon_dphi = {fReader, "ph_met_wmuon_dphi"};
   TTreeReaderArray<float> ph_ZVtx = {fReader, "ph_ZVtx"};
   TTreeReaderValue<Int_t> n_jet = {fReader, "n_jet"};
   TTreeReaderValue<Int_t> n_jet_good = {fReader, "n_jet_good"};
   TTreeReaderValue<Int_t> n_el_baseline = {fReader, "n_el_baseline"};
   TTreeReaderValue<Int_t> n_mu_baseline = {fReader, "n_mu_baseline"};
   TTreeReaderArray<int> ph_isTight = {fReader, "ph_isTight"};
   TTreeReaderArray<float> ph_topoetcone40 = {fReader, "ph_topoetcone40"};
   TTreeReaderArray<float> ph_ptcone20 = {fReader, "ph_ptcone20"};

   TTreeReaderArray<int> ph_isEM = {fReader, "ph_isEM"};

   TTreeReaderValue<Float_t> met_nomuon_tst_et = {fReader, "met_nomuon_tst_et"};
   TTreeReaderValue<Float_t> met_noelectron_tst_et = {fReader, "met_noelectron_tst_et"};
   TTreeReaderValue<Float_t> mumu_m = {fReader, "mumu_m"};
   TTreeReaderValue<Float_t> ee_m = {fReader, "ee_m"};
   TTreeReaderArray<float> ph_met_nomuon_dphi = {fReader, "ph_met_nomuon_dphi"};
   TTreeReaderArray<float> ph_met_noele_dphi = {fReader, "ph_met_noele_dphi"};
   TTreeReaderValue<Int_t> n_mu = {fReader, "n_mu"};
   TTreeReaderValue<Int_t> n_el = {fReader, "n_el"};

   TTreeReaderValue<Float_t> xSec_SUSY = {fReader, "xSec_SUSY"};
   TTreeReaderValue<Float_t> k_factor = {fReader, "k_factor"};
   TTreeReaderValue<Float_t> filter_eff = {fReader, "filter_eff"};
   TTreeReaderValue<Float_t> evsf_good_nominal_EL = {fReader, "evsf_good_nominal_EL"};
   TTreeReaderValue<Float_t> evsf_good_nominal_MU = {fReader, "evsf_good_nominal_MU"};
   TTreeReaderValue<Float_t> evsf_leading_nominal_PH = {fReader, "evsf_leading_nominal_PH"};
   TTreeReaderValue<Float_t> pu_weight = {fReader, "pu_weight"};
   TTreeReaderValue<Float_t> mc_weight_sum = {fReader, "mc_weight_sum"};
   TTreeReaderValue<float> mconly_weight = {fReader, "mconly_weight"};

   //------------------------------DEFINIZIONE VARIABILI------------------------------
   
   int tmpInt;
   float tmpFloat;
   bool tmpBool;

   Int_t NumberOfEvents;
   Int_t N_trigger;
   Int_t N_met_tst_et;
   Int_t N_ph_pt;
   Int_t N_met_tst_sig_old;
   Int_t N_ph_met_dphi;
   Int_t N_ph_ZVtx;
   Int_t N_jet_veto;
   Int_t N_lepton_veto;

   Float_t weight;

   Int_t intervallix,intervalliy;
   Float_t minx,maxx,miny,maxy;
   Float_t Eiso;

   Float_t bin_tight, bin_tight3, bin_tight4, bin_tight5, bin_nottight;

   
   //_____________ISTOGRAMMI_____________
   //ogni vettore ha 5 istogrammi che rappresentano rispettivamente le regioni ISR1, ISR2, ISR3, ESR1, ESR2

   TH2F **SR_H;
   TH2F **oneMuCR_H;
   TH2F **twoMuCR_H;
   TH2F **twoECR_H; 
   TH2F *gammaJetCR_H;

   TFile *file;

   Int_t N_TightIso;
  

   Selector_fondo(TTree * /*tree*/ =0) : 
      NumberOfEvents(0),
      N_trigger(0),
      N_met_tst_et(0),
      N_ph_pt(0),
      N_met_tst_sig_old(0),
      N_ph_met_dphi(0),
      N_ph_ZVtx(0),
      N_jet_veto(0),
      N_lepton_veto(0),
      weight(0),
      SR_H(0),
      oneMuCR_H(0),
      twoMuCR_H(0),
      twoECR_H(0),
      gammaJetCR_H(0),
      file(0),
      N_TightIso(0)
      { }

   virtual ~Selector_fondo() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();


   virtual void FillGraphs(TH2F **g, int i, Float_t met);
   virtual void FillGraphs(TH2F *g, int i); 



   ClassDef(Selector_fondo,0);

};

#endif

#ifdef Selector_fondo_cxx
void Selector_fondo::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t Selector_fondo::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef Selector_fondo_cxx
