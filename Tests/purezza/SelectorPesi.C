#define SelectorPesi_cxx
// The class definition in SelectorPesi.h has been generated automatically
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
// root> T->Process("SelectorPesi.C")
// root> T->Process("SelectorPesi.C","some options")
// root> T->Process("SelectorPesi.C+")
//


#include <SelectorPesi.h>
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <cmath>
#include <fstream>
#include <TTree.h>
#include <iomanip>


using namespace std;

void SelectorPesi::Begin(TTree * tree)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   //_________________DEFINIZIONE_ISTOGRAMMI_________________

   bin_tight = 5.;
   bin_tight3 = 1.;
   bin_tight4 = 2.;
   bin_tight5 = 3.;
   bin_nottight = 4.;



   //---------------------------------------------
   //X = isolamento  Y = tightness

   intervalliy = 5;
   miny = 0.;
   maxy = 5.;
   intervallix = 140;
   minx = -40.;
   maxx = 100.;

   //---------------------------------------------
   c1 = new TCanvas("c1");


   weights_H = new TH1F("xSec_SUSY Wjets", "xSec_SUSY Wjets", 100000, -100000., +1000.);
   weights_H->GetXaxis()->SetTitle("weights");
   weights_H->GetXaxis()->CenterTitle();
   weights_H->GetYaxis()->SetTitle("Number of events");
   weights_H->GetYaxis()->CenterTitle();
   

}

void SelectorPesi::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();

}

Bool_t SelectorPesi::Process(Long64_t entry)
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

   NumberOfEvents++;

   weight = *xSec_SUSY;//luminosity * (*xSec_SUSY * *k_factor * *filter_eff (un pochino strano, tanti eventi e mal distribuito) * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH (strano) * *pu_weight * *mconly_weight) / *mc_weight_sum;   
   

   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {

      if(*trigger_HLT_g140_loose==1) {
         //++N_trigger;

         if(*met_tst_et>150000.) {
            //++N_met_tst_et;

            //if(ph_pt[i]<180000.)
            if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52)) {
               //++N_ph_pt;

               if(*met_tst_sig_old>8.5) {
                  //++N_met_tst_sig_old;

                  if(fabs(ph_met_wmuon_dphi[i]) > 0.4) {
                     //++N_ph_met_dphi;
                                                
                     if(fabs(ph_ZVtx[i])<250.) {
                        //++N_ph_ZVtx;

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet)) {
                           //++N_jet_veto;

                           if(true/**n_el_baseline==0 && *n_mu_baseline==0*/) {
                              //++N_lepton_veto;
                              if(weight<weightMin) weightMin = weight;
                              if(weight>weightMax) weightMax = weight;
                              if(abs(weight)<100) accettabili++;
                              weights_H->Fill(weight);

                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }


  weights_H->Fill(weight);





   return kTRUE;
}

void SelectorPesi::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void SelectorPesi::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
 

   cout << endl;
   cout << "Min weight: " << weightMin << endl;
   cout << "Max weight: " << weightMax << endl;
   cout << "Eventi totali: " << NumberOfEvents << endl;
   cout << "Minori di 100: " <<  100.*float(accettabili)/float(NumberOfEvents) << " %" << endl << endl;

   weights_H->GetXaxis()->SetRangeUser(weightMin-50., weightMax+50.);

   c1->SetLogy();
   c1->SetLogx();
   c1->cd();
   weights_H->Draw("hist");


}



