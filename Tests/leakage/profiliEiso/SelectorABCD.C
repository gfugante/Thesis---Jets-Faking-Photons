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
#include <TH2F.h>
#include <TCanvas.h>
#include <TTreeReader.h>
#include <cmath>
#include <fstream>
#include <TTree.h>
#define PATH_OUT "root_files/Znunugamma_profili.root"

bool pesati = true;

using namespace std;

void SelectorABCD::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   //_________________DEFINIZIONE_ISTOGRAMMI_________________




   //---------------------------------------------


   intervallix = 340;
   minx = -30.;
   maxx = 140.;

   //---------------------------------------------
   
   file = new TFile(PATH_OUT, "RECREATE");

   histo = new TH1F*[3];

  
   histo[0] = new TH1F("ISR1", "ISR1", intervallix, minx, maxx);
   histo[0]->GetXaxis()->SetTitle("Calorimeter Isolation [GeV]");
   histo[0]->GetYaxis()->SetTitle("Number of events");
   histo[0]->GetXaxis()->CenterTitle();
   histo[0]->GetYaxis()->CenterTitle();

   histo[1] = new TH1F("ISR2", "ISR2", intervallix, minx, maxx);
   histo[1]->GetXaxis()->SetTitle("Calorimeter Isolation [GeV]");
   histo[1]->GetYaxis()->SetTitle("Number of events");
   histo[1]->GetXaxis()->CenterTitle();
   histo[1]->GetYaxis()->CenterTitle();

   histo[2] = new TH1F("ISR3", "ISR3", intervallix, minx, maxx);
   histo[2]->GetXaxis()->SetTitle("Calorimeter Isolation [GeV]");
   histo[2]->GetYaxis()->SetTitle("Number of events");
   histo[2]->GetXaxis()->CenterTitle();
   histo[2]->GetYaxis()->CenterTitle();



   
   

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



   //eventi totali
   ++NumberOfEvents;

   //Zee
   //if(*run != 364502 && *run != 364503 && *run != 364504) return kFALSE;

   //Zmumu
   //if(*run != 364507 && *run != 364508 && *run != 364509) return kFALSE;

   //Ztautau
   //if(*run != 364512 && *run != 364513 && *run != 364514) return kFALSE;

   //Znunu
   //if(*run != 364517 && *run != 364518 && *run != 364519) return kFALSE;

   //Wenu
   //if(*run != 364523 && *run != 364524 && *run != 364525) return kFALSE;

   //Wmunu
   //if(*run != 364528 && *run != 364529 && *run != 364530) return kFALSE;

   //Wtaunu
   //if(*run != 364533 && *run != 364534 && *run != 364535) return kFALSE;



   //________________SIGNAL_REGION________________

   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {

      if(*trigger_HLT_g140_loose==1) {
         ++N_trigger;

         if(*met_tst_et>150000.) {
            ++N_met_tst_et;

            //if(ph_pt[i]<180000.)
            if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52)) {
               ++N_ph_pt;

               if(*met_tst_sig_old>8.5) {
                  ++N_met_tst_sig_old;

                  if(fabs(ph_met_wmuon_dphi[i]) > 0.4) {
                     ++N_ph_met_dphi;
                                                
                     if(fabs(ph_ZVtx[i])<250.) {
                        ++N_ph_ZVtx;

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet)) {
                           ++N_jet_veto;

                           if(*n_el_baseline==0 && *n_mu_baseline==0) {
                              ++N_lepton_veto;

                              if( ph_truth_type[i] == 13 )  FillGraphs(histo, i, *met_tst_et);

                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

/*
   //________________1MuCR________________   

   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {
      
      if(*trigger_HLT_g140_loose==1)
      
         if(*met_nomuon_tst_et>150000.)

            //if(ph_pt[i]<180000.)
            if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52)) 
      
               if(fabs(ph_met_nomuon_dphi[i]) > 0.4) 
      
                  if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet)) 
      
                     if(*n_el_baseline==0 && *n_mu==1 && *n_mu_baseline==1)
      
                        if( ph_truth_type[i] == 13 )  FillGraphs(histo, i, *met_nomuon_tst_et);
                        
   }

*/
   //________________2MuCR________________   
   
   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {
   
      if(*trigger_HLT_g140_loose==1)

         if(*met_nomuon_tst_et>150000.)    
            
               //if(ph_pt[i]<180000.)
               if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52)) 

                     if(fabs(ph_met_nomuon_dphi[i]) > 0.4) 

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet)) 

                           if(*n_el_baseline==0 && *n_mu==2 && *mumu_m>10000 && *n_mu_baseline==2) 

                              if( ph_truth_type[i] == 13 )  FillGraphs(histo, i, *met_nomuon_tst_et);
                           
   }

   //________________2EleCR________________   

   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {

      if(*trigger_HLT_g140_loose==1) 

         if(*met_noelectron_tst_et>150000.) 
               
               //if(ph_pt[i]<180000.)
               if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52)) 

                     if(fabs(ph_met_noele_dphi[i]) > 0.4) 

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet)) 

                           if(*n_mu_baseline==0 && *n_el==2 && *ee_m>10000 && *n_el_baseline==2) 

                              if( ph_truth_type[i] == 13 )  FillGraphs(histo, i, *met_noelectron_tst_et);
                           
   }
/*
    //________________gammaJetCR________________   

   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {

      if(*trigger_HLT_g140_loose==1) 

         if(*met_tst_et > 85000. && *met_tst_et<110000) 
            
               //if(ph_pt[i]<180000.)
               if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52)) 

                     if(fabs(ph_met_wmuon_dphi[i])>0.4 && fabs(ph_met_wmuon_dphi[i])<3) 

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet))

                           if(*n_el_baseline==0 && *n_mu_baseline==0) 

                              FillGraphs(gammaJetCR_H, i);
                           
   }

*/

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
 
   //stampo i dati


   cout << endl;
   cout << "____________________________________________________" << endl << endl;
   cout << "               Cutflow" << endl;
   cout << "____________________________________________________" << endl << endl;
   cout << "            Totale  " << NumberOfEvents << endl;
   cout << "           trigger  " << N_trigger << endl;
   cout << "               MET  " << N_met_tst_sig_old << endl;
   cout << "  MET significance  " << N_met_tst_sig_old << endl;
   cout << "                pt  " << N_ph_pt << endl;
   cout << "           MET dphi " << N_ph_met_dphi << endl;
   cout << "          z-vertex  " << N_ph_ZVtx << endl;
   cout << "          jet veto  " << N_jet_veto << endl;
   cout << "       lepton veto  " << N_lepton_veto << endl;
   //cout << "         tight-iso  " << N_TightIso << endl;
   cout << "____________________________________________________" << endl << endl;
   cout << endl;

   //gStyle->SetOptStat(0);


   //histo->Draw("hist");


   file->Write();




}




void SelectorABCD::FillGraphs(TH1F **g, int i, Float_t met) {


   Eiso = (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45);  //In GeV
   float Etrack = ph_ptcone20[i]/ph_pt[i];
   


   if(pesati) {
      if(*mconly_weight > 100.)  weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
      if(*mconly_weight < -100.) weight = -1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
      else weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;
   }
   if(!pesati)weight = 1.;

   if(*xSec_SUSY>500.) weight=0.;

   
   //if ( Eiso > 3. )
      if (met > 150000.)
         g[0]->Fill(Eiso , weight);
      if (met > 225000.)
         g[1]->Fill(Eiso , weight);
      if (met > 300000.)
         g[2]->Fill(Eiso , weight);

   
/*   //ISR1
   if (met > 150000.) {
      
      if (ph_isTight[i])                               g[0] -> Fill(xbin, bin_tight-1, weight);
      if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[0] -> Fill(xbin, bin_tight3-1, weight);
      if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[0] -> Fill(xbin, bin_tight4-1, weight);
      if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[0] -> Fill(xbin, bin_tight5-1, weight);
      if (!ph_isTight[i])                              g[0] -> Fill(xbin, bin_nottight-1, weight);
   }

   //ISR2
   if(met > 225000.) {
      if (ph_isTight[i])                               g[1] -> Fill(xbin, bin_tight-1, weight);
      if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[1] -> Fill(xbin, bin_tight3-1, weight);
      if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[1] -> Fill(xbin, bin_tight4-1, weight);
      if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[1] -> Fill(xbin, bin_tight5-1, weight);
      if (!ph_isTight[i])                              g[1] -> Fill(xbin, bin_nottight-1, weight);
   }

   //ISR3
   if(met > 300000.) {
      if (ph_isTight[i] )                              g[2] -> Fill(xbin, bin_tight-1, weight);
      if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[2] -> Fill(xbin, bin_tight3-1, weight);
      if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[2] -> Fill(xbin, bin_tight4-1, weight);
      if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[2] -> Fill(xbin, bin_tight5-1, weight);
      if (!ph_isTight[i])                              g[2] -> Fill(xbin, bin_nottight-1, weight);
   }

   //ESR1
   if(met < 225000. && met > 150000.) {
      if (ph_isTight[i])                               g[3] -> Fill(xbin, bin_tight-1, weight);
      if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[3] -> Fill(xbin, bin_tight3-1, weight);
      if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[3] -> Fill(xbin, bin_tight4-1, weight);
      if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[3] -> Fill(xbin, bin_tight5-1, weight);
      if (!ph_isTight[i])                              g[3] -> Fill(xbin, bin_nottight-1, weight);
   }

   //ESR2
   if(met < 300000. && met > 225000.) {
      if (ph_isTight[i] )                              g[4] -> Fill(xbin, bin_tight-1, weight);
      if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[4] -> Fill(xbin, bin_tight3-1, weight);
      if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[4] -> Fill(xbin, bin_tight4-1, weight);
      if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[4] -> Fill(xbin, bin_tight5-1, weight);
      if (!ph_isTight[i])                              g[4] -> Fill(xbin, bin_nottight-1, weight);
   }
 */  

}

//overload per la gammaJetCR
void SelectorABCD::FillGraphs(TH1F *g, int i) {



   Eiso = (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45);  //In GeV


   
}

