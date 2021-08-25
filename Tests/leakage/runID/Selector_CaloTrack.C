#define Selector_CaloTrack_cxx
// The class definition in Selector_CaloTrack.h has been generated automatically
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
// root> T->Process("Selector_CaloTrack.C")
// root> T->Process("Selector_CaloTrack.C","some options")
// root> T->Process("Selector_CaloTrack.C+")
//


#include <Selector_CaloTrack.h>
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
#include <cstring>
#define PATH_OUT "dati.txt"

int point_number = 0;
int run_ID = 364535;


using namespace std;

void Selector_CaloTrack::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   
   track_limit = 0.1;



   SR = new Float_t*[5];
   oneMuCR = new Float_t*[5];
   twoMuCR = new Float_t*[5];
   twoECR = new Float_t*[5];


   for (int i = 0; i < 5; i++) {
      
      SR[i] = new Float_t[4];
      oneMuCR[i] = new Float_t[4];
      twoMuCR[i] = new Float_t[4];
      twoECR[i] = new Float_t[4];

      

      for (int k = 0; k < 4; k++) {
         
         SR[i][k] = 0.;
         oneMuCR[i][k] = 0.;
         twoMuCR[i][k] = 0.;
         twoECR[i][k] = 0.;
      
      }
   
   

   }


   gammaJetCR = new Float_t[4];

   
   for (int k = 0; k < 4; k++)
         gammaJetCR[k] = 0.;


   regions = new string[5];
   CR = new string[5];
   mat = new Float_t**[4];

   
   

}

void Selector_CaloTrack::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();

}

Bool_t Selector_CaloTrack::Process(Long64_t entry)
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

   if (*run != run_ID) return kFALSE;
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

                              if( ph_truth_type[0] == 13 )  FillGraphs(SR, i, *met_tst_et, 0);

                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

   //________________1MuCR________________   

   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {
      
      if(*trigger_HLT_g140_loose==1)
      
         if(*met_nomuon_tst_et>150000.)

            //if(ph_pt[i]<180000.)
            if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52)) 
      
               if(fabs(ph_met_nomuon_dphi[i]) > 0.4) 
      
                  if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet)) 
      
                     if(*n_el_baseline==0 && *n_mu==1 && *n_mu_baseline==1)
      
                        if( ph_truth_type[0] == 13 )  FillGraphs(oneMuCR, i, *met_nomuon_tst_et, 1);
                        
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

                              if( ph_truth_type[0] == 13 )  FillGraphs(twoMuCR, i, *met_nomuon_tst_et, 2);
                           
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

                              if( ph_truth_type[0] == 13 )  FillGraphs(twoECR, i, *met_noelectron_tst_et, 3);
                           
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

                              if( ph_truth_type[0] == 13 )  FillGraphs(gammaJetCR, i);
                           
   }



   return kTRUE;
}

void Selector_CaloTrack::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_CaloTrack::Terminate()
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




   regions[0] = "ISR1";
   regions[1] = "ISR2";
   regions[2] = "ISR3";
   regions[3] = "ESR1";
   regions[4] = "ESR2";

   CR[0] = "SR";
   CR[1] = "1muCR";
   CR[2] = "2muCR";
   CR[3] = "2eCR";
   CR[4] = "gammajetCR";

   mat[0] = SR;
   mat[1] = oneMuCR;
   mat[2] = twoMuCR;
   mat[3] = twoECR;




   ofstream out;
   out.open(PATH_OUT);

   for (int i = 0; i < 4; i++) {

      out << CR[i] << ":" << endl;
      
      for (int j = 0; j < 5; j++) {
      
         out << "  " << regions[j] << ":" << endl;   
         out << "    " << "Na: " << mat[i][j][0] << endl;
         out << "    " << "Nb: " << mat[i][j][1] << endl;
         out << "    " << "Ma: " << mat[i][j][2] << endl; 
         out << "    " << "Mb: " << mat[i][j][3] << endl;
         
      }
   }

   out << CR[4] << ":" << endl;
   out << "  " << "Na: " << gammaJetCR[0] << endl;
   out << "  " << "Nb: " << gammaJetCR[1] << endl;
   out << "  " << "Ma: " << gammaJetCR[2] << endl; 
   out << "  " << "Mb: " << gammaJetCR[3] << endl;




   out.close();

}




void Selector_CaloTrack::FillGraphs(Float_t** g, int i, Float_t met, int region) {

   
   Ecalo = (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45);  //In GeV
   Etrack = ph_ptcone20[i]/ph_pt[i];
   
   if(*mconly_weight > 100.)  weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else if(*mconly_weight < -100.) weight = -1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;


   //ISR1
   if (met > 150000.) {

   
      // tight iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( ph_isTight[i] ) 
            g[0][0] += weight;

      // tight non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( ph_isTight[i] ) 
            g[0][1] += weight;

      // tight-4 iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[0][2] += weight;

      // tight-4 non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[0][3] += weight;

      
   
   }
   //ISR2
   if(met > 225000.) {


      // tight iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( ph_isTight[i] ) 
            g[1][0] += weight;

      // tight non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( ph_isTight[i] ) 
            g[1][1] += weight;

      // tight-4 iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[1][2] += weight;

      // tight-4 non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[1][3] += weight;

      

   }

   //ISR3
   if(met > 300000.) {

      
      // tight iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( ph_isTight[i] ) 
            g[2][0] += weight;

      // tight non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( ph_isTight[i] ) 
            g[2][1] += weight;

      // tight-4 iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[2][2] += weight;

      // tight-4 non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[2][3] += weight;

      

   }

   //ESR1
   if(met < 225000. && met > 150000.) {

      
      // tight iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( ph_isTight[i] ) 
            g[3][0] += weight;

      // tight non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( ph_isTight[i] ) 
            g[3][1] += weight;

      // tight-4 iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[3][2] += weight;

      // tight-4 non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[3][3] += weight;

      

   }

   //ESR2
   if(met < 300000. && met > 225000.) {

      
      // tight iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( ph_isTight[i] ) 
            g[4][0] += weight;

      // tight non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( ph_isTight[i] ) 
            g[4][1] += weight;

      // tight-4 iso
      if ( Ecalo < 0. && Etrack < 0.05 ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[4][2] += weight;

      // tight-4 non iso
      if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
         if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
            g[4][3] += weight;

      }

   

}

//overload per la gammaJetCR
void Selector_CaloTrack::FillGraphs(Float_t* g, int i) {



   Ecalo = (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45);  //In GeV
   Etrack = ph_ptcone20[i]/ph_pt[i];

   if(*mconly_weight > 100.)  weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else if(*mconly_weight < -100.) weight = -1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;


   
   // tight iso
   if ( Ecalo < 0. && Etrack < 0.05 ) 
      if ( ph_isTight[i] ) 
         g[0] += weight;

   // tight non iso
   if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
      if ( ph_isTight[i] ) 
         g[1] += weight;

   // tight-4 iso
   if ( Ecalo < 0. && Etrack < 0.05 ) 
      if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
         g[2] += weight;

   // tight-4 non iso
   if ( Ecalo > 3. || ( Ecalo < 0. && Etrack > track_limit ) ) 
      if ( !(ph_isEM[i] & tight4) && !ph_isTight[i] ) 
         g[3] += weight;

   
   

}







