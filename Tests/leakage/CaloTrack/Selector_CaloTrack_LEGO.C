#define Selector_CaloTrack_LEGO_cxx
// The class definition in Selector_CaloTrack_LEGO.h has been generated automatically
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
// root> T->Process("Selector_CaloTrack_LEGO.C")
// root> T->Process("Selector_CaloTrack_LEGO.C","some options")
// root> T->Process("Selector_CaloTrack_LEGO.C+")
//


#include <Selector_CaloTrack_LEGO.h>
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
#define PATH_OUT "hist_Wgamma_1muCR.root"

bool pesati = true;


using namespace std;

void Selector_CaloTrack_LEGO::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   file = new TFile(PATH_OUT, "RECREATE");
   
   intervallix = 60;
   minx = -20.;
   maxx = 100.;
   intervalliy = 20;
   miny = 0.;
   maxy = 1.;

   CaloTrack = new TH2F("SR - ISR1","SR - ISR1",intervallix,minx,maxx,intervalliy,miny,maxy);

   //CaloTrack->SetTitle("W+jets 1muCR - ISR1");
   CaloTrack->GetXaxis()->SetTitle("Calorimetric Isolation");
   CaloTrack->GetXaxis()->CenterTitle();
   CaloTrack->GetYaxis()->SetTitle("Track Isolation");
   CaloTrack->GetYaxis()->CenterTitle();

   

   track_limit = 0.1;
   

}

void Selector_CaloTrack_LEGO::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();

}

Bool_t Selector_CaloTrack_LEGO::Process(Long64_t entry)
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

                              if( ph_truth_type[0] == 13 )  FillGraphs(i, *met_tst_et);

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
      
                        if( ph_truth_type[0] == 13 ) FillGraphs(i, *met_nomuon_tst_et);
                        
   }

   //________________2MuCR________________   
   
   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {
   
      if(*trigger_HLT_g140_loose==1)

         if(*met_nomuon_tst_et>150000.)    
            
               //if(ph_pt[i]<180000.)
               if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52)) 

                     if(fabs(ph_met_nomuon_dphi[i]) > 0.4) 

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet)) 

                           if(*n_el_baseline==0 && *n_mu==2 && *mumu_m>10000 && *n_mu_baseline==2) 

                              if( ph_truth_type[0] == 13 ) FillGraphs(i, *met_nomuon_tst_et);
                           
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

                              if( ph_truth_type[0] == 13 ) FillGraphs(i, *met_noelectron_tst_et);
                           
   }

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

void Selector_CaloTrack_LEGO::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_CaloTrack_LEGO::Terminate()
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
   cout << "                pt  " << N_ph_pt << endl;
   cout << "               MET  " << N_met_tst_et << endl;
   cout << "  MET significance  " << N_met_tst_sig_old << endl;
   cout << "          MET dphi  " << N_ph_met_dphi << endl;
   cout << "          z-vertex  " << N_ph_ZVtx << endl;
   cout << "          jet veto  " << N_jet_veto << endl;
   cout << "       lepton veto  " << N_lepton_veto << endl;
   //cout << "         tight-iso  " << N_TightIso << endl;
   cout << "____________________________________________________" << endl << endl;
   cout << endl;

   gStyle->SetOptStat(0);

   TCanvas *c1 = new TCanvas("c1");


   c1->cd();
   
   CaloTrack->Draw("LEGO");

   file->Write();


   cout << "SR" << endl;
   cout << "         iso: " << iso << endl;
   cout << "     not_iso: " << not_iso << endl;
   cout << "in_the_strip: " << in_the_strip << endl;

   cout << "seganale scartato: " << 100.*float(in_the_strip)/float(total) << " %" << endl << endl;




}




void Selector_CaloTrack_LEGO::FillGraphs(int i, Float_t met) {

   
   //if( (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45) < 0. &&  (ph_ptcone20[i]/ph_pt[i]) > 0.05){
   //   cout << "ph_isConv: " << ph_isConv[i] << endl;
   //}
   
   Ecalo = (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45);
   Etrack = (ph_ptcone20[i]/ph_pt[i]);
   

   if(met > 150000. && (Etrack > 0.1 || (Etrack < 0.1 && Ecalo > 3.))) {
   
      if(pesati) {
         if(*mconly_weight > 100.)  weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
         if(*mconly_weight < -100.) weight = -1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
         else weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;
      }
      if(!pesati)weight = 1.;

      if(*xSec_SUSY>500.) weight=0.;

      CaloTrack->Fill(Ecalo, Etrack, weight);


      //if (Etrack < 0.05)
         total++;

      if ( Ecalo < 0. && Etrack < 0.05 )
         iso++;

      if ( (Ecalo > 0. && Ecalo < 3. && Etrack < track_limit) || (Ecalo < 0. && Etrack > 0.05 && Etrack < track_limit) )
         in_the_strip++;

      if ( Ecalo > 3. || Etrack > track_limit )
         not_iso++;

   }



}

//overload per la gammaJetCR
void Selector_CaloTrack_LEGO::FillGraphs( int i) {

   
   
}







