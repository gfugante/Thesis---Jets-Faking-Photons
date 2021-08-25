//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jul 28 11:21:10 2019 by ROOT version 6.14/04
// from TTree Wgamma/
// found on file: /storage_tmp/atlas/fpiazza/MC_minitrees_65/mc16a_65.root
//////////////////////////////////////////////////////////

#ifndef SelectorData_h
#define SelectorData_h


// global constant variables
#define tight3 0x65fc01
#define tight4 0x45fc01
#define tight5 0x41fc01
#define luminosity 140000.

#define sample "data"
#define directory " 18"


#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>



class SelectorData : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain



   // used variables

   Float_t ****SR, ****onemuCR, ****twomuCR, ****twoeCR, ***gammajetCR;

   Float_t *met_bins;
   
   Float_t calo_isolation, track_isolation;
   Float_t *calo_isolation_gap, *track_isolation_gap;
   Float_t calo_isolation_max_not_iso, track_isolation_max_not_iso;
   Float_t calo_isolation_max_iso, track_isolation_max_iso;
   Float_t weight;

   int bin_tight, bin_tight3, bin_tight4, bin_tight5, bin_nottight;

   int i, numberOfMetBins;




   // LEAFS
   TTreeReaderValue<Int_t> trigger_HLT_g140_loose = {fReader, "trigger_HLT_g140_loose"};
   TTreeReaderValue<Float_t> met_tst_et = {fReader, "met_tst_et"};
   TTreeReaderArray<float> ph_pt = {fReader, "ph_pt"};
   TTreeReaderArray<float> ph_eta2 = {fReader, "ph_eta2"};
   TTreeReaderValue<Float_t> met_tst_sig = {fReader, "met_tst_sig"};
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






   SelectorData(TTree * /*tree*/ =0) { }
   virtual ~SelectorData() { }
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


   virtual void read_parameters(string file);
   virtual void create_matrices();
   virtual void select_met_bin(Float_t ****mat, int i, Float_t met);
   virtual void fill_matrices(Float_t ***mat, int i); 



   ClassDef(SelectorData,0);

};

#endif

#ifdef SelectorData_cxx
void SelectorData::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t SelectorData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef SelectorData_cxx
