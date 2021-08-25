import ROOT
import math
import numpy as np
import yaml
import derivate_complete as dc
import derivate_ridotte as dr


# path degli oggetti usati e creati

PATH_EVENTI = "root_files/eventi_pesati.root"
PATH_COEFFICIENTI = "coefficienti_pesati.txt"



# oggetti necessari alle funzioni

with open(PATH_COEFFICIENTI, "r") as f:
	coeff = yaml.load(f)

app_lambda = []
toll = 1E-5

# calcolo della purezza e dell'errore propagato

def Purezza(Na,Nb,Ma,Mb,c1,c2,c3,R_MC,save_app=False):

	if(Na is 0 or Nb is 0 or Ma is 0 or Mb is 0 or c1 is 0 or c2 is 0 or c3 is 0 or R_MC is 0):
		if save_app is True:
			app_lambda.append(-999)
		return 0
	else:

		x = Mb + Na*c3 - Nb*c2*R_MC - Ma*c1*R_MC
		y = c1*c2*R_MC - c3
		z = 4*y*(Na*Mb - Nb*Ma*R_MC)/pow(x,2)
		
		if save_app is True:
			app_lambda.append(z)
		
		try:
			if( abs(z) < toll ):
				return 100*(1 - (Nb*Ma*R_MC)/(Na*Mb)) * Mb / x 

			else:
				return 100*x*(-1 + math.sqrt(1 + z))/ (2*y*Na)

		except (ZeroDivisionError,ValueError):
			return 0

def SigmaPurezza(Na,Nb,Ma,Mb,c1,sigma_c1,c2,sigma_c2,c3,sigma_c3,R_MC,sigma_R_MC):

	if(Na is 0 or Nb is 0 or Ma is 0 or Mb is 0 or c1 is 0 or c2 is 0 or c3 is 0 or R_MC is 0):
		return 0, 0

	else:

		x = Mb + Na*c3 - Nb*c2*R_MC - Ma*c1*R_MC
		y = c1*c2*R_MC - c3
		z = 4*y*(Na*Mb - Nb*Ma*R_MC)/pow(x,2)
		
		try:


			# errore approssimato
			DNa = dr.DNa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			DNb = dr.DNb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			DMa = dr.DMa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			DMb = dr.DMb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)

			Dc1 = dr.Dc1(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			Dc2 = dr.Dc2(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			Dc3 = dr.Dc3(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			DR_MC = dr.DR_MC(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)


			e1 = 100*math.sqrt( Na*pow(DNa,2) + Nb*pow(DNb,2) + Ma*pow(DMa,2) + Mb*pow(DMb,2) + \
							  pow(Dc1*sigma_c1,2) + pow(Dc2*sigma_c2,2) + pow(Dc3*sigma_c3,2) + pow(DR_MC*sigma_R_MC,2) )

			# errore non approssimato
			DNa = dc.DNa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			DNb = dc.DNb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			DMa = dc.DMa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			DMb = dc.DMb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)

			Dc1 = dc.Dc1(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			Dc2 = dc.Dc2(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			Dc3 = dc.Dc3(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			DR_MC = dc.DR_MC(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
			
			e2 = 100*math.sqrt( Na*pow(DNa,2) + Nb*pow(DNb,2) + Ma*pow(DMa,2) + Mb*pow(DMb,2) + \
							  pow(Dc1*sigma_c1,2) + pow(Dc2*sigma_c2,2) + pow(Dc3*sigma_c3,2) + pow(DR_MC*sigma_R_MC,2) )

			return e1, e2
			
		
		except (ZeroDivisionError, ValueError):
			return 0, 0




# bin tightness
tight 		= 5
tight3 		= 1
tight4		= 2
tight5 		= 3
nottight 	= 4


# quantita' usate per il calcolo delle sistematiche, gli elementi centrali delle liste calcolano al purezza attese,
# mentre il primo e l'ultimo le purezze per la stima delle sistematiche

iso = [2., 3., 4.]
t = [tight3, tight4, tight5]



file = ROOT.TFile(PATH_EVENTI)

# nomi delle regioni
regions = [ key.GetName() for key in file.GetListOfKeys() ]

print("\n")
print("Propagazione degli errori:")
print("\n")
print("-"*90)
print("Regione		Errore			Errore			Differenza")
print("             	approssimato		non approssimato")
print("-"*90)

for i in range(len(file.GetListOfKeys())):

	hist = file.Get(regions[i])

	binx1 = hist.GetXaxis().FindBin(hist.GetXaxis().GetXmin())
	binx2 = hist.GetXaxis().FindBin(0.) - 1
	binx3 = hist.GetXaxis().FindBin(iso[1])
	binx4 = hist.GetXaxis().FindBin(hist.GetXaxis().GetXmax())
	
	# calcolo Na, Nb, Ma, Mb
	Na = hist.Integral(binx1, binx2, tight, tight)
	Nb = hist.Integral(binx3, binx4, tight, tight)
	Ma = hist.Integral(binx1, binx2, t[1], t[1])
	Mb = hist.Integral(binx3, binx4, t[1], t[1])

	
	# carico coefficienti di SL e R
	c1 = coeff[regions[i]]["c1"]
	sigma_c1 = coeff[regions[i]]["sigma_c1"]
	c2 = coeff[regions[i]]["c2"]
	sigma_c2 = coeff[regions[i]]["sigma_c2"]
	c3 = coeff[regions[i]]["c3"]
	sigma_c3 = coeff[regions[i]]["sigma_c3"]
	R_MC = coeff[regions[i]]["R_MC"]
	sigma_R_MC = coeff[regions[i]]["sigma_R_MC"]

	
	e1, e2 = SigmaPurezza(Na,Nb,Ma,Mb,c1,sigma_c1,c2,sigma_c2,c3,sigma_c3,R_MC,sigma_R_MC)
	
	print(regions[i] + "	" + repr(round(e1,3)) + "			" +  repr(round(e2,3)) + "			" + repr(round(abs(e1-e2),3)))


print("-"*90)
print("\n")


