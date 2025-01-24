#define SelectorMC_cxx
// The class definition in SelectorMC.h has been generated automatically
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
// root> T->Process("SelectorMC.C")
// root> T->Process("SelectorMC.C","some options")
// root> T->Process("SelectorMC.C+")
//


#include "SelectorMC.h"
#include <TH2.h>
#include <TStyle.h>

#include <fstream>
#include <cstring>


using namespace std;


void SelectorMC::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();


   read_parameters("selector_parameters.txt");

   create_matrices();


   // signal-background distinction
   if (sample == "Wgamma" || sample == "Zgamma" || sample == "Znunugamma" || sample == "gammajets_sig" )
      {signal = true;  background = false;}
      
   else if (sample == "Wjets" || sample == "Zjets" || sample == "gammajets_bkg" )
      {signal = false; background = true;}  

}

void SelectorMC::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t SelectorMC::Process(Long64_t entry)
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

   fReader.SetEntry(entry);




   // for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) 
   if (ph_pt.GetSize() != 0)
   {

      i = 0;

      //_______________switch on signal or background_______________

      if (ph_pdgId.GetSize() == 0 || ph_mother_pdgId.GetSize() == 0) return kFALSE;


      if (signal) {

         if ( !(ph_pdgId[i] == 22 && abs(ph_mother_pdgId[i])<100) ) {
            
            // checks also the subleading photon
            if( sample == "gammajets_sig" ) {
               
               if (ph_pt.GetSize() < 1) return kFALSE;
               i = 1;
               if ( !(ph_pdgId[i] == 22 && abs(ph_mother_pdgId[i])<100) )  return kFALSE;
            
            } else {return kFALSE;}

         }

      } else if (background) {

         if ( !(abs(ph_pdgId[i]) != 11 && (ph_pdgId[i] != 22 || (ph_pdgId[i] == 22 && abs(ph_mother_pdgId[i])>100))) ) {
               
            // checks also the subleading photon
            if( sample == "gammajets_bkg" ) {
               
               if (ph_pt.GetSize() < 1) return kFALSE;
               i = 1;
               if ( !(abs(ph_pdgId[i]) != 11 && (ph_pdgId[i] != 22 || (ph_pdgId[i] == 22 && abs(ph_mother_pdgId[i])>100))) )
                  return kFALSE;
            
            } else {return kFALSE;}

         }

      }





      //_______________selections for control regions_______________

      // SR
      if(*trigger_HLT_g140_loose==1)

         if(*met_tst_et > 150000.)

            if(ph_pt[i] > 150000. && fabs(ph_eta2[i]) < 2.37 && (fabs(ph_eta2[i]) < 1.37 || fabs(ph_eta2[i]) > 1.52))

               if(*met_tst_sig > 8.5)

                  if(fabs(ph_met_wmuon_dphi[i]) > 0.4)
                                                
                     if(fabs(ph_ZVtx[i]) < 250.)

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet))

                           if(*n_el_baseline==0 && *n_mu_baseline==0)
                              
                              select_met_bin(SR, i, *met_tst_et);


      // 1muCR
      if(*trigger_HLT_g140_loose==1)
      
         if(*met_nomuon_tst_et > 150000.)

            if(ph_pt[i] > 150000. && fabs(ph_eta2[i]) < 2.37 && (fabs(ph_eta2[i]) < 1.37 || fabs(ph_eta2[i]) > 1.52))
      
               if(fabs(ph_met_nomuon_dphi[i]) > 0.4)
      
                  if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet))
      
                     if(*n_el_baseline==0 && *n_mu==1 && *n_mu_baseline==1)
                        
                        select_met_bin(onemuCR, i, *met_nomuon_tst_et);


      // 2muCR
      if(*trigger_HLT_g140_loose==1)

         if(*met_nomuon_tst_et > 150000.)
            
               if(ph_pt[i] > 150000. && fabs(ph_eta2[i]) < 2.37 && (fabs(ph_eta2[i]) < 1.37 || fabs(ph_eta2[i]) > 1.52))

                     if(fabs(ph_met_nomuon_dphi[i]) > 0.4)

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet))

                           if(*n_el_baseline==0 && *n_mu==2 && *mumu_m > 10000. && *n_mu_baseline==2)

                              select_met_bin(twomuCR, i, *met_nomuon_tst_et);


      // 2eCR
      if(*trigger_HLT_g140_loose==1)

         if(*met_noelectron_tst_et > 150000.)
               
               if(ph_pt[i] > 150000. && fabs(ph_eta2[i]) < 2.37 && (fabs(ph_eta2[i]) < 1.37 || fabs(ph_eta2[i]) > 1.52))

                     if(fabs(ph_met_noele_dphi[i]) > 0.4)

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet))

                           if(*n_mu_baseline==0 && *n_el==2 && *ee_m > 10000. && *n_el_baseline==2)

                              select_met_bin(twoeCR, i, *met_noelectron_tst_et);


      // gammajetCR
      if(*trigger_HLT_g140_loose==1)

         if(*met_tst_et > 85000. && *met_tst_et < 110000.)
            
               if(ph_pt[i] > 150000. && fabs(ph_eta2[i]) < 2.37 && (fabs(ph_eta2[i]) < 1.37 || fabs(ph_eta2[i]) > 1.52))

                     if(fabs(ph_met_wmuon_dphi[i]) > 0.4 && fabs(ph_met_wmuon_dphi[i]) < 3.)

                        if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet))

                           if(*n_el_baseline==0 && *n_mu_baseline==0)

                              fill_matrices(gammajetCR, i);


   }



   return kTRUE;
}

void SelectorMC::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void SelectorMC::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.


   // write all data in .txt file to be imported in python script with yaml

   string control_region[5] = {"SR", "onemuCR", "twomuCR", "twoeCR", "gammajetCR"};

   string *met_region = new string[2*numberOfMetBins - 1];
   
   for (int l = 0; l < numberOfMetBins; l++)
      met_region[l] = "ISR" + to_string(l+1);

   for (int l = 0; l < numberOfMetBins - 1; l++) 
      met_region[l + numberOfMetBins] = "ESR" + to_string(l+1);


   
   Float_t ****data[4];
   data[0] = SR;
   data[1] = onemuCR;
   data[2] = twomuCR;
   data[3] = twoeCR;

   string tightness[5];
   tightness[bin_tight]    = "tight";
   tightness[bin_tight3]   = "tight3";
   tightness[bin_tight4]   = "tight4";
   tightness[bin_tight5]   = "tight5";
   tightness[bin_nottight] = "nottight";

   string isolation[3];
   isolation[0] = "up";
   isolation[1] = "iso";
   isolation[2] = "down";



   ofstream out("dati/txt files" + string(directory) + "/" + string(sample) + ".txt");

   for (int l = 0; l < 4; l++) {

      out << control_region[l] << ":" << endl;
      
      for (int j = 0; j < 2*numberOfMetBins - 1; j++) {

         out << "  " << met_region[j] << ":" << endl;

         for (int k = 0; k < 5; k++) {

            out << "    " << tightness[k] << ":" << endl;
            
            for (int n = 0; n < 3; n++) {

               out << "      " << isolation[n] << ":" << endl;
               out << "        Na:  " << data[l][j][k][n][0] << endl;
               out << "        Nb:  " << data[l][j][k][n][1] << endl;

            }

         }

      }

   }


   out << control_region[4] << ":" << endl;
      
   for (int k = 0; k < 5; k++) {

      out << "  " << tightness[k] << ":" << endl;

      for (int n = 0; n < 3; n++) {

         out << "    " << isolation[n] << ":" << endl;
         out << "      Na:  " << gammajetCR[k][n][0] << endl;
         out << "      Nb:  " << gammajetCR[k][n][1] << endl;

      }
      

   }


   out.close();

}


void SelectorMC::read_parameters(string file)

{

   ifstream input_variables;
   input_variables.open(file);


   Float_t parameter;
   static const std::streamsize max = std::numeric_limits<std::streamsize>::max();


   // MET divisions in MeV
   if (input_variables.ignore(max, '=') >> parameter)    numberOfMetBins = int(parameter);
   
   met_bins = new Float_t[numberOfMetBins];
   
   for (int l = 0; l < numberOfMetBins; l++)
      if (input_variables.ignore(max, '=') >> parameter)    met_bins[l] = Float_t(parameter);
   
   
   // tight selections bins
   if (input_variables.ignore(max, '=') >> parameter)    bin_tight    = int(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    bin_tight3   = int(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    bin_tight4   = int(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    bin_tight5   = int(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    bin_nottight = int(parameter);

   // isolation parameters
   calo_isolation_gap = new Float_t[3];
   if (input_variables.ignore(max, '=') >> parameter)    calo_isolation_max_iso      = Float_t(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    calo_isolation_gap[0]       = Float_t(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    calo_isolation_gap[1]       = Float_t(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    calo_isolation_gap[2]       = Float_t(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    calo_isolation_max_not_iso  = Float_t(parameter);
   
   track_isolation_gap = new Float_t[3];
   if (input_variables.ignore(max, '=') >> parameter)    track_isolation_max_iso     = Float_t(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    track_isolation_gap[0]      = Float_t(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    track_isolation_gap[1]      = Float_t(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    track_isolation_gap[2]      = Float_t(parameter);
   if (input_variables.ignore(max, '=') >> parameter)    track_isolation_max_not_iso = Float_t(parameter);

}


void SelectorMC::create_matrices()

{

   // create matrices and set to zero
   // 5 MET divisions, 5 tight selections, each isolated or not,
   // so the order to access the matrix elements is: MET, tightness, isolation

   // n ISRs + n-1 ESR
   int numberOfRegions = 2*numberOfMetBins - 1;

   SR      = new Float_t***[numberOfRegions];
   onemuCR = new Float_t***[numberOfRegions];
   twomuCR = new Float_t***[numberOfRegions];
   twoeCR  = new Float_t***[numberOfRegions];

   for (int l = 0; l < numberOfRegions; l++) {
      
      SR[l]      = new Float_t**[5];
      onemuCR[l] = new Float_t**[5];
      twomuCR[l] = new Float_t**[5];
      twoeCR[l]  = new Float_t**[5];

      for (int j = 0; j < 5; j++) {

         SR[l][j]      = new Float_t*[3];
         onemuCR[l][j] = new Float_t*[3];
         twomuCR[l][j] = new Float_t*[3];
         twoeCR[l][j]  = new Float_t*[3];

         for (int k = 0; k < 3; k++) {

            SR[l][j][k]      = new Float_t[2];
            onemuCR[l][j][k] = new Float_t[2];
            twomuCR[l][j][k] = new Float_t[2];
            twoeCR[l][j][k]  = new Float_t[2];

            for (int n = 0; n < 2; n++) {

               SR[l][j][k][n]      = 0.;
               onemuCR[l][j][k][n] = 0.;
               twomuCR[l][j][k][n] = 0.;
               twoeCR[l][j][k][n]  = 0.;

            }
         
         }

      }
   
   }

   gammajetCR = new Float_t**[5];

   for (int j = 0; j < 5; j++) {

      gammajetCR[j] = new Float_t*[3];

      for (int k = 0; k < 3; k++) {

         gammajetCR[j][k] = new Float_t[2];

         for (int n = 0; n < 2; n++)

            gammajetCR[j][k][n] = 0.;

      }

            

   }

}


void SelectorMC::select_met_bin(Float_t ****mat, int i, Float_t met)

{
      
   // ISR
   for (int j = 0; j < numberOfMetBins; j++) 
      if (met > met_bins[j]) 
         fill_matrices(mat[j], i);

   // ESR
   for (int j = 0; j < numberOfMetBins-1; j++)
      if (met > met_bins[j] && met < met_bins[j+1])
         fill_matrices(mat[j+numberOfMetBins], i);

}


void SelectorMC::fill_matrices(Float_t ***mat, int i)

{

   if(*mconly_weight >  100.)       weight =  1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else if(*mconly_weight < -100.)  weight = -1. * luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight) / *mc_weight_sum;
   else                             weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;


   if(*xSec_SUSY>500.) weight = 0.;

   calo_isolation  = (ph_topoetcone40[i]/1E3) - (0.022*(ph_pt[i]/1E3)+2.45);  //In GeV
   track_isolation = ph_ptcone20[i]/ph_pt[i];


   // NOMINAL

   for (int n = 0; n < 3; n++) {

      if (calo_isolation < calo_isolation_max_iso && track_isolation < track_isolation_max_iso) {
         
         if (ph_isTight[i])                              mat[bin_tight][n][0]    += weight;
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i])   mat[bin_tight3][n][0]   += weight;
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i])   mat[bin_tight4][n][0]   += weight;
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i])   mat[bin_tight5][n][0]   += weight;
         if (!ph_isTight[i])                             mat[bin_nottight][n][0] += weight;

      }

      if ((calo_isolation  > calo_isolation_max_iso + calo_isolation_gap[n] && calo_isolation < calo_isolation_max_not_iso && track_isolation < track_isolation_max_not_iso) ||
          (calo_isolation <= calo_isolation_max_iso + calo_isolation_gap[n] && track_isolation > track_isolation_max_iso + track_isolation_gap[n] && track_isolation < track_isolation_max_not_iso)) {
         
         if (ph_isTight[i])                              mat[bin_tight][n][1]    += weight;
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i])   mat[bin_tight3][n][1]   += weight;
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i])   mat[bin_tight4][n][1]   += weight;
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i])   mat[bin_tight5][n][1]   += weight;
         if (!ph_isTight[i])                             mat[bin_nottight][n][1] += weight;

      }

   }




   // TEST

   // if (track_isolation > 0.05) return kFALSE;

   /*for (int n = 0; n < 3; n++) {

      if (calo_isolation < calo_isolation_max_iso) {// && track_isolation < track_isolation_max_iso) {
         
         if (ph_isTight[i])                              mat[bin_tight][n][0]    += weight;
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i])   mat[bin_tight3][n][0]   += weight;
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i])   mat[bin_tight4][n][0]   += weight;
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i])   mat[bin_tight5][n][0]   += weight;
         if (!ph_isTight[i])                             mat[bin_nottight][n][0] += weight;

      }

      if ((calo_isolation  > calo_isolation_max_iso + calo_isolation_gap[n] && calo_isolation < calo_isolation_max_not_iso)) {// && track_isolation < track_isolation_max_not_iso) ||
          //(calo_isolation <= calo_isolation_max_iso + calo_isolation_gap[n])) {// && track_isolation > track_isolation_max_iso + track_isolation_gap[n] && track_isolation < track_isolation_max_not_iso)) {
         
         if (ph_isTight[i])                              mat[bin_tight][n][1]    += weight;
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i])   mat[bin_tight3][n][1]   += weight;
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i])   mat[bin_tight4][n][1]   += weight;
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i])   mat[bin_tight5][n][1]   += weight;
         if (!ph_isTight[i])                             mat[bin_nottight][n][1] += weight;

      }

   }*/

}



