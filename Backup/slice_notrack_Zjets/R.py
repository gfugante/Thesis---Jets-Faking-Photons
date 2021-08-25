import ROOT
import math

non = ""
PATH_IN_FONDO = "eventi"+non+"_pesati.root"
PATH_OUT = "R"+non+"_pesati/R.txt"

#bin tightness
tight = 5
tight3 = 1
tight4 = 2
tight5 = 3
nottight = 4

isolamento = 3.




file_background = ROOT.TFile(PATH_IN_FONDO)

coefficienti = open(PATH_OUT, "w+")


regions = [ key.GetName() for key in file_background.GetListOfKeys() ]


for i in range(len(file_background.GetListOfKeys())):

	
	hist_b = file_background.Get(regions[i])


#	binx1_b = hist_b.GetXaxis().FindBin(hist_b.GetXaxis().GetXmin())
#	binx2_b = hist_b.GetXaxis().FindBin(0.) - 1
#	binx3_b = hist_b.GetXaxis().FindBin( isolamento )
#	binx4_b = hist_b.GetXaxis().FindBin(hist_b.GetXaxis().GetXmax())
	

	# calcolo Na, Nb, Ma, Mb
#	Na_b = hist_b.Integral(binx1_b, binx2_b, tight, tight)
#	Nb_b = hist_b.Integral(binx3_b, binx4_b, tight, tight)
#	Ma_b = hist_b.Integral(binx1_b, binx2_b, tight4, tight4)
#	Mb_b = hist_b.Integral(binx3_b, binx4_b, tight4, tight4)

	Na_b = hist_b.GetBinContent(1, tight)
	Nb_b = hist_b.GetBinContent(2, tight)
	Ma_b = hist_b.GetBinContent(1, tight4)
	Mb_b = hist_b.GetBinContent(2, tight4)

	try:

		R_MC = (Na_b*Mb_b)/float(Nb_b*Ma_b)
		sigma_R_MC = R_MC * math.sqrt((1/Na_b) + (1/Nb_b) + (1/Ma_b) + (1/Mb_b))


	except (ZeroDivisionError, ValueError):

		R_MC = 0
		sigma_R_MC = 0


	print("\n")
	print(regions[i])
	print("   R_MC: \t" + repr(round(R_MC,3)))
	print("   sigma_R_MC: \t" + repr(round(sigma_R_MC,3)))

	print("   " + "-"*27)
	print("   Na_b: " + repr(round(Na_b,2)))
	print("   Nb_b: " + repr(round(Nb_b,2)))
	print("   Ma_b: " + repr(round(Ma_b,2)))
	print("   Mb_b: " + repr(round(Mb_b,2)))

	
	coefficienti.write(regions[i] + ":\n")
	coefficienti.write("   R_MC: " + repr(R_MC) + "\n")
	coefficienti.write("   sigma_R_MC: " + repr(sigma_R_MC) + "\n")
	coefficienti.write("   Na_b: " + repr(Na_b) + "\n")
	coefficienti.write("   Nb_b: " + repr(Nb_b) + "\n")
	coefficienti.write("   Ma_b: " + repr(Ma_b) + "\n")
	coefficienti.write("   Mb_b: " + repr(Mb_b) + "\n")

	

print("\n\n")