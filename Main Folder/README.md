
JETS FAKING PHOTONS 2019

This folder contains all the scripts to perform the Jets Faking Photons analysis, here a brief description of them and the data employed.

1. Samples  
	Monte Carlo samples:  
		These samples are simulations generated for the general ATLAS detector team. To perform the analysis we used the following samples:  
			•W + gamma: W boson decaying into a muon and a neutrino, associated with an energetic photon (signal)  
			•Z + gamma:  Z boson decaying into a muon and a neutrino, associated with an energetic photon (signal)  
			•W + jet: W boson decaying into a muon and a neutrino, associated with a jet (background)  
			•Z + jet:  Z boson decaying into a muon and a neutrino, associated with a jet (background)  
			•Znunu+ gamma: Z boson decaying into two neutrinos, associated with an energetic photon (signal)  
			•gamma jet: an event with an energetic photon and a jet (both signal and background)  
		Each sample has three similar generations, associated to the years 2015-16, 2017 and 2018.  
	Real data:  
		These are the real data from the so full Run2 dataset, comprising of all the data taken from 2015 to 2018, amounting to more than 2PB of storage.  
  
2. Script: routine.sh  
	Bash file that runs the scripts to analyze the raw Monte Carlo samples and real data and saving the results in the folder ‘dati’.   
	Both from the MC samples and the real data are taken from the full Run2 of LHC.  
  
  
2. Scripts: TSelectors (SelectorData.h, SelectorData.C, SelectorMC.h, SelectorMC.C)  
	C++ scripts that perform the above mentioned raw data analysis, they are specific ROOT files that analyze the TTrees, which are specific ROOT data structures. ROOt is CERN’s data analysis framework.  
	There are two header and two .C files to account for the difference between the real data and the MC samples.  
  
	Each TSelector takes its input parameters from ‘selector_parameters.txt’ (Missing energy transverse bins (MET), Calorimetric isolation, Tracking system isolation, Tightness).  
	The results produced by these selectors are photons populations stored matrices easily readable with the ‘Yaml’ python library. The hierarchy of the data is:   

			Signal or Control Region (SR - CR) —>  Inclusive or Exclusive MET region (ISR - ESR)  —> Tightness —> Track Isolation  
  
3. Notebook: Full analysis.ipynb  
	This is the main notebook used to analyze the data in the ‘dati’ folder and to produce all results and plots later published.  
  
4. Script: derivate_complete.py  
	File containing all the derivatives used in the analysis for error propagation. To avoid mistakes they have all been generated with Mathematica.  
  
5. Script: functions.py  
	Functions used in the analysis.  

