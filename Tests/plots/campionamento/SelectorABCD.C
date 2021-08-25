#define SelectorABCD_cxx
// The class definition in SelectorABCD.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("SelectorABCD.C")
// root> T->Process("SelectorABCD.C","some options")
// root> T->Process("SelectorABCD.C+")
//


#include <SelectorABCD.h>
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <TH1F.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <cmath>
#include <fstream>
#include <TTree.h>
#include <cstring>


string process = "Wgamma";
bool pesati = true;

#define tight3 0x65fc01
#define tight4 0x45fc01
#define tight5 0x41fc01
#define luminosity 140000.



using namespace std;

void SelectorABCD::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   N = 4000;
   bins = new float[N];
   Na = new float[N-1];
   Nb = new float[N-1];
   Ma = new float[N-1];
   Mb = new float[N-1];
   
   
   
   for (int i = 0; i < N-1; i++) {
      Na[i] = 0.;
      Nb[i] = 0.;
      Ma[i] = 0.;
      Mb[i] = 0.;
      bins[i] = (i+1)*0.5;
   }
   bins[N-1] = N*0.5;


}

void SelectorABCD::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();

}

Bool_t SelectorABCD::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);

   //-----------------------SELEZIONI-------------------------

   if (ph_pdgId.GetSize() == 0 || ph_mother_pdgId.GetSize() == 0)    return kFALSE;
   
   // signal

   if (sample == "Wgamma" || sample == "Zgamma" || sample == "Znunugamma" || sample == "gammajets")
      if ( !(ph_pdgId[0] == 22 && abs(ph_mother_pdgId[0])<100) )
         return kFALSE;


   // background
   
   if (sample == "Wjets" || sample == "Zjets")
      if ( !(abs(ph_pdgId[0]) != 11 && (ph_pdgId[0] != 22 || (ph_pdgId[0] == 22 && abs(ph_mother_pdgId[0])>100))) )
         return kFALSE;



   if (met_pt == "pt")  var = ph_pt[0];
   if (met_pt == "met") var = *met_tst_et;
   

   // SR
   if(*trigger_HLT_g140_loose==1)

         if(*met_tst_et > 150000.)

            if(ph_pt[0] > 150000. && fabs(ph_eta2[0]) < 2.37 && (fabs(ph_eta2[0]) < 1.37 || fabs(ph_eta2[0]) > 1.52))

               if(*met_tst_sig_old > 8.5)

                  if(fabs(ph_met_wmuon_dphi[0]) > 0.4)
                                                
                     if(fabs(ph_ZVtx[0]) < 250.)

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet))

                           if(*n_el_baseline==0 && *n_mu_baseline==0)   

                              for (int i = 0; i < N-1; i++) 
                                 if (var/1E3 > bins[i] && var/1E3 <= bins[i+1])
                                    fill_matrices(i);


            

   
   

   return kTRUE;
}

void SelectorABCD::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void SelectorABCD::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
 

   ofstream out("dati/txt files" + string(directory) + "/" + string(sample) + "_" + string(met_pt) + ".txt");

   for (int i = 0; i < N; i++)
      out << Na[i] << "\t" << Nb[i] << "\t" << Ma[i] << "\t" << Mb[i] << endl;

   out.close();

   

}


void SelectorABCD::fill_matrices(int i)

{

   if(*mconly_weight >  100.)       weight =  1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else if(*mconly_weight < -100.)  weight = -1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else                             weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;

   if(*xSec_SUSY>500.) weight = 0.;

   calo_isolation  = (ph_topoetcone40[0]/1E3) - (0.022*(ph_pt[0]/1E3)+2.45);  //In GeV
   track_isolation = ph_ptcone20[0]/ph_pt[0];


   if (calo_isolation < 0. && track_isolation < 0.05) {
      
      if (ph_isTight[0])                              Na[i] += weight;
      if (!(ph_isEM[0] & tight4) && !ph_isTight[0])   Ma[i] += weight;
   }

   if ((calo_isolation  > 3. && calo_isolation < 140. && track_isolation < 2.) ||
       (calo_isolation <= 3. && track_isolation > 0.10 && track_isolation < 2.)) {
      
      if (ph_isTight[0])                              Nb[i] += weight;
      if (!(ph_isEM[0] & tight4) && !ph_isTight[0])   Mb[i] += weight;
      
   }

}

