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


   limit = new float[4];
   limit[0] = 150000.;
   limit[1] = 225000.;
   limit[2] = 300000.;
   limit[3] = 2000000.;
   
   slice = new Float_t*[3];
   for (int i = 0; i < 3; i++) {
      
      slice[i] = new Float_t[4];
      
      for (int j = 0; j < 4; j++)
         slice[i][j] = 0.;
   }


/*   intervalli = 24;
   float min = -40.;
   float max = 200.;

   
   file = new TFile(("root_files_MET/test/" + process + "_Ecalo.root").c_str(), "RECREATE");

   slice_endcap = new TH1F*[3];
   slice_barrel = new TH1F*[3];


   for (int i = 0; i < 3; i++) {
      //int i = 0;
      slice_endcap[i] = new TH1F(("slice" + to_string(i+1) + "_endcap").c_str(), ("slice" + to_string(i+1) + "_endcap").c_str(), intervalli, min, max);
      slice_endcap[i]->GetXaxis()->SetTitle("Calorimetric Isolation [GeV]");
      slice_endcap[i]->GetXaxis()->CenterTitle();
      slice_endcap[i]->GetYaxis()->SetTitle("Number of events");
      slice_endcap[i]->GetYaxis()->CenterTitle();

   }

   for (int i = 0; i < 3; i++) {

      slice_barrel[i] = new TH1F(("slice" + to_string(i+1) + "_barrel").c_str(), ("slice" + to_string(i+1) + "_barrel").c_str(), intervalli, min, max);
      slice_barrel[i]->GetXaxis()->SetTitle("Calorimetric Isolation [GeV]");
      slice_barrel[i]->GetXaxis()->CenterTitle();
      slice_barrel[i]->GetYaxis()->SetTitle("Number of events");
      slice_barrel[i]->GetYaxis()->CenterTitle();

   }
   
*/


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

   for (int i = 0, n = ph_pt.GetSize(); i < n; ++i) { 

      /*if( ph_truth_type[i] != 13 ) return kFALSE;


      if(*mconly_weight > 100.)  weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
      if(*mconly_weight < -100.) weight = -1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
      else weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;


      float Ecalo = (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45);  //In GeV
      float track = ph_ptcone20[i]/ph_pt[i];

      

      //if ( ph_isTight[i] )
      //if ( track < 0.05 )
      //if ( Ecalo < 0. )
      //if ( *met_tst_sig_old > 8.5 )
      //if ( fabs(ph_met_wmuon_dphi[i]) > 0.4 )
      if (  *trigger_HLT_g140_loose==1 &&
            ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52) &&
            *met_tst_sig_old>8.5 &&
            fabs(ph_met_wmuon_dphi[i]) > 0.4 &&
            fabs(ph_ZVtx[i])<250. )
      {

         //slice_endcap->Fill(ph_pt[i]/1E3, weight);
         
         //if (abs(ph_eta2[i]) > 1.56 && abs(ph_eta2[i]) < 2.37) {
            
            for (int j = 0; j < 3; j++) {

               if (*met_tst_et > limit[j] && *met_tst_et < limit[j+1])
                  slice_endcap[j]->Fill(Ecalo, weight);
            
            }

         //}

         
         if (abs(ph_eta2[i]) < 1.37) {
            
            for (int j = 0; j < 3; j++) {

               if (*met_tst_et > limit[j] && *met_tst_et < limit[j+1])
                  //slice_barrel[j]->Fill(Ecalo, weight);
            
            }
            
         }

      }

      number_of_events++;

      if (true) {
         if (ph_pdgId.GetSize() == 0 || ph_mother_pdgId.GetSize() == 0) {events_fail_pdgId++; return kFALSE;}
      }

      if (true) {

         if (true) {
            if ( !(ph_pdgId[i] == 22 && abs(ph_mother_pdgId[i])<100) ) { 
               events_fail_selection++;
               return kFALSE;
            }

         }

         else if (ph_truth_type[i] != 13) return kFALSE;

      }
      /*if (true) {

         if ( !(abs(ph_pdgId[i]) != 11 && (ph_pdgId[i] != 22 || (ph_pdgId[i] == 22 && abs(ph_mother_pdgId[i])>100))) )    return kFALSE;
         // if( ph_truth_type[i] != 0 && ph_truth_type[i] != 16 && ph_truth_type[i] != 17 ) return kFALSE;
      
      }



      for (int j = 0; j < 3; j++) 

         if (ph_pt[i] > limit[j] && ph_pt[i] < limit[j+1]) 

            fill_matrices(slice[j], i);*/
              

      number_of_events++;
      
      if (ph_pdgId.GetSize() == 0) {
      
         events_fail_mother_pdgId++;
         return kFALSE;

      }

      if (ph_mother_pdgId.GetSize() == 0) {
      
         events_fail_mother_pdgId++;
         return kFALSE;

      }

      if ( !(ph_pdgId[i] == 22 && abs(ph_mother_pdgId[i])<100) ) {

         events_fail_selection++;
         return kFALSE;
      }
         
            

   
   }

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
 

   //gStyle->SetOptStat(0);


   //file->Write();
   /*Float_t Na, Nb, Ma, Mb, R, sigma_R, c1, sigma_c1;

   for (int i = 0; i < 3; i++) {

      Na = slice[i][0];
      Nb = slice[i][1];
      Ma = slice[i][2];
      Mb = slice[i][3];

      if( Na > 0. && Nb > 0.) {

         c1 = Nb / Na;
         sigma_c1 = c1 * sqrt((1./Na) + (1./Nb));

      } else {c1 = 0.; sigma_c1 = 0.;}


      if( Na > 0. && Nb > 0. && Ma > 0. && Mb > 0.) {

         R = (Na*Mb)/(Nb*Ma);
         sigma_R = R * sqrt((1./Na) + (1./Nb) + (1./Ma) + (1./Mb));

      } else {R = 0.; sigma_R = 0.;}

      cout << endl;
      // cout << setprecision(8);

      cout << "slice " << i << endl;
      cout << "c1 = " << c1 << endl;
      cout << "sigma_c1 = " << sigma_c1 << endl;
      cout << "R = " << R << endl;
      cout << "sigma_R = " << sigma_R << endl;
      cout << endl;
   }*/

   cout << "total events     : " << number_of_events << endl;
   cout << "fail pdgId       : " << events_fail_pdgId << "\t" << 100.*float(events_fail_pdgId)/float(number_of_events) << endl;
   cout << "fail mother_pdgId: " << events_fail_mother_pdgId << "\t" << 100.*float(events_fail_mother_pdgId)/float(number_of_events) << endl;

   cout << "fail selection   : " << events_fail_selection << "\t" << 100.*float(events_fail_selection)/float(number_of_events) << endl;
   


}


void SelectorABCD::fill_matrices(Float_t *mat, int i)

{

   if(*mconly_weight >  100.)       weight =  1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else if(*mconly_weight < -100.)  weight = -1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else                             weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;

   if(*xSec_SUSY>500.) weight = 0.;

   calo_isolation  = (ph_topoetcone40[i]/1E3) - (0.022*(ph_pt[i]/1E3)+2.45);  //In GeV
   track_isolation = ph_ptcone20[i]/ph_pt[i];


   if (calo_isolation < 0. && track_isolation < 0.05) {
      
      if (ph_isTight[i])                              mat[0] += weight;
      if (!(ph_isEM[i] & tight4) && !ph_isTight[i])   mat[2] += weight;
   }

   if ((calo_isolation  > 3. && calo_isolation < 140. && track_isolation < 2.) ||
       (calo_isolation <= 3. && track_isolation > 0.10 && track_isolation < 2.)) {
      
      if (ph_isTight[i])                              mat[1] += weight;
      if (!(ph_isEM[i] & tight4) && !ph_isTight[i])   mat[3] += weight;
      
   }

}

