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
#include <TCanvas.h>
#include <TTreeReader.h>
#include <cmath>
#include <fstream>
#include <TTree.h>
#include <TBranch.h>


using namespace std;

void SelectorABCD::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   N_SR = new Int_t[4];       //Na Nb Ma Mb
   SR = new Int_t*[5];
   oneMuCR = new Int_t*[5];
   twoMuCR = new Int_t*[5];
   twoECR = new Int_t*[5];

   for(int i=0; i<5; i++)  {
      SR[i] = new Int_t[4];
      oneMuCR[i] = new Int_t[4];
      twoMuCR[i] = new Int_t[4];
      twoECR[i] = new Int_t[4];
   }
   
   //azzero i contatori per i calcoli delle regioni di segnale e di controllo

   for(int i=0; i<4; i++)     N_SR[i]=0;

   for(int i=0; i<5; i++) {
      for(int j=0; j<4; j++) {
         SR[i][j] = 0;
         oneMuCR[i][j] = 0;
         twoMuCR[i][j] = 0;
         twoECR[i][j] = 0;
      }
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


   //eventi totali
   ++NumberOfEvents;

   //___________________________________________________________________________TRIGGER__
      
   if(*trigger_HLT_g140_loose==1)   ++N_trigger;
   else return kFALSE;

   //___________________________________________________________________________MET__
      
   if(*met_tst_et>150000.)   ++N_met_tst_et;
   else return kFALSE;

   //___________________________________________________________________________PT__

   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {

      if(ph_pt[i]>150000. && fabs(ph_eta2[i])<2.37 && 
         (fabs(ph_eta2[i])<1.37 || fabs(ph_eta2[i])>1.52))   ++N_ph_pt;
         else return kFALSE;
   }

   //___________________________________________________________________________MET_SIGNIFICANCE__
   
   if(*met_tst_sig_old>8.5)   ++N_met_tst_sig_old;
   else return kFALSE;

   //___________________________________________________________________________PH_MET_DPHI__
   
   for (int i = 0, n =  ph_met_wmuon_dphi.GetSize(); i < n; ++i) {

      if(fabs(ph_met_wmuon_dphi[i]) > 0.4)      ++N_ph_met_dphi;
      else return kFALSE;
   }

   //___________________________________________________________________________PH_POINTING(Z)__

   for (int i = 0, n =  ph_ZVtx.GetSize(); i < n; ++i) {

      if(fabs(ph_ZVtx[i])<250.)   ++N_ph_ZVtx;
      else return kFALSE;
   }

   //___________________________________________________________________________JET_VETO__

   if(*n_jet==0 ||(*n_jet==1 && *n_jet_good==*n_jet))   ++N_jet_veto;
   else return kFALSE;
   
   //___________________________________________________________________________LEPTON_VETO__
/*   
   if(*n_el_baseline==0 && *n_mu_baseline==0)    ++N_lepton_veto;
   else return kFALSE;
*/
   

   //___________________________________________________________________________TIGHTNESS__
   
   //DA SISTEMARE
   
   for (int i = 0, n =  ph_isEM.GetSize(); i < n; ++i) {

      if (!(ph_isEM[i] & tight3) && ph_isTight[i]!=1 ) N_tight_3++;
      if (!(ph_isEM[i] & tight4) && ph_isTight[i]!=1 ) N_tight_4++;
      if (!(ph_isEM[i] & tight5) && ph_isTight[i]!=1 ) N_tight_5++;
   
   }
   
/*
   for (int i = 0, n =  ph_isTight.GetSize(); i < n; ++i) {
   
      if(ph_isTight[i]==1)      ++N_ph_isTight;
      else return kFALSE;
   }

   //___________________________________________________________________________ISOLATION__

   for (int i = 0, n =  ph_pt.GetSize(); i < n; ++i) {


      if(ph_topoetcone40[i]/1000. < (0.022*(ph_pt[i]/1000.)+2.45) &&  ph_ptcone20[i]/ph_pt[i]<0.05)   ++N_ph_iso;
      else return kFALSE;
   }
*/

   //___________________________________________________________________________SIGNAL_AND_CONTROL_REGIONS__

   Calcola(N_SR);
   //carico le matrici con le popolazioni delle varie CR
   
   if( *n_el_baseline == 0 && *n_mu_baseline == 0 ) CalcolaCR(SR);
   /*
   if( *n_el == 0 && *n_mu == 1 ) CalcolaCR(oneMuCR);
   if( *n_el == 0 && *n_mu == 2 ) CalcolaCR(twoMuCR);
   if( *n_el == 2 && *n_mu == 0 ) CalcolaCR(twoECR);
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


   cout << endl << endl;
   cout << "____________________________________________________" << endl << endl;
   cout << "               Cutflow" << endl;
   cout << "____________________________________________________" << endl << endl;
   cout << "            Totale  " << NumberOfEvents << endl;
   cout << "            trigger " << N_trigger << endl;
   cout << "  MET significance  " << N_met_tst_et << endl;
   cout << "                pt  " << N_ph_pt << endl;
   cout << "           MET dphi " << N_ph_met_dphi << endl;
   cout << "          z-vertex  " << N_ph_ZVtx << endl;
   cout << "          jet veto  " << N_jet_veto << endl;
   cout << "       lepton veto  " << N_lepton_veto << endl;
   cout << "         tightness  " << N_ph_isTight << endl;
   cout << "        isolamento  " << N_ph_iso << endl;
   cout << "____________________________________________________" << endl;
   cout << "____________________________________________________" << endl;
   cout << "tight-3\t\ttight-4\t\ttight-5" << endl;
   cout << N_tight_3 << "\t\t" << N_tight_4 << "\t\t" << N_tight_5 << endl;
   cout << "____________________________________________________" << endl;  
   cout << endl;
   cout << "SR" << endl;
   PrintMat(SR);
   cout << "1muCR" << endl;
   PrintMat(oneMuCR);
   cout << "2muCR" << endl;
   PrintMat(twoMuCR);
   cout << "2eCR" << endl;
   PrintMat(twoECR);



}

void SelectorABCD::CalcolaCR(Int_t **mat) {

   if(*met_tst_sumet > 150000.) Calcola(mat[0]);
   if(*met_tst_sumet > 225000.) Calcola(mat[1]);
   if(*met_tst_sumet > 300000.) Calcola(mat[2]);
   if(*met_tst_sumet < 225000. && *met_tst_sumet > 150000.) Calcola(mat[3]);
   if(*met_tst_sumet < 300000. && *met_tst_sumet > 225000.) Calcola(mat[4]);

}

void SelectorABCD::Calcola(Int_t *v) {

   for (int i = 0, n =  ph_isTight.GetSize(); i < n; ++i) {
      if(ph_isTight[i]==1) tight = true; else tight = false;
      if(ph_topoetcone40[i] < 2450. + 0.022*ph_pt[i]   &&    ph_ptcone20[i]/ph_pt[i] < 50.) iso = true; else iso = false;   
   }

   
   for (int i = 0, n =  ph_isTight.GetSize(); i < n; ++i) {
      if(tight && iso)        ++v[0];     //SR     Na  
      else if(tight && !iso)  ++v[1];     //CR1    Nb
      else if(!tight && iso)  ++v[2];     //CR2    Ma
      else if(!tight && !iso) ++v[3];     //CR3    Mb
   }

}

Float_t SelectorABCD::Purezza(Int_t *v) {
   // P = 1 - Nb*Ma/Na*Mb
   return 100.*(1.-(float(v[1]*v[2])/float(v[0]*v[3])));
}

void SelectorABCD::PrintMat(Int_t **mat){

   cout << "--------------------------------------------------------------------------------" << endl;
   cout << "       |  Na\t\tNb\t\tMa\t\tMb\t\tPurezza" << endl;
   cout << "--------------------------------------------------------------------------------" << endl;
   cout << " ISR1  |  " << mat[0][0] << "\t\t" << mat[0][1] << "\t\t" << mat[0][2] << "\t\t" << mat[0][3] << "\t\t"
        << Purezza(mat[0]) << "%" << endl;
   
   cout << " ISR2  |  " << mat[1][0] << "\t\t" << mat[1][1] << "\t\t" << mat[1][2] << "\t\t" << mat[1][3] << "\t\t"
        << Purezza(mat[1]) << "%" <<endl;
   
   cout << " ISR3  |  " << mat[2][0] << "\t\t" << mat[2][1] << "\t\t" << mat[2][2] << "\t\t" << mat[2][3] << "\t\t"
        << Purezza(mat[2]) << "%" <<endl;
   
   cout << " ESR1  |  " << mat[3][0] << "\t\t" << mat[3][1] << "\t\t" << mat[3][2] << "\t\t" << mat[3][3] << "\t\t"
        << Purezza(mat[3]) << "%" <<endl;
   
   cout << " ESR2  |  " << mat[4][0] << "\t\t" << mat[4][1] << "\t\t" << mat[4][2] << "\t\t" << mat[4][3] << "\t\t"
        << Purezza(mat[4]) << "%" <<endl;
   
   cout << "--------------------------------------------------------------------------------" << endl;
   cout << endl;

}


