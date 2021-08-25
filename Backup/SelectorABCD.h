//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar  7 14:44:34 2019 by ROOT version 6.14/04
// from TTree Wgamma/
// found on file: mc16a_Vgamma_gammajet_36.4fb.root
//////////////////////////////////////////////////////////


/* 
TAGLI

SR
Preselected: trigger_HLT_g140_loose
MET cut: met_tst_et>150000
ph cut: ph_pt>150000&&fabs(ph_eta2)<2.37 && (fabs(ph_eta2)<1.37 || fabs(ph_eta2)>1.52)
MET sig: met_tst_sig_old>8.5
Dphi(MET,ph): fabs(ph_met_dphi) > 0.4
Z vertex: fabs(ph_ZVtx<250)
jet veto: n_jet==0 ||(n_jet==1 && n_jet_good==n_jet)
lep veto: n_el_baseline==0 && n_mu_baseline==0"
tight ph: ph_isTight==1
isolation: ph_topoetcone40/1000. < (0.022*(ph_pt/1000)+2.45) &&
ph_ptcone20/ph_pt<0.05

Per le CR vanno eliminati i tagli in MET significance e Z vertex. Poi
bisogna sostituire alla met la met_nomu per le MuCR e la met_noelectron
per la 2EleCR, sia nel taglio di MET che in Dphi(MET,ph) (quindi dovrai
usare ph_met_nomuon_dphi o ph_met_noelectron_dphi). Infine bisogna
sostituire il lepton veto con
- 1MuCR n_el_baseline==0 && n_mu==1
- 2MuCR n_el_baseline==0 && n_mu==2 && mumu_m>10000
- 2EleCR n_mu_baseline==0 && n_el==2 && ee_m>10000

per le tightness-x sono a 1 le va variabili che non si vogliono controllare
(1,11,12,13,14,15,16 sono sempre a 1)

tight2 18,19,22
tight3 19,22
tight4 19
tight5 

da rivedere meglio

*/


// -------------- MASCHERE ---------------- //

#ifndef tight3
#define tight3 0x65fc01
#endif

#ifndef tight4
#define tight4 0x45fc01
#endif

#ifndef tight5
#define tight5 0x41fc01
#endif


#ifndef SelectorABCD_h
#define SelectorABCD_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <fstream>
// Headers needed by this particular selector
#include <vector>



class SelectorABCD : public TSelector {
public :
   TTreeReader    fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   /*TTreeReaderValue<Int_t> run = {fReader, "run"};
   TTreeReaderValue<ULong64_t> event = {fReader, "event"};
   TTreeReaderValue<Int_t> last = {fReader, "last"};
   TTreeReaderValue<Int_t> year = {fReader, "year"};
   
   
   TTreeReaderValue<Int_t> n_jet_preor = {fReader, "n_jet_preor"};
   TTreeReaderValue<Int_t> n_tau_preor = {fReader, "n_tau_preor"};
   TTreeReaderValue<Int_t> n_mu_preor = {fReader, "n_mu_preor"};
   TTreeReaderValue<Int_t> n_el_preor = {fReader, "n_el_preor"};
   TTreeReaderValue<Int_t> n_ph_preor = {fReader, "n_ph_preor"};
   
   TTreeReaderValue<Int_t> n_el_baseline = {fReader, "n_el_baseline"};
   TTreeReaderValue<Int_t> n_tau_baseline = {fReader, "n_tau_baseline"};
   TTreeReaderValue<Int_t> n_mu_baseline = {fReader, "n_mu_baseline"};
   TTreeReaderValue<Int_t> n_mu_baseline_bad = {fReader, "n_mu_baseline_bad"};
   TTreeReaderValue<Int_t> n_allmu_bad = {fReader, "n_allmu_bad"};
   TTreeReaderValue<Int_t> n_tau = {fReader, "n_tau"};
   TTreeReaderValue<Int_t> n_mu = {fReader, "n_mu"};
   TTreeReaderValue<Float_t> munu_mT = {fReader, "munu_mT"};
   TTreeReaderValue<Float_t> enu_mT = {fReader, "enu_mT"};
   TTreeReaderValue<Float_t> mumu_m = {fReader, "mumu_m"};
   TTreeReaderValue<Float_t> ee_m = {fReader, "ee_m"};
   TTreeReaderArray<float> mconly_weights = {fReader, "mconly_weights"};
   TTreeReaderValue<Float_t> pu_weight = {fReader, "pu_weight"};
   TTreeReaderValue<Float_t> jvt_weight = {fReader, "jvt_weight"};
   TTreeReaderValue<Float_t> jvt_all_weight = {fReader, "jvt_all_weight"};
   TTreeReaderArray<int> truth_W_decay = {fReader, "truth_W_decay"};
   TTreeReaderValue<Float_t> GenFiltMet = {fReader, "GenFiltMet"};
   TTreeReaderValue<Int_t> n_truthTop = {fReader, "n_truthTop"};
   TTreeReaderValue<Float_t> averageIntPerXing = {fReader, "averageIntPerXing"};
   TTreeReaderValue<Float_t> corAverageIntPerXing = {fReader, "corAverageIntPerXing"};
   TTreeReaderValue<Int_t> n_vx = {fReader, "n_vx"};
   TTreeReaderValue<Float_t> pu_hash = {fReader, "pu_hash"};
   TTreeReaderValue<Float_t> allmu_tot_SF = {fReader, "allmu_tot_SF"};
   TTreeReaderValue<Int_t> trigger_matched_electron = {fReader, "trigger_matched_electron"};
   TTreeReaderValue<Int_t> trigger_matched_muon = {fReader, "trigger_matched_muon"};
   TTreeReaderValue<Int_t> trigger_HLT_g140_loose = {fReader, "trigger_HLT_g140_loose"};
   TTreeReaderValue<Int_t> trigger_HLT_g160_loose = {fReader, "trigger_HLT_g160_loose"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100 = {fReader, "trigger_HLT_xe100"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_mht_L1XE50 = {fReader, "trigger_HLT_xe100_mht_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe110_mht_L1XE50 = {fReader, "trigger_HLT_xe110_mht_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe90_mht_L1XE50 = {fReader, "trigger_HLT_xe90_mht_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe90_tc_lcw_L1XE50 = {fReader, "trigger_HLT_xe90_tc_lcw_L1XE50"};
   TTreeReaderValue<Int_t> trigger_pass = {fReader, "trigger_pass"};
   TTreeReaderValue<Int_t> lbn = {fReader, "lbn"};
   TTreeReaderValue<Int_t> bcid = {fReader, "bcid"};
   TTreeReaderValue<Float_t> pdf_x1 = {fReader, "pdf_x1"};
   TTreeReaderValue<Float_t> pdf_x2 = {fReader, "pdf_x2"};
   TTreeReaderValue<Float_t> pdf_pdf1 = {fReader, "pdf_pdf1"};
   TTreeReaderValue<Float_t> pdf_pdf2 = {fReader, "pdf_pdf2"};
   TTreeReaderValue<Float_t> pdf_scale = {fReader, "pdf_scale"};
   TTreeReaderValue<Int_t> flag_bib = {fReader, "flag_bib"};
   TTreeReaderValue<Int_t> flag_bib_raw = {fReader, "flag_bib_raw"};
   TTreeReaderValue<Int_t> flag_sct = {fReader, "flag_sct"};
   TTreeReaderValue<Int_t> flag_core = {fReader, "flag_core"};
   TTreeReaderValue<Int_t> trigger_HLT_2e17_loose = {fReader, "trigger_HLT_2e17_loose"};
   TTreeReaderValue<Int_t> trigger_HLT_2mu14 = {fReader, "trigger_HLT_2mu14"};
   TTreeReaderValue<Int_t> trigger_HLT_3j175 = {fReader, "trigger_HLT_3j175"};
   TTreeReaderValue<Int_t> trigger_HLT_4j85 = {fReader, "trigger_HLT_4j85"};
   TTreeReaderValue<Int_t> trigger_HLT_e120_lhloose = {fReader, "trigger_HLT_e120_lhloose"};
   TTreeReaderValue<Int_t> trigger_HLT_e120_lhloose_nod0 = {fReader, "trigger_HLT_e120_lhloose_nod0"};
   TTreeReaderValue<Int_t> trigger_HLT_e140_lhloose_nod0 = {fReader, "trigger_HLT_e140_lhloose_nod0"};
   TTreeReaderValue<Int_t> trigger_HLT_e24_lhmedium_L1EM18VH = {fReader, "trigger_HLT_e24_lhmedium_L1EM18VH"};
   TTreeReaderValue<Int_t> trigger_HLT_e24_lhmedium_L1EM20VH = {fReader, "trigger_HLT_e24_lhmedium_L1EM20VH"};
   TTreeReaderValue<Int_t> trigger_HLT_e24_lhmedium_iloose_L1EM20VH = {fReader, "trigger_HLT_e24_lhmedium_iloose_L1EM20VH"};
   TTreeReaderValue<Int_t> trigger_HLT_e24_lhtight_iloose = {fReader, "trigger_HLT_e24_lhtight_iloose"};
   TTreeReaderValue<Int_t> trigger_HLT_e24_lhtight_nod0_ivarloose = {fReader, "trigger_HLT_e24_lhtight_nod0_ivarloose"};
   TTreeReaderValue<Int_t> trigger_HLT_e26_lhtight_ivarloose = {fReader, "trigger_HLT_e26_lhtight_ivarloose"};
   TTreeReaderValue<Int_t> trigger_HLT_e26_lhtight_nod0_ivarloose = {fReader, "trigger_HLT_e26_lhtight_nod0_ivarloose"};
   TTreeReaderValue<Int_t> trigger_HLT_e28_tight_iloose = {fReader, "trigger_HLT_e28_tight_iloose"};
   TTreeReaderValue<Int_t> trigger_HLT_e60_lhmedium = {fReader, "trigger_HLT_e60_lhmedium"};
   TTreeReaderValue<Int_t> trigger_HLT_e60_lhmedium_nod0 = {fReader, "trigger_HLT_e60_lhmedium_nod0"};
   TTreeReaderValue<Int_t> trigger_HLT_e60_medium = {fReader, "trigger_HLT_e60_medium"};
   TTreeReaderValue<Int_t> trigger_HLT_g120_loose = {fReader, "trigger_HLT_g120_loose"};
   TTreeReaderValue<Int_t> trigger_HLT_g300_etcut = {fReader, "trigger_HLT_g300_etcut"};
   TTreeReaderValue<Int_t> trigger_HLT_ht700_L1J100 = {fReader, "trigger_HLT_ht700_L1J100"};
   TTreeReaderValue<Int_t> trigger_HLT_ht850_L1J100 = {fReader, "trigger_HLT_ht850_L1J100"};
   TTreeReaderValue<Int_t> trigger_HLT_j30_xe10_razor100 = {fReader, "trigger_HLT_j30_xe10_razor100"};
   TTreeReaderValue<Int_t> trigger_HLT_j30_xe10_razor170 = {fReader, "trigger_HLT_j30_xe10_razor170"};
   TTreeReaderValue<Int_t> trigger_HLT_j30_xe10_razor185 = {fReader, "trigger_HLT_j30_xe10_razor185"};
   TTreeReaderValue<Int_t> trigger_HLT_j30_xe10_razor195 = {fReader, "trigger_HLT_j30_xe10_razor195"};
   TTreeReaderValue<Int_t> trigger_HLT_j30_xe60_razor100 = {fReader, "trigger_HLT_j30_xe60_razor100"};
   TTreeReaderValue<Int_t> trigger_HLT_j30_xe60_razor170 = {fReader, "trigger_HLT_j30_xe60_razor170"};
   TTreeReaderValue<Int_t> trigger_HLT_j30_xe60_razor185 = {fReader, "trigger_HLT_j30_xe60_razor185"};
   TTreeReaderValue<Int_t> trigger_HLT_j30_xe60_razor195 = {fReader, "trigger_HLT_j30_xe60_razor195"};
   TTreeReaderValue<Int_t> trigger_HLT_j360 = {fReader, "trigger_HLT_j360"};
   TTreeReaderValue<Int_t> trigger_HLT_j380 = {fReader, "trigger_HLT_j380"};
   TTreeReaderValue<Int_t> trigger_HLT_mu24_imedium = {fReader, "trigger_HLT_mu24_imedium"};
   TTreeReaderValue<Int_t> trigger_HLT_mu24_ivarmedium = {fReader, "trigger_HLT_mu24_ivarmedium"};
   TTreeReaderValue<Int_t> trigger_HLT_mu26_imedium = {fReader, "trigger_HLT_mu26_imedium"};
   TTreeReaderValue<Int_t> trigger_HLT_mu26_ivarmedium = {fReader, "trigger_HLT_mu26_ivarmedium"};
   TTreeReaderValue<Int_t> trigger_HLT_mu50 = {fReader, "trigger_HLT_mu50"};
   TTreeReaderValue<Int_t> trigger_HLT_mu60_0eta105_msonly = {fReader, "trigger_HLT_mu60_0eta105_msonly"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_mht = {fReader, "trigger_HLT_xe100_mht"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_pueta = {fReader, "trigger_HLT_xe100_pueta"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_pufit = {fReader, "trigger_HLT_xe100_pufit"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_pufit_L1XE50 = {fReader, "trigger_HLT_xe100_pufit_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_pufit_L1XE55 = {fReader, "trigger_HLT_xe100_pufit_L1XE55"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_tc_em = {fReader, "trigger_HLT_xe100_tc_em"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_tc_lcw = {fReader, "trigger_HLT_xe100_tc_lcw"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_tc_lcw_L1XE50 = {fReader, "trigger_HLT_xe100_tc_lcw_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe100_tc_lcw_L1XE60 = {fReader, "trigger_HLT_xe100_tc_lcw_L1XE60"};
   TTreeReaderValue<Int_t> trigger_HLT_xe110_pufit_L1XE50 = {fReader, "trigger_HLT_xe110_pufit_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe110_pufit_L1XE55 = {fReader, "trigger_HLT_xe110_pufit_L1XE55"};
   TTreeReaderValue<Int_t> trigger_HLT_xe110_pufit_xe65_L1XE50 = {fReader, "trigger_HLT_xe110_pufit_xe65_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe110_pufit_xe70_L1XE50 = {fReader, "trigger_HLT_xe110_pufit_xe70_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe120_pufit_L1XE50 = {fReader, "trigger_HLT_xe120_pufit_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe130_mht_L1XE50 = {fReader, "trigger_HLT_xe130_mht_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe70 = {fReader, "trigger_HLT_xe70"};
   TTreeReaderValue<Int_t> trigger_HLT_xe70_mht = {fReader, "trigger_HLT_xe70_mht"};
   TTreeReaderValue<Int_t> trigger_HLT_xe70_pueta = {fReader, "trigger_HLT_xe70_pueta"};
   TTreeReaderValue<Int_t> trigger_HLT_xe70_pufit = {fReader, "trigger_HLT_xe70_pufit"};
   TTreeReaderValue<Int_t> trigger_HLT_xe70_tc_em = {fReader, "trigger_HLT_xe70_tc_em"};
   TTreeReaderValue<Int_t> trigger_HLT_xe70_tc_lcw = {fReader, "trigger_HLT_xe70_tc_lcw"};
   TTreeReaderValue<Int_t> trigger_HLT_xe80 = {fReader, "trigger_HLT_xe80"};
   TTreeReaderValue<Int_t> trigger_HLT_xe80_pueta = {fReader, "trigger_HLT_xe80_pueta"};
   TTreeReaderValue<Int_t> trigger_HLT_xe80_tc_lcw_L1XE50 = {fReader, "trigger_HLT_xe80_tc_lcw_L1XE50"};
   TTreeReaderValue<Int_t> trigger_HLT_xe90_pufit_L1XE50 = {fReader, "trigger_HLT_xe90_pufit_L1XE50"};
   TTreeReaderValue<Int_t> trigger_L1_XE50 = {fReader, "trigger_L1_XE50"};
   TTreeReaderValue<Int_t> trigger_L1_XE70 = {fReader, "trigger_L1_XE70"};
   TTreeReaderValue<Int_t> trigger_L2_2J15_XE55 = {fReader, "trigger_L2_2J15_XE55"};
   TTreeReaderValue<Int_t> trigger_ht700_L1J75 = {fReader, "trigger_ht700_L1J75"};
   TTreeReaderValue<Int_t> trigger_ht850_L1J75 = {fReader, "trigger_ht850_L1J75"};
   TTreeReaderValue<Int_t> hfor = {fReader, "hfor"};
   TTreeReaderValue<Int_t> n_ph_tight = {fReader, "n_ph_tight"};
   TTreeReaderValue<Int_t> n_ph_baseline = {fReader, "n_ph_baseline"};
   TTreeReaderValue<Int_t> n_ph_baseline_tight = {fReader, "n_ph_baseline_tight"};
   TTreeReaderValue<Int_t> pdf_id1 = {fReader, "pdf_id1"};
   TTreeReaderValue<Int_t> pdf_id2 = {fReader, "pdf_id2"};
   TTreeReaderValue<Int_t> bb_decision = {fReader, "bb_decision"};
   TTreeReaderValue<Int_t> n_jet_truth = {fReader, "n_jet_truth"};
   TTreeReaderValue<Float_t> truth_V_bare_pt = {fReader, "truth_V_bare_pt"};
   TTreeReaderValue<Float_t> truth_V_bare_eta = {fReader, "truth_V_bare_eta"};
   TTreeReaderValue<Float_t> truth_V_bare_phi = {fReader, "truth_V_bare_phi"};
   TTreeReaderValue<Float_t> truth_V_bare_m = {fReader, "truth_V_bare_m"};
   TTreeReaderValue<Float_t> truth_V_dressed_pt = {fReader, "truth_V_dressed_pt"};
   TTreeReaderValue<Float_t> truth_V_dressed_eta = {fReader, "truth_V_dressed_eta"};
   TTreeReaderValue<Float_t> truth_V_dressed_phi = {fReader, "truth_V_dressed_phi"};
   TTreeReaderValue<Float_t> truth_V_dressed_m = {fReader, "truth_V_dressed_m"};
   TTreeReaderValue<Float_t> met_ph_MT = {fReader, "met_ph_MT"};
   TTreeReaderValue<Float_t> met_tst_sig_old = {fReader, "met_tst_sig_old"};
   TTreeReaderValue<Int_t> n_ph_tot = {fReader, "n_ph_tot"};
   TTreeReaderValue<Int_t> n_el_tot = {fReader, "n_el_tot"};
   TTreeReaderValue<Int_t> n_el_probe = {fReader, "n_el_probe"};
   TTreeReaderValue<Int_t> n_jet_tot = {fReader, "n_jet_tot"};
   TTreeReaderValue<Int_t> n_jet_good = {fReader, "n_jet_good"};
   TTreeReaderValue<Int_t> n_mu_tot = {fReader, "n_mu_tot"};
   TTreeReaderValue<Int_t> n_tau_tot = {fReader, "n_tau_tot"};
   TTreeReaderValue<Int_t> n_pv = {fReader, "n_pv"};
   TTreeReaderValue<Float_t> xSec_AMI = {fReader, "xSec_AMI"};
   TTreeReaderValue<Float_t> xSec_SUSY = {fReader, "xSec_SUSY"};
   TTreeReaderValue<Float_t> k_factor = {fReader, "k_factor"};
   TTreeReaderValue<Float_t> filter_eff = {fReader, "filter_eff"};
   TTreeReaderValue<Float_t> evsf_good_nominal_EL = {fReader, "evsf_good_nominal_EL"};
   TTreeReaderValue<Float_t> evsf_good_nominal_MU = {fReader, "evsf_good_nominal_MU"};
   TTreeReaderValue<Float_t> evsf_leading_nominal_PH = {fReader, "evsf_leading_nominal_PH"};
   TTreeReaderValue<Float_t> met_eleterm_et = {fReader, "met_eleterm_et"};
   TTreeReaderValue<Float_t> met_eleterm_phi = {fReader, "met_eleterm_phi"};
   TTreeReaderValue<Float_t> met_eleterm_etx = {fReader, "met_eleterm_etx"};
   TTreeReaderValue<Float_t> met_eleterm_ety = {fReader, "met_eleterm_ety"};
   TTreeReaderValue<Float_t> met_eleterm_sumet = {fReader, "met_eleterm_sumet"};
   TTreeReaderValue<Float_t> met_jetterm_et = {fReader, "met_jetterm_et"};
   TTreeReaderValue<Float_t> met_jetterm_phi = {fReader, "met_jetterm_phi"};
   TTreeReaderValue<Float_t> met_jetterm_etx = {fReader, "met_jetterm_etx"};
   TTreeReaderValue<Float_t> met_jetterm_ety = {fReader, "met_jetterm_ety"};
   TTreeReaderValue<Float_t> met_jetterm_sumet = {fReader, "met_jetterm_sumet"};
   TTreeReaderValue<Float_t> met_muonterm_et = {fReader, "met_muonterm_et"};
   TTreeReaderValue<Float_t> met_muonterm_phi = {fReader, "met_muonterm_phi"};
   TTreeReaderValue<Float_t> met_muonterm_etx = {fReader, "met_muonterm_etx"};
   TTreeReaderValue<Float_t> met_muonterm_ety = {fReader, "met_muonterm_ety"};
   TTreeReaderValue<Float_t> met_muonterm_sumet = {fReader, "met_muonterm_sumet"};
   TTreeReaderValue<Float_t> met_muonterm_tst_et = {fReader, "met_muonterm_tst_et"};
   TTreeReaderValue<Float_t> met_muonterm_tst_phi = {fReader, "met_muonterm_tst_phi"};
   TTreeReaderValue<Float_t> met_muonterm_tst_etx = {fReader, "met_muonterm_tst_etx"};
   TTreeReaderValue<Float_t> met_muonterm_tst_ety = {fReader, "met_muonterm_tst_ety"};
   TTreeReaderValue<Float_t> met_muonterm_tst_sumet = {fReader, "met_muonterm_tst_sumet"};
   TTreeReaderValue<Float_t> met_noelectron_tst_et = {fReader, "met_noelectron_tst_et"};
   TTreeReaderValue<Float_t> met_noelectron_tst_phi = {fReader, "met_noelectron_tst_phi"};
   TTreeReaderValue<Float_t> met_noelectron_tst_etx = {fReader, "met_noelectron_tst_etx"};
   TTreeReaderValue<Float_t> met_noelectron_tst_ety = {fReader, "met_noelectron_tst_ety"};
   TTreeReaderValue<Float_t> met_noelectron_tst_sumet = {fReader, "met_noelectron_tst_sumet"};
   TTreeReaderValue<Float_t> met_nomuon_tst_et = {fReader, "met_nomuon_tst_et"};
   TTreeReaderValue<Float_t> met_nomuon_tst_phi = {fReader, "met_nomuon_tst_phi"};
   TTreeReaderValue<Float_t> met_nomuon_tst_etx = {fReader, "met_nomuon_tst_etx"};
   TTreeReaderValue<Float_t> met_nomuon_tst_ety = {fReader, "met_nomuon_tst_ety"};
   TTreeReaderValue<Float_t> met_nomuon_tst_sumet = {fReader, "met_nomuon_tst_sumet"};
   TTreeReaderValue<Float_t> met_nophoton_tst_et = {fReader, "met_nophoton_tst_et"};
   TTreeReaderValue<Float_t> met_nophoton_tst_phi = {fReader, "met_nophoton_tst_phi"};
   TTreeReaderValue<Float_t> met_nophoton_tst_etx = {fReader, "met_nophoton_tst_etx"};
   TTreeReaderValue<Float_t> met_nophoton_tst_ety = {fReader, "met_nophoton_tst_ety"};
   TTreeReaderValue<Float_t> met_nophoton_tst_sumet = {fReader, "met_nophoton_tst_sumet"};
   TTreeReaderValue<Float_t> met_phterm_et = {fReader, "met_phterm_et"};
   TTreeReaderValue<Float_t> met_phterm_phi = {fReader, "met_phterm_phi"};
   TTreeReaderValue<Float_t> met_phterm_etx = {fReader, "met_phterm_etx"};
   TTreeReaderValue<Float_t> met_phterm_ety = {fReader, "met_phterm_ety"};
   TTreeReaderValue<Float_t> met_phterm_sumet = {fReader, "met_phterm_sumet"};
   TTreeReaderValue<Float_t> met_softerm_cst_et = {fReader, "met_softerm_cst_et"};
   TTreeReaderValue<Float_t> met_softerm_cst_phi = {fReader, "met_softerm_cst_phi"};
   TTreeReaderValue<Float_t> met_softerm_cst_etx = {fReader, "met_softerm_cst_etx"};
   TTreeReaderValue<Float_t> met_softerm_cst_ety = {fReader, "met_softerm_cst_ety"};
   TTreeReaderValue<Float_t> met_softerm_cst_sumet = {fReader, "met_softerm_cst_sumet"};
   TTreeReaderValue<Float_t> met_softerm_tst_et = {fReader, "met_softerm_tst_et"};
   TTreeReaderValue<Float_t> met_softerm_tst_phi = {fReader, "met_softerm_tst_phi"};
   TTreeReaderValue<Float_t> met_softerm_tst_etx = {fReader, "met_softerm_tst_etx"};
   TTreeReaderValue<Float_t> met_softerm_tst_ety = {fReader, "met_softerm_tst_ety"};
   TTreeReaderValue<Float_t> met_softerm_tst_sumet = {fReader, "met_softerm_tst_sumet"};
   TTreeReaderValue<Float_t> met_track_et = {fReader, "met_track_et"};
   TTreeReaderValue<Float_t> met_track_phi = {fReader, "met_track_phi"};
   TTreeReaderValue<Float_t> met_track_etx = {fReader, "met_track_etx"};
   TTreeReaderValue<Float_t> met_track_ety = {fReader, "met_track_ety"};
   TTreeReaderValue<Float_t> met_track_sumet = {fReader, "met_track_sumet"};
   TTreeReaderValue<Float_t> met_truth_et = {fReader, "met_truth_et"};
   TTreeReaderValue<Float_t> met_truth_phi = {fReader, "met_truth_phi"};
   TTreeReaderValue<Float_t> met_truth_etx = {fReader, "met_truth_etx"};
   TTreeReaderValue<Float_t> met_truth_ety = {fReader, "met_truth_ety"};
   TTreeReaderValue<Float_t> met_truth_sumet = {fReader, "met_truth_sumet"};
   
   TTreeReaderValue<Float_t> met_tst_et = {fReader, "met_tst_et"};   
   TTreeReaderValue<Float_t> met_tst_etx = {fReader, "met_tst_etx"};
   TTreeReaderValue<Float_t> met_tst_ety = {fReader, "met_tst_ety"};
   
   TTreeReaderArray<float> mu_pt = {fReader, "mu_pt"};
   TTreeReaderArray<float> mu_eta = {fReader, "mu_eta"};
   TTreeReaderArray<float> mu_phi = {fReader, "mu_phi"};
   TTreeReaderArray<float> mu_SF = {fReader, "mu_SF"};
   TTreeReaderArray<float> mu_SF_baseline = {fReader, "mu_SF_baseline"};
   TTreeReaderArray<float> mu_SF_iso = {fReader, "mu_SF_iso"};
   TTreeReaderArray<int> mu_isotool_pass_loosetrackonly = {fReader, "mu_isotool_pass_loosetrackonly"};
   TTreeReaderArray<int> mu_isotool_pass_fixedcuttighttrackonly = {fReader, "mu_isotool_pass_fixedcuttighttrackonly"};
   TTreeReaderArray<float> mu_m = {fReader, "mu_m"};
   TTreeReaderArray<float> mu_d0 = {fReader, "mu_d0"};
   TTreeReaderArray<float> mu_d0sig = {fReader, "mu_d0sig"};
   TTreeReaderArray<float> mu_z0 = {fReader, "mu_z0"};
   TTreeReaderArray<float> mu_z0sig = {fReader, "mu_z0sig"};
   TTreeReaderArray<float> mu_charge = {fReader, "mu_charge"};
   TTreeReaderArray<float> mu_id_pt = {fReader, "mu_id_pt"};
   TTreeReaderArray<float> mu_id_eta = {fReader, "mu_id_eta"};
   TTreeReaderArray<float> mu_id_phi = {fReader, "mu_id_phi"};
   TTreeReaderArray<float> mu_id_m = {fReader, "mu_id_m"};
   TTreeReaderArray<float> mu_me_pt = {fReader, "mu_me_pt"};
   TTreeReaderArray<float> mu_me_eta = {fReader, "mu_me_eta"};
   TTreeReaderArray<float> mu_me_phi = {fReader, "mu_me_phi"};
   TTreeReaderArray<float> mu_me_m = {fReader, "mu_me_m"};
   TTreeReaderArray<float> mu_ptcone20 = {fReader, "mu_ptcone20"};
   TTreeReaderArray<float> mu_ptvarcone20 = {fReader, "mu_ptvarcone20"};
   TTreeReaderArray<float> mu_etcone20 = {fReader, "mu_etcone20"};
   TTreeReaderArray<float> mu_topoetcone20 = {fReader, "mu_topoetcone20"};
   TTreeReaderArray<float> mu_ptcone30 = {fReader, "mu_ptcone30"};
   TTreeReaderArray<float> mu_ptvarcone30 = {fReader, "mu_ptvarcone30"};
   TTreeReaderArray<float> mu_etcone30 = {fReader, "mu_etcone30"};
   TTreeReaderArray<float> mu_topoetcone30 = {fReader, "mu_topoetcone30"};
   TTreeReaderArray<float> mu_ptcone40 = {fReader, "mu_ptcone40"};
   TTreeReaderArray<float> mu_ptvarcone40 = {fReader, "mu_ptvarcone40"};
   TTreeReaderArray<float> mu_etcone40 = {fReader, "mu_etcone40"};
   TTreeReaderArray<float> mu_topoetcone40 = {fReader, "mu_topoetcone40"};
   TTreeReaderArray<int> mu_author = {fReader, "mu_author"};
   TTreeReaderArray<int> mu_quality = {fReader, "mu_quality"};
   TTreeReaderArray<int> mu_isSA = {fReader, "mu_isSA"};
   TTreeReaderArray<int> mu_isotool_pass_loose = {fReader, "mu_isotool_pass_loose"};
   TTreeReaderArray<int> mu_isotool_pass_gradient = {fReader, "mu_isotool_pass_gradient"};
   TTreeReaderArray<int> mu_isotool_pass_gradientloose = {fReader, "mu_isotool_pass_gradientloose"};
   TTreeReaderArray<float> mu_met_nomuon_dphi = {fReader, "mu_met_nomuon_dphi"};
   TTreeReaderArray<float> mu_met_wmuon_dphi = {fReader, "mu_met_wmuon_dphi"};
   TTreeReaderArray<float> mu_pt_1 = {fReader, "mu_pt_1"};
   TTreeReaderArray<float> mu_eta_1 = {fReader, "mu_eta_1"};
   TTreeReaderArray<float> mu_phi_1 = {fReader, "mu_phi_1"};
   TTreeReaderArray<float> mu_pt_2 = {fReader, "mu_pt_2"};
   TTreeReaderArray<float> mu_eta_2 = {fReader, "mu_eta_2"};
   TTreeReaderArray<float> mu_phi_2 = {fReader, "mu_phi_2"};
   TTreeReaderArray<float> mu_pt_3 = {fReader, "mu_pt_3"};
   TTreeReaderArray<float> mu_eta_3 = {fReader, "mu_eta_3"};
   TTreeReaderArray<float> mu_phi_3 = {fReader, "mu_phi_3"};
   TTreeReaderArray<float> el_pt = {fReader, "el_pt"};
   TTreeReaderArray<float> el_eta = {fReader, "el_eta"};
   TTreeReaderArray<float> el_phi = {fReader, "el_phi"};
   TTreeReaderArray<float> el_SF = {fReader, "el_SF"};
   TTreeReaderArray<float> el_SF_baseline = {fReader, "el_SF_baseline"};
   TTreeReaderArray<float> el_SF_iso = {fReader, "el_SF_iso"};
   TTreeReaderArray<float> el_SF_trigger = {fReader, "el_SF_trigger"};
   TTreeReaderArray<float> el_SF_tot = {fReader, "el_SF_tot"};
   TTreeReaderArray<float> el_SF_tot_isotight = {fReader, "el_SF_tot_isotight"};
   TTreeReaderArray<int> el_isotool_pass_loosetrackonly = {fReader, "el_isotool_pass_loosetrackonly"};
   TTreeReaderArray<int> el_isotool_pass_fixedcuttighttrackonly = {fReader, "el_isotool_pass_fixedcuttighttrackonly"};
   TTreeReaderArray<int> el_isotool_pass_fixedcuttight = {fReader, "el_isotool_pass_fixedcuttight"};
   TTreeReaderArray<float> el_m = {fReader, "el_m"};
   TTreeReaderArray<float> el_charge = {fReader, "el_charge"};
   TTreeReaderArray<float> el_id_pt = {fReader, "el_id_pt"};
   TTreeReaderArray<float> el_id_eta = {fReader, "el_id_eta"};
   TTreeReaderArray<float> el_id_phi = {fReader, "el_id_phi"};
   TTreeReaderArray<float> el_id_m = {fReader, "el_id_m"};
   TTreeReaderArray<float> el_cl_pt = {fReader, "el_cl_pt"};
   TTreeReaderArray<float> el_cl_eta = {fReader, "el_cl_eta"};
   TTreeReaderArray<float> el_cl_etaBE2 = {fReader, "el_cl_etaBE2"};
   TTreeReaderArray<float> el_cl_phi = {fReader, "el_cl_phi"};
   TTreeReaderArray<float> el_cl_m = {fReader, "el_cl_m"};
   TTreeReaderArray<float> el_ptcone20 = {fReader, "el_ptcone20"};
   TTreeReaderArray<float> el_ptvarcone20 = {fReader, "el_ptvarcone20"};
   TTreeReaderArray<float> el_etcone20 = {fReader, "el_etcone20"};
   TTreeReaderArray<float> el_topoetcone20 = {fReader, "el_topoetcone20"};
   TTreeReaderArray<float> el_ptcone30 = {fReader, "el_ptcone30"};
   TTreeReaderArray<float> el_ptvarcone30 = {fReader, "el_ptvarcone30"};
   TTreeReaderArray<float> el_etcone30 = {fReader, "el_etcone30"};
   TTreeReaderArray<float> el_topoetcone30 = {fReader, "el_topoetcone30"};
   TTreeReaderArray<float> el_ptcone40 = {fReader, "el_ptcone40"};
   TTreeReaderArray<float> el_ptvarcone40 = {fReader, "el_ptvarcone40"};
   TTreeReaderArray<float> el_etcone40 = {fReader, "el_etcone40"};
   TTreeReaderArray<float> el_topoetcone40 = {fReader, "el_topoetcone40"};
   TTreeReaderArray<float> el_d0 = {fReader, "el_d0"};
   TTreeReaderArray<float> el_d0sig = {fReader, "el_d0sig"};
   TTreeReaderArray<float> el_z0 = {fReader, "el_z0"};
   TTreeReaderArray<float> el_z0sig = {fReader, "el_z0sig"};
   TTreeReaderArray<int> el_author = {fReader, "el_author"};
   TTreeReaderArray<int> el_isConv = {fReader, "el_isConv"};
   TTreeReaderArray<float> el_truth_pt = {fReader, "el_truth_pt"};
   TTreeReaderArray<float> el_truth_eta = {fReader, "el_truth_eta"};
   TTreeReaderArray<float> el_truth_phi = {fReader, "el_truth_phi"};
   TTreeReaderArray<int> el_truth_status = {fReader, "el_truth_status"};
   TTreeReaderArray<int> el_truth_type = {fReader, "el_truth_type"};
   TTreeReaderArray<int> el_truth_origin = {fReader, "el_truth_origin"};
   TTreeReaderArray<int> el_isotool_pass_loose = {fReader, "el_isotool_pass_loose"};
   TTreeReaderArray<int> el_isotool_pass_gradient = {fReader, "el_isotool_pass_gradient"};
   TTreeReaderArray<int> el_isotool_pass_gradientloose = {fReader, "el_isotool_pass_gradientloose"};
   TTreeReaderArray<float> el_met_nomuon_dphi = {fReader, "el_met_nomuon_dphi"};
   TTreeReaderArray<float> el_met_wmuon_dphi = {fReader, "el_met_wmuon_dphi"};
   TTreeReaderArray<float> el_met_noelectron_dphi = {fReader, "el_met_noelectron_dphi"};
   TTreeReaderArray<float> el_pt_1 = {fReader, "el_pt_1"};
   TTreeReaderArray<float> el_eta_1 = {fReader, "el_eta_1"};
   TTreeReaderArray<float> el_phi_1 = {fReader, "el_phi_1"};
   TTreeReaderArray<float> el_pt_2 = {fReader, "el_pt_2"};
   TTreeReaderArray<float> el_eta_2 = {fReader, "el_eta_2"};
   TTreeReaderArray<float> el_phi_2 = {fReader, "el_phi_2"};
   TTreeReaderArray<float> el_pt_3 = {fReader, "el_pt_3"};
   TTreeReaderArray<float> el_eta_3 = {fReader, "el_eta_3"};
   TTreeReaderArray<float> el_phi_3 = {fReader, "el_phi_3"};
   TTreeReaderArray<float> el_1_met_nomuon_dphi = {fReader, "el_1_met_nomuon_dphi"};
   TTreeReaderArray<float> el_2_met_nomuon_dphi = {fReader, "el_2_met_nomuon_dphi"};
   TTreeReaderArray<float> el_3_met_nomuon_dphi = {fReader, "el_3_met_nomuon_dphi"};
   TTreeReaderArray<float> el_1_met_noelectron_dphi = {fReader, "el_1_met_noelectron_dphi"};
   TTreeReaderArray<float> el_2_met_noelectron_dphi = {fReader, "el_2_met_noelectron_dphi"};
   TTreeReaderArray<float> el_3_met_noelectron_dphi = {fReader, "el_3_met_noelectron_dphi"};
   TTreeReaderArray<float> el_1_met_wmuon_dphi = {fReader, "el_1_met_wmuon_dphi"};
   TTreeReaderArray<float> el_2_met_wmuon_dphi = {fReader, "el_2_met_wmuon_dphi"};
   TTreeReaderArray<float> el_3_met_wmuon_dphi = {fReader, "el_3_met_wmuon_dphi"};
   TTreeReaderArray<float> jet_pt = {fReader, "jet_pt"};
   TTreeReaderArray<float> jet_eta = {fReader, "jet_eta"};
   
   TTreeReaderArray<float> jet_m = {fReader, "jet_m"};
   TTreeReaderArray<float> jet_fmax = {fReader, "jet_fmax"};
   TTreeReaderArray<float> jet_fch = {fReader, "jet_fch"};
   TTreeReaderArray<int> jet_PartonTruthLabelID = {fReader, "jet_PartonTruthLabelID"};
   TTreeReaderArray<int> jet_ConeTruthLabelID = {fReader, "jet_ConeTruthLabelID"};
   TTreeReaderArray<float> jet_met_nomuon_dphi = {fReader, "jet_met_nomuon_dphi"};
   TTreeReaderArray<float> jet_met_wmuon_dphi = {fReader, "jet_met_wmuon_dphi"};
   TTreeReaderArray<float> jet_met_noelectron_dphi = {fReader, "jet_met_noelectron_dphi"};
   TTreeReaderArray<float> jet_met_nophoton_dphi = {fReader, "jet_met_nophoton_dphi"};
   TTreeReaderArray<float> jet_weight = {fReader, "jet_weight"};
   TTreeReaderArray<float> jet_raw_pt = {fReader, "jet_raw_pt"};
   TTreeReaderArray<float> jet_raw_eta = {fReader, "jet_raw_eta"};
   TTreeReaderArray<float> jet_raw_phi = {fReader, "jet_raw_phi"};
   TTreeReaderArray<float> jet_raw_m = {fReader, "jet_raw_m"};
   TTreeReaderArray<float> jet_timing = {fReader, "jet_timing"};
   TTreeReaderArray<float> jet_emfrac = {fReader, "jet_emfrac"};
   TTreeReaderArray<float> jet_hecf = {fReader, "jet_hecf"};
   TTreeReaderArray<float> jet_hecq = {fReader, "jet_hecq"};
   TTreeReaderArray<float> jet_larq = {fReader, "jet_larq"};
   TTreeReaderArray<float> jet_avglarq = {fReader, "jet_avglarq"};
   TTreeReaderArray<float> jet_negE = {fReader, "jet_negE"};
   TTreeReaderArray<float> jet_lambda = {fReader, "jet_lambda"};
   TTreeReaderArray<float> jet_lambda2 = {fReader, "jet_lambda2"};
   TTreeReaderArray<float> jet_jvtxf = {fReader, "jet_jvtxf"};
   TTreeReaderArray<int> jet_fmaxi = {fReader, "jet_fmaxi"};
   TTreeReaderArray<float> jet_jvt = {fReader, "jet_jvt"};
   TTreeReaderArray<int> jet_cleaning = {fReader, "jet_cleaning"};
   TTreeReaderArray<float> jet_TruthLabelDeltaR_B = {fReader, "jet_TruthLabelDeltaR_B"};
   TTreeReaderArray<float> jet_TruthLabelDeltaR_C = {fReader, "jet_TruthLabelDeltaR_C"};
   TTreeReaderArray<float> jet_TruthLabelDeltaR_T = {fReader, "jet_TruthLabelDeltaR_T"};
   TTreeReaderArray<float> jet_pt_1 = {fReader, "jet_pt_1"};
   TTreeReaderArray<float> jet_pt_2 = {fReader, "jet_pt_2"};
   TTreeReaderArray<float> jet_pt_3 = {fReader, "jet_pt_3"};
   TTreeReaderArray<float> jet_eta_1 = {fReader, "jet_eta_1"};
   TTreeReaderArray<float> jet_eta_2 = {fReader, "jet_eta_2"};
   TTreeReaderArray<float> jet_eta_3 = {fReader, "jet_eta_3"};
   TTreeReaderArray<float> jet_phi_1 = {fReader, "jet_phi_1"};
   TTreeReaderArray<float> jet_phi_2 = {fReader, "jet_phi_2"};
   TTreeReaderArray<float> jet_phi_3 = {fReader, "jet_phi_3"};
   TTreeReaderArray<float> jet_1_met_nomuon_dphi = {fReader, "jet_1_met_nomuon_dphi"};
   TTreeReaderArray<float> jet_2_met_nomuon_dphi = {fReader, "jet_2_met_nomuon_dphi"};
   TTreeReaderArray<float> jet_3_met_nomuon_dphi = {fReader, "jet_3_met_nomuon_dphi"};
   TTreeReaderArray<float> jet_1_met_wmuon_dphi = {fReader, "jet_1_met_wmuon_dphi"};
   TTreeReaderArray<float> jet_2_met_wmuon_dphi = {fReader, "jet_2_met_wmuon_dphi"};
   TTreeReaderArray<float> jet_3_met_wmuon_dphi = {fReader, "jet_3_met_wmuon_dphi"};
   TTreeReaderArray<float> jet_1_ph_dphi = {fReader, "jet_1_ph_dphi"};
   TTreeReaderArray<float> jet_2_ph_dphi = {fReader, "jet_2_ph_dphi"};
   TTreeReaderArray<float> jet_3_ph_dphi = {fReader, "jet_3_ph_dphi"};
   TTreeReaderArray<float> jet_pt_all = {fReader, "jet_pt_all"};
   TTreeReaderArray<float> jet_eta_all = {fReader, "jet_eta_all"};
   TTreeReaderArray<float> jet_phi_all = {fReader, "jet_phi_all"};
   TTreeReaderArray<int> jet_isBad_all = {fReader, "jet_isBad_all"};
   TTreeReaderArray<int> jet_passOR_all = {fReader, "jet_passOR_all"};
   TTreeReaderArray<float> jet_jvt_all = {fReader, "jet_jvt_all"};

   
   
   TTreeReaderArray<float> ph_SF = {fReader, "ph_SF"};
   TTreeReaderArray<float> ph_SF_baseline = {fReader, "ph_SF_baseline"};
   TTreeReaderArray<float> ph_SF_iso = {fReader, "ph_SF_iso"};
   TTreeReaderArray<int> ph_isotool_pass_fixedcuttightcaloonly = {fReader, "ph_isotool_pass_fixedcuttightcaloonly"};
   TTreeReaderArray<int> ph_isotool_pass_fixedcuttight = {fReader, "ph_isotool_pass_fixedcuttight"};
   TTreeReaderArray<int> ph_isotool_pass_fixedcutloose = {fReader, "ph_isotool_pass_fixedcutloose"};
   TTreeReaderArray<float> ph_m = {fReader, "ph_m"};
   TTreeReaderArray<float> ph_ptcone20 = {fReader, "ph_ptcone20"};
   TTreeReaderArray<float> ph_ptvarcone20 = {fReader, "ph_ptvarcone20"};
   TTreeReaderArray<float> ph_etcone20 = {fReader, "ph_etcone20"};
   TTreeReaderArray<float> ph_topoetcone20 = {fReader, "ph_topoetcone20"};
   TTreeReaderArray<float> ph_ptcone30 = {fReader, "ph_ptcone30"};
   TTreeReaderArray<float> ph_ptvarcone30 = {fReader, "ph_ptvarcone30"};
   TTreeReaderArray<float> ph_etcone30 = {fReader, "ph_etcone30"};
   TTreeReaderArray<float> ph_topoetcone30 = {fReader, "ph_topoetcone30"};
   TTreeReaderArray<float> ph_ptcone40 = {fReader, "ph_ptcone40"};
   TTreeReaderArray<float> ph_ptvarcone40 = {fReader, "ph_ptvarcone40"};
   TTreeReaderArray<float> ph_etcone40 = {fReader, "ph_etcone40"};
   
   
   TTreeReaderArray<int> ph_isEM = {fReader, "ph_isEM"};
   TTreeReaderArray<unsigned int> ph_OQ = {fReader, "ph_OQ"};
   TTreeReaderArray<int> ph_author = {fReader, "ph_author"};
   TTreeReaderArray<int> ph_isConv = {fReader, "ph_isConv"};
   TTreeReaderArray<float> ph_truth_pt = {fReader, "ph_truth_pt"};
   TTreeReaderArray<float> ph_truth_eta = {fReader, "ph_truth_eta"};
   TTreeReaderArray<float> ph_truth_phi = {fReader, "ph_truth_phi"};
   TTreeReaderArray<int> ph_truth_status = {fReader, "ph_truth_status"};
   TTreeReaderArray<int> ph_truth_type = {fReader, "ph_truth_type"};
   TTreeReaderArray<int> ph_truth_origin = {fReader, "ph_truth_origin"};
   TTreeReaderArray<float> ph_met_nomuon_dphi = {fReader, "ph_met_nomuon_dphi"};
   
   TTreeReaderArray<float> ph_met_nophoton_dphi = {fReader, "ph_met_nophoton_dphi"};
   TTreeReaderArray<float> ph_met_dphi = {fReader, "ph_met_dphi"};
   TTreeReaderArray<float> ph_met_noele_dphi = {fReader, "ph_met_noele_dphi"};
   TTreeReaderArray<float> ph_eta2 = {fReader, "ph_eta2"};
   TTreeReaderArray<float> ph_time = {fReader, "ph_time"};
   TTreeReaderArray<int> ph_pdgId = {fReader, "ph_pdgId"};
   TTreeReaderArray<int> ph_mother_pdgId = {fReader, "ph_mother_pdgId"};
   
   TTreeReaderArray<float> ph_ZVtx_err = {fReader, "ph_ZVtx_err"};
   TTreeReaderArray<float> ph_pt_2 = {fReader, "ph_pt_2"};
   TTreeReaderArray<float> ph_eta_2 = {fReader, "ph_eta_2"};
   TTreeReaderArray<float> ph_phi_2 = {fReader, "ph_phi_2"};
   TTreeReaderArray<float> ph_pt_3 = {fReader, "ph_pt_3"};
   TTreeReaderArray<float> ph_eta_3 = {fReader, "ph_eta_3"};
   TTreeReaderArray<float> ph_phi_3 = {fReader, "ph_phi_3"};
   */
   

   //------------------------------LEAFS USATE------------------------------
   TTreeReaderValue<Int_t> trigger_HLT_g140_loose = {fReader, "trigger_HLT_g140_loose"};
   TTreeReaderValue<Float_t> met_tst_et = {fReader, "met_tst_et"};
   TTreeReaderArray<float> ph_pt = {fReader, "ph_pt"};
   TTreeReaderArray<float> ph_eta2 = {fReader, "ph_eta2"};
   TTreeReaderValue<Float_t> met_tst_sig_old = {fReader, "met_tst_sig_old"};
//   TTreeReaderArray<float> ph_met_dphi = {fReader, "ph_met_dphi"};
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
   TTreeReaderValue<Float_t> met_tst_sumet = {fReader, "met_tst_sumet"};
   //------------------------------DEFINIZIONE VARIABILI------------------------------
   
   int tmpInt;
   float tmpFloat;
   bool tmpBool;
   Int_t NumberOfEvents;
   Int_t N_trigger;
   Int_t N_met_tst_et;
   Int_t N_ph_pt;
   Int_t N_met_tst_sig_old;
   Int_t N_ph_met_dphi;
   Int_t N_ph_ZVtx;
   Int_t N_jet_veto;
   Int_t N_lepton_veto;
   Int_t N_ph_isTight;
   Int_t N_ph_iso;

   Int_t N_tight_3; 
   Int_t N_tight_4; 
   Int_t N_tight_5;


   //Le matrici sono del tipo
   //
   //    | Na    Nb    Ma    Mb
   //ISR1|
   //ISR2|
   //ISR3|
   //ESR1|
   //ESR2|

   Int_t **SR;
   Int_t **oneMuCR;
   Int_t **twoMuCR;
   Int_t **twoECR;

   Int_t *N_SR;         //Na Nb Ma Mb
   
   ofstream out;
   bool tight, iso;



   SelectorABCD(TTree * /*tree*/ =0) : 
      NumberOfEvents(0),
      N_trigger(0),
      N_met_tst_et(0),
      N_ph_pt(0),
      N_met_tst_sig_old(0),
      N_ph_met_dphi(0),
      N_ph_ZVtx(0),
      N_jet_veto(0),
      N_lepton_veto(0),
      N_ph_isTight(0),
      N_ph_iso(0),
      N_SR(0),
      SR(0),
      oneMuCR(0),
      twoMuCR(0),
      twoECR(0),
      N_tight_3(0),        
      N_tight_4(0),           
      N_tight_5(0)
      { }

   virtual ~SelectorABCD() { }
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

   virtual void CalcolaCR(Int_t **mat);    
   virtual void Calcola(Int_t *v);
   virtual void PrintMat(Int_t **mat);

   virtual Float_t Purezza(Int_t *v); 



   ClassDef(SelectorABCD,0);

};

#endif

#ifdef SelectorABCD_cxx
void SelectorABCD::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t SelectorABCD::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef SelectorABCD_cxx
