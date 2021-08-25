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
#include <TLine.h>
#define PATH_OUT "eventi_non_pesati.root"
bool pesati = true;

int run_ID = 364155;

using namespace std;

void SelectorABCD::Begin(TTree * /*tree*/)
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
   
   file = new TFile(PATH_OUT, "RECREATE");

   
   SR_H = new TH2F*[5];
   oneMuCR_H = new TH2F*[5];
   twoMuCR_H = new TH2F*[5];
   twoECR_H = new TH2F*[5];

   SR_H[0] = new TH2F("SR - ISR1","SR - ISR1",intervallix,minx,maxx,intervalliy,miny,maxy);
   SR_H[1] = new TH2F("SR - ISR2","SR - ISR2",intervallix,minx,maxx,intervalliy,miny,maxy);
   SR_H[2] = new TH2F("SR - ISR3","SR - ISR3",intervallix,minx,maxx,intervalliy,miny,maxy);
   SR_H[3] = new TH2F("SR - ESR1","SR - ESR1",intervallix,minx,maxx,intervalliy,miny,maxy);
   SR_H[4] = new TH2F("SR - ESR2","SR - ESR2",intervallix,minx,maxx,intervalliy,miny,maxy);

   oneMuCR_H[0] = new TH2F("1muCR - ISR1","1#muCR - ISR1",intervallix,minx,maxx,intervalliy,miny,maxy);
   oneMuCR_H[1] = new TH2F("1muCR - ISR2","1#muCR - ISR2",intervallix,minx,maxx,intervalliy,miny,maxy);
   oneMuCR_H[2] = new TH2F("1muCR - ISR3","1#muCR - ISR3",intervallix,minx,maxx,intervalliy,miny,maxy);
   oneMuCR_H[3] = new TH2F("1muCR - ESR1","1#muCR - ESR1",intervallix,minx,maxx,intervalliy,miny,maxy);
   oneMuCR_H[4] = new TH2F("1muCR - ESR2","1#muCR - ESR2",intervallix,minx,maxx,intervalliy,miny,maxy);

   twoMuCR_H[0] = new TH2F("2muCR - ISR1","2#muCR - ISR1",intervallix,minx,maxx,intervalliy,miny,maxy);
   twoMuCR_H[1] = new TH2F("2muCR - ISR2","2#muCR - ISR2",intervallix,minx,maxx,intervalliy,miny,maxy);
   twoMuCR_H[2] = new TH2F("2muCR - ISR3","2#muCR - ISR3",intervallix,minx,maxx,intervalliy,miny,maxy);
   twoMuCR_H[3] = new TH2F("2muCR - ESR1","2#muCR - ESR1",intervallix,minx,maxx,intervalliy,miny,maxy);
   twoMuCR_H[4] = new TH2F("2muCR - ESR2","2#muCR - ESR2",intervallix,minx,maxx,intervalliy,miny,maxy);

   twoECR_H[0] = new TH2F("2eCR - ISR1","2eCR_H - ISR1",intervallix,minx,maxx,intervalliy,miny,maxy);
   twoECR_H[1] = new TH2F("2eCR - ISR2","2eCR_H - ISR2",intervallix,minx,maxx,intervalliy,miny,maxy);
   twoECR_H[2] = new TH2F("2eCR - ISR3","2eCR_H - ISR3",intervallix,minx,maxx,intervalliy,miny,maxy);
   twoECR_H[3] = new TH2F("2eCR - ESR1","2eCR_H - ESR1",intervallix,minx,maxx,intervalliy,miny,maxy);
   twoECR_H[4] = new TH2F("2eCR - ESR2","2eCR_H - ESR2",intervallix,minx,maxx,intervalliy,miny,maxy);

   gammaJetCR_H = new TH2F("gammajetCR","#gamma + jet CR",intervallix,minx,maxx,intervalliy,miny,maxy);

   gammaJetCR_H->GetXaxis()->SetTitle("E_{iso} [GeV]");
   gammaJetCR_H->GetXaxis()->CenterTitle();
   gammaJetCR_H->GetXaxis()->SetTitleOffset(1.6);
   gammaJetCR_H->GetYaxis()->SetBinLabel(bin_tight, "Tight");
   gammaJetCR_H->GetYaxis()->SetBinLabel(bin_tight3, "Tight-3");
   gammaJetCR_H->GetYaxis()->SetBinLabel(bin_tight4, "Tight-4");
   gammaJetCR_H->GetYaxis()->SetBinLabel(bin_tight5, "Tight-5");
   gammaJetCR_H->GetYaxis()->SetBinLabel(bin_nottight, "Not Tight");
   gammaJetCR_H->SetMinimum(0.);
   gammaJetCR_H->GetZaxis()->SetTitle("Number of events");
   gammaJetCR_H->GetZaxis()->SetTitleOffset(1.2);

   for(int i = 0; i < 4; i++) {

      SR_H[i]->SetMinimum(0.);
      oneMuCR_H[i]->SetMinimum(0.);
      twoMuCR_H[i]->SetMinimum(0.);
      twoECR_H[i]->SetMinimum(0.);

      SR_H[i]->GetXaxis()->SetTitle("E_{iso} [GeV]");
      oneMuCR_H[i]->GetXaxis()->SetTitle("E_{iso} [GeV]");
      twoMuCR_H[i]->GetXaxis()->SetTitle("E_{iso} [GeV]");
      twoECR_H[i]->GetXaxis()->SetTitle("E_{iso} [GeV]");

      SR_H[i]->GetXaxis()->CenterTitle();
      oneMuCR_H[i]->GetXaxis()->CenterTitle();
      twoMuCR_H[i]->GetXaxis()->CenterTitle();
      twoECR_H[i]->GetXaxis()->CenterTitle();

      SR_H[i]->GetXaxis()->SetTitleOffset(1.6);
      oneMuCR_H[i]->GetXaxis()->SetTitleOffset(1.6);
      twoMuCR_H[i]->GetXaxis()->SetTitleOffset(1.6);
      twoECR_H[i]->GetXaxis()->SetTitleOffset(1.6);

      SR_H[i]->GetYaxis()->SetBinLabel(bin_tight, "Tight");
      SR_H[i]->GetYaxis()->SetBinLabel(bin_tight3, "Tight-3");
      SR_H[i]->GetYaxis()->SetBinLabel(bin_tight4, "Tight-4");
      SR_H[i]->GetYaxis()->SetBinLabel(bin_tight5, "Tight-5");
      SR_H[i]->GetYaxis()->SetBinLabel(bin_nottight, "Not Tight");

      oneMuCR_H[i]->GetYaxis()->SetBinLabel(bin_tight, "Tight");
      oneMuCR_H[i]->GetYaxis()->SetBinLabel(bin_tight3, "Tight-3");
      oneMuCR_H[i]->GetYaxis()->SetBinLabel(bin_tight4, "Tight-4");
      oneMuCR_H[i]->GetYaxis()->SetBinLabel(bin_tight5, "Tight-5");
      oneMuCR_H[i]->GetYaxis()->SetBinLabel(bin_nottight, "Not Tight");

      twoMuCR_H[i]->GetYaxis()->SetBinLabel(bin_tight, "Tight");
      twoMuCR_H[i]->GetYaxis()->SetBinLabel(bin_tight3, "Tight-3");
      twoMuCR_H[i]->GetYaxis()->SetBinLabel(bin_tight4, "Tight-4");
      twoMuCR_H[i]->GetYaxis()->SetBinLabel(bin_tight5, "Tight-5");
      twoMuCR_H[i]->GetYaxis()->SetBinLabel(bin_nottight, "Not Tight");

      twoECR_H[i]->GetYaxis()->SetBinLabel(bin_tight, "Tight");
      twoECR_H[i]->GetYaxis()->SetBinLabel(bin_tight3, "Tight-3");
      twoECR_H[i]->GetYaxis()->SetBinLabel(bin_tight4, "Tight-4");
      twoECR_H[i]->GetYaxis()->SetBinLabel(bin_tight5, "Tight-5");
      twoECR_H[i]->GetYaxis()->SetBinLabel(bin_nottight, "Not Tight");

      SR_H[i]->GetZaxis()->SetTitle("Number of events");
      oneMuCR_H[i]->GetZaxis()->SetTitle("Number of events");
      twoMuCR_H[i]->GetZaxis()->SetTitle("Number of events");
      twoECR_H[i]->GetZaxis()->SetTitle("Number of events");

      SR_H[i]->GetZaxis()->SetTitleOffset(1.2);
      oneMuCR_H[i]->GetZaxis()->SetTitleOffset(1.2);
      twoMuCR_H[i]->GetZaxis()->SetTitleOffset(1.2);
      twoECR_H[i]->GetZaxis()->SetTitleOffset(1.2);

   }

   

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


   // selezione sulle slice
   if ( *run!=364155 ) return kFALSE;

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

                              FillGraphs(SR_H, i, *met_tst_et);

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
      
                        FillGraphs(oneMuCR_H, i, *met_nomuon_tst_et);
                        
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

                              FillGraphs(twoMuCR_H, i, *met_nomuon_tst_et);
                           
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

                              FillGraphs(twoECR_H, i, *met_noelectron_tst_et);
                           
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


   SR_H[0]->Draw("LEGO");


   file->Write();

}




void SelectorABCD::FillGraphs(TH2F **g, int i, Float_t met) {
   

   if (ph_ptcone20[i]/ph_pt[i]<0.05) {

      Eiso = (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45);  //In GeV

      if(pesati) weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;
      if(!pesati)weight = 1.;
      if(abs(*mconly_weight)>100.) weight=1.;
      
      //ISR1
      if (met > 150000.) {
         
         if (ph_isTight[i])                               g[0] -> Fill(Eiso, bin_tight-1, weight); //if(Eiso<0.) N_TightIso++;} 
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[0] -> Fill(Eiso, bin_tight3-1, weight);
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[0] -> Fill(Eiso, bin_tight4-1, weight);
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[0] -> Fill(Eiso, bin_tight5-1, weight);
         if (!ph_isTight[i])                              g[0] -> Fill(Eiso, bin_nottight-1, weight);
      }

      //ISR2
      if(met > 225000.) {
         if (ph_isTight[i])                               g[1] -> Fill(Eiso, bin_tight-1, weight);
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[1] -> Fill(Eiso, bin_tight3-1, weight);
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[1] -> Fill(Eiso, bin_tight4-1, weight);
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[1] -> Fill(Eiso, bin_tight5-1, weight);
         if (!ph_isTight[i])                              g[1] -> Fill(Eiso, bin_nottight-1, weight);
      }

      //ISR3
      if(met > 300000.) {
         if (ph_isTight[i] )                              g[2] -> Fill(Eiso, bin_tight-1, weight);
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[2] -> Fill(Eiso, bin_tight3-1, weight);
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[2] -> Fill(Eiso, bin_tight4-1, weight);
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[2] -> Fill(Eiso, bin_tight5-1, weight);
         if (!ph_isTight[i])                              g[2] -> Fill(Eiso, bin_nottight-1, weight);
      }

      //ESR1
      if(met < 225000. && met > 150000.) {
         if (ph_isTight[i])                               g[3] -> Fill(Eiso, bin_tight-1, weight);
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[3] -> Fill(Eiso, bin_tight3-1, weight);
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[3] -> Fill(Eiso, bin_tight4-1, weight);
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[3] -> Fill(Eiso, bin_tight5-1, weight);
         if (!ph_isTight[i])                              g[3] -> Fill(Eiso, bin_nottight-1, weight);
      }

      //ESR2
      if(met < 300000. && met > 225000.) {
         if (ph_isTight[i] )                              g[4] -> Fill(Eiso, bin_tight-1, weight);
         if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g[4] -> Fill(Eiso, bin_tight3-1, weight);
         if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g[4] -> Fill(Eiso, bin_tight4-1, weight);
         if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g[4] -> Fill(Eiso, bin_tight5-1, weight);
         if (!ph_isTight[i])                              g[4] -> Fill(Eiso, bin_nottight-1, weight);
      }
      
   
   }
}

//overload per la gammaJetCR
void SelectorABCD::FillGraphs(TH2F *g, int i) {

   if (ph_ptcone20[i]/ph_pt[i]<0.05) {

      Eiso = (ph_topoetcone40[i]/1000.) - (0.022*(ph_pt[i]/1000.)+2.45);  //In GeV

      if(pesati) weight = luminosity * (*xSec_SUSY * *k_factor * *filter_eff * *evsf_good_nominal_EL * *evsf_good_nominal_MU * *evsf_leading_nominal_PH * *pu_weight * *mconly_weight) / *mc_weight_sum;
      if(!pesati)weight = 1.;
      if(abs(*mconly_weight)>100.) weight=1.;

      if (ph_isTight[i])                               g -> Fill(Eiso, bin_tight-1, weight);
      if (!(ph_isEM[i] & tight3) && !ph_isTight[i] )   g -> Fill(Eiso, bin_tight3-1, weight);
      if (!(ph_isEM[i] & tight4) && !ph_isTight[i] )   g -> Fill(Eiso, bin_tight4-1, weight);
      if (!(ph_isEM[i] & tight5) && !ph_isTight[i] )   g -> Fill(Eiso, bin_tight5-1, weight);
      if (!ph_isTight[i])                              g -> Fill(Eiso, bin_nottight-1, weight);
   }  
   
}


