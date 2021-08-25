import ROOT
import math

PATH_IN_SEGNALE = "puro_segnale_pesato.root"
PATH_IN_FONDO = "puro_fondo_pesato.root"
PATH_OUT = "coefficienti_pesati.txt"

#bin tightness
tight = 5
tight3 = 1
tight4 = 2
tight5 = 3
nottight = 4

isolamento = 3.



file_segnale = ROOT.TFile(PATH_IN_SEGNALE)
file_background = ROOT.TFile(PATH_IN_FONDO)

coefficienti = open(PATH_OUT, "w+")


regions = [ key.GetName() for key in file_segnale.GetListOfKeys() ]


for i in range(len(file_segnale.GetListOfKeys())):

	hist_s = file_segnale.Get(regions[i])
	hist_b = file_background.Get(regions[i])


	binx1_s = hist_s.GetXaxis().FindBin(hist_s.GetXaxis().GetXmin())
	binx2_s = hist_s.GetXaxis().FindBin(0.) - 1
	binx3_s = hist_s.GetXaxis().FindBin( isolamento )
	binx4_s = hist_s.GetXaxis().FindBin(hist_s.GetXaxis().GetXmax())

	binx1_b = hist_b.GetXaxis().FindBin(hist_b.GetXaxis().GetXmin())
	binx2_b = hist_b.GetXaxis().FindBin(0.) - 1
	binx3_b = hist_b.GetXaxis().FindBin( isolamento )
	binx4_b = hist_b.GetXaxis().FindBin(hist_b.GetXaxis().GetXmax())
	

	# calcolo Na, Nb, Ma, Mb
	Na_b = hist_b.Integral(binx1_b, binx2_b, tight, tight)
	Nb_b = hist_b.Integral(binx3_b, binx4_b, tight, tight)
	Ma_b = hist_b.Integral(binx1_b, binx2_b, tight4, tight4)
	Mb_b = hist_b.Integral(binx3_b, binx4_b, tight4, tight4)

	Na_s = hist_s.Integral(binx1_s, binx2_s, tight, tight)
	Nb_s = hist_s.Integral(binx3_s, binx4_s, tight, tight)
	Ma_s = hist_s.Integral(binx1_s, binx2_s, tight4, tight4)
	Mb_s = hist_s.Integral(binx3_s, binx4_s, tight4, tight4)


	try:

		c1 = abs(Nb_s/Na_s)
		c2 = abs(Ma_s/Na_s)
		c3 = abs(Mb_s/Na_s)
		R_MC = abs((Na_b*Mb_b)/float(Nb_b*Ma_b))
		
		sigma_c1 = c1 * math.sqrt((1/Na_s) + (1/Nb_s))
		sigma_c2 = c2 * math.sqrt((1/Na_s) + (1/Ma_s))
		sigma_c3 = c3 * math.sqrt((1/Na_s) + (1/Mb_s))
		

		# problemi con integrali negativi (Na per la 1muCr - ISR2!
		sigma_R_MC = R_MC * math.sqrt((1/Na_b) + (1/Nb_b) + (1/Ma_b) + (1/Mb_b))


	except (ZeroDivisionError, ValueError):
		c1 = 0
		c2 = 0
		c3 = 0
		R_MC = 0

		sigma_c1 = 0	
		sigma_c2 = 0
		sigma_c3 = 0
		sigma_R_MC = 0


	print("\n")
	print(regions[i])
	print("   c1: \t\t" + repr(round(100*c1,3)) + " %")
	print("   sigma_c1: \t" + repr(round(100*sigma_c1,3)) + " %")
	print("   c2: \t\t" + repr(round(100*c2,3)) + " %")
	print("   sigma_c2: \t" + repr(round(100*sigma_c2,3)) + " %")
	print("   c3: \t\t" + repr(round(100*c3,3)) + " %")
	print("   sigma_c3: \t" + repr(round(100*sigma_c3,3)) + " %")
	print("   R_MC: \t" + repr(round(R_MC,3)))
	print("   sigma_R_MC: \t" + repr(round(sigma_R_MC,3)))

	coefficienti.write(regions[i] + ":\n")
	coefficienti.write("   c1: " + repr(c1) + "\n")
	coefficienti.write("   sigma_c1: " + repr(sigma_c1) + "\n")
	coefficienti.write("   c2: " + repr(c2) + "\n")
	coefficienti.write("   sigma_c2: " + repr(sigma_c2) + "\n")
	coefficienti.write("   c3: " + repr(c3) + "\n")
	coefficienti.write("   sigma_c3: " + repr(sigma_c3) + "\n")
	coefficienti.write("   R_MC: " + repr(R_MC) + "\n")
	coefficienti.write("   sigma_R_MC: " + repr(sigma_R_MC) + "\n")

	print("   " + "-"*27)
	print("   Na_s: " + repr(round(Na_s,2)))
	print("   Nb_s: " + repr(round(Nb_s,2)))
	print("   Ma_s: " + repr(round(Ma_s,2)))
	print("   Mb_s: " + repr(round(Mb_s,2)))
	print("   Na_b: " + repr(round(Na_b,2)))
	print("   Nb_b: " + repr(round(Nb_b,2)))
	print("   Ma_b: " + repr(round(Ma_b,2)))
	print("   Mb_b: " + repr(round(Mb_b,2)))

print("\n\n")
