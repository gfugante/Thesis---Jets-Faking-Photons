import ROOT
import math

PATH_IN = "eventi_pesati.root"
PATH_OUT = "Wgamma_pesati.txt"

#bin tightness
tight = 5
tight3 = 1
tight4 = 2
tight5 = 3
nottight = 4

isolamento = 3.



file = ROOT.TFile(PATH_IN)

coefficienti = open(PATH_OUT, "w+")


regions = [ key.GetName() for key in file.GetListOfKeys() ]


for i in range(len(file.GetListOfKeys())):

	hist_s = file.Get(regions[i])


	#binx1_s = hist_s.GetXaxis().FindBin(hist_s.GetXaxis().GetXmin())
	#binx2_s = hist_s.GetXaxis().FindBin(0.) - 1
	#binx3_s = hist_s.GetXaxis().FindBin( isolamento )
	#binx4_s = hist_s.GetXaxis().FindBin(hist_s.GetXaxis().GetXmax())

	
	# calcolo Na, Nb, Ma, Mb
	Na_s = hist_s.GetBinContent(1, tight)
	Nb_s = hist_s.GetBinContent(2, tight)
	Ma_s = hist_s.GetBinContent(1, tight4)
	Mb_s = hist_s.GetBinContent(2, tight4)


	try:

		c1 = Nb_s/Na_s
		c2 = Ma_s/Na_s
		c3 = Mb_s/Na_s
		
		sigma_c1 = c1 * math.sqrt((1/Na_s) + (1/Nb_s))
		sigma_c2 = c2 * math.sqrt((1/Na_s) + (1/Ma_s))
		sigma_c3 = c3 * math.sqrt((1/Na_s) + (1/Mb_s))



	except (ZeroDivisionError, ValueError):
		c1 = 0
		c2 = 0
		c3 = 0

		sigma_c1 = 0	
		sigma_c2 = 0
		sigma_c3 = 0


	print("\n")
	print(regions[i])
	print("   c1: \t\t" + repr(round(100*c1,3)) + " %")
	print("   sigma_c1: \t" + repr(round(100*sigma_c1,3)) + " %")
	print("   c2: \t\t" + repr(round(100*c2,3)) + " %")
	print("   sigma_c2: \t" + repr(round(100*sigma_c2,3)) + " %")
	print("   c3: \t\t" + repr(round(100*c3,3)) + " %")
	print("   sigma_c3: \t" + repr(round(100*sigma_c3,3)) + " %")
	
	coefficienti.write(regions[i] + ":\n")
	coefficienti.write("   c1: " + repr(c1) + "\n")
	coefficienti.write("   sigma_c1: " + repr(sigma_c1) + "\n")
	coefficienti.write("   c2: " + repr(c2) + "\n")
	coefficienti.write("   sigma_c2: " + repr(sigma_c2) + "\n")
	coefficienti.write("   c3: " + repr(c3) + "\n")
	coefficienti.write("   sigma_c3: " + repr(sigma_c3) + "\n")
	
	print("   " + "-"*27)
	print("   Na_s: " + repr(round(Na_s,2)))
	print("   Nb_s: " + repr(round(Nb_s,2)))
	print("   Ma_s: " + repr(round(Ma_s,2)))
	print("   Mb_s: " + repr(round(Mb_s,2)))
	

	coefficienti.write("   Na_s: " + repr(Na_s) + "\n")
	coefficienti.write("   Nb_s: " + repr(Nb_s) + "\n")
	coefficienti.write("   Ma_s: " + repr(Ma_s) + "\n")
	coefficienti.write("   Mb_s: " + repr(Mb_s) + "\n")
	
print("\n\n")
