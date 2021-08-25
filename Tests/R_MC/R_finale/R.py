import ROOT
import math


PATH_IN_FONDO = "Wjets_noMET.root"
PATH_OUT = "R_Wjets_noMET.txt"

#bin tightness
tight = 5
tight3 = 1
tight4 = 2
tight5 = 3
nottight = 4






file_background = ROOT.TFile(PATH_IN_FONDO)

coefficienti = open(PATH_OUT, "w+")


regions = [ key.GetName() for key in file_background.GetListOfKeys() ]


for i in range(len(file_background.GetListOfKeys())):

	
	hist = file_background.Get(regions[i])


	Na = hist.GetBinContent(1, tight)
	Nb = hist.GetBinContent(2, tight)
	Ma = hist.GetBinContent(1, tight4)
	Mb = hist.GetBinContent(2, tight4)

	if Na>0 and Nb>0 and Ma>0 and Mb>0:

		try:
			R_MC = (Na*Mb)/float(Nb*Ma)
			sigma_R_MC = R_MC * math.sqrt((1/Na) + (1/Nb) + (1/Ma) + (1/Mb))


		except (ZeroDivisionError, ValueError):

			R_MC = 0
			sigma_R_MC = 0

	else:
		R_MC = 0
		sigma_R_MC = 0


	print("\n")
	print(regions[i])
	print("   R_MC: \t" + repr(round(R_MC,3)))
	print("   sigma_R_MC: \t" + repr(round(sigma_R_MC,3)))

	print("   " + "-"*27)
	print("   Na: " + repr(round(Na,2)))
	print("   Nb: " + repr(round(Nb,2)))
	print("   Ma: " + repr(round(Ma,2)))
	print("   Mb: " + repr(round(Mb,2)))

	
	coefficienti.write(regions[i] + ":\n")
	coefficienti.write("   R_MC: " + repr(R_MC) + "\n")
	coefficienti.write("   sigma_R_MC: " + repr(sigma_R_MC) + "\n")
	coefficienti.write("   Na: " + repr(Na) + "\n")
	coefficienti.write("   Nb: " + repr(Nb) + "\n")
	coefficienti.write("   Ma: " + repr(Ma) + "\n")
	coefficienti.write("   Mb: " + repr(Mb) + "\n")

	

print("\n\n")
