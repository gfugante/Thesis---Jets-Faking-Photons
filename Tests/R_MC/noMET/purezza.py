import ROOT
import math
import numpy as np
import yaml
import derivate_complete as dc
import derivate_ridotte as dr


# path degli oggetti usati e creati

PATH_EVENTI = "eventi_pesati.root"
PATH_COEFFICIENTI = "coefficienti_pesati.txt"
PATH_APPROSSIMAZIONI = "approssimazioni_pesate.txt"
PATH_DATI = "dati_pesati.txt"



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
		return 0

	else:

		x = Mb + Na*c3 - Nb*c2*R_MC - Ma*c1*R_MC
		y = c1*c2*R_MC - c3
		z = 4*y*(Na*Mb - Nb*Ma*R_MC)/pow(x,2)
		
		try:

			if( abs(z) < toll ):

				DNa = dr.DNa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				DNb = dr.DNb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				DMa = dr.DMa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				DMb = dr.DMb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)

				Dc1 = dr.Dc1(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				Dc2 = dr.Dc2(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				Dc3 = dr.Dc3(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				DR_MC = dr.DR_MC(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)


				return 100*math.sqrt( Na*pow(DNa,2) + Nb*pow(DNb,2) + Ma*pow(DMa,2) + Mb*pow(DMb,2) + \
								  pow(Dc1*sigma_c1,2) + pow(Dc2*sigma_c2,2) + pow(Dc3*sigma_c3,2) + pow(DR_MC*sigma_R_MC,2) )

			else:
				
				DNa = dc.DNa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				DNb = dc.DNb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				DMa = dc.DMa(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				DMb = dc.DMb(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)

				Dc1 = dc.Dc1(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				Dc2 = dc.Dc2(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				Dc3 = dc.Dc3(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				DR_MC = dc.DR_MC(Na,Nb,Ma,Mb,c1,c2,c3,R_MC)
				

				return 100*math.sqrt( Na*pow(DNa,2) + Nb*pow(DNb,2) + Ma*pow(DMa,2) + Mb*pow(DMb,2) + \
								  pow(Dc1*sigma_c1,2) + pow(Dc2*sigma_c2,2) + pow(Dc3*sigma_c3,2) + pow(DR_MC*sigma_R_MC,2) )

		
		except (ZeroDivisionError, ValueError):
			return 0




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

data = np.zeros((len(file.GetListOfKeys()), 9))
# 0.Na 1.Nb 2.Ma 3.Mb 4.Purezza 5.propagazione degli errori 6.errore sistematico isolamento 7.errore sistematico tightness
# 8.errore sistematico totale in quadratura

# nomi delle regioni
regions = [ key.GetName() for key in file.GetListOfKeys() ]



# calcoli delle purezze e delle sistematiche

for i in range(len(file.GetListOfKeys())):

	hist = file.Get(regions[i])

	binx1 = hist.GetXaxis().FindBin(hist.GetXaxis().GetXmin())
	binx2 = hist.GetXaxis().FindBin(0.) - 1
	binx3 = hist.GetXaxis().FindBin(iso[1])
	binx4 = hist.GetXaxis().FindBin(hist.GetXaxis().GetXmax())
	
	# calcolo Na, Nb, Ma, Mb
	data[i][0] = hist.Integral(binx1, binx2, tight, tight)
	data[i][1] = hist.Integral(binx3, binx4, tight, tight)
	data[i][2] = hist.Integral(binx1, binx2, t[1], t[1])
	data[i][3] = hist.Integral(binx3, binx4, t[1], t[1])

	
	# carico coefficienti di SL e R
	c1 = coeff[regions[i]]["c1"]
	sigma_c1 = coeff[regions[i]]["sigma_c1"]
	c2 = coeff[regions[i]]["c2"]
	sigma_c2 = coeff[regions[i]]["sigma_c2"]
	c3 = coeff[regions[i]]["c3"]
	sigma_c3 = coeff[regions[i]]["sigma_c3"]
	R_MC = coeff[regions[i]]["R_MC"]
	sigma_R_MC = coeff[regions[i]]["sigma_R_MC"]
	
	try:	
		# purezza ed errore dalla propagazione

		data[i][4] = Purezza(data[i][0], data[i][1], data[i][2], data[i][3], c1, c2, c3, R_MC, save_app=True)
		
		data[i][5] = SigmaPurezza(data[i][0], data[i][1], data[i][2], data[i][3], \
									c1, sigma_c1, c2, sigma_c2, c3, sigma_c3, R_MC, sigma_R_MC)
		
		# calcolo delle incertezze sistematiche
		
		# isolamento
		binx3 = hist.GetXaxis().FindBin(iso[0])
		Nb = hist.Integral(binx3, binx4, tight, tight)
		Mb = hist.Integral(binx3, binx4, t[1], t[1])
		a = Purezza(data[i][0], Nb, data[i][2], Mb, c1, c2, c3, R_MC)
		
		binx3 = hist.GetXaxis().FindBin(iso[2])
		Nb = hist.Integral(binx3, binx4, tight, tight)
		Mb = hist.Integral(binx3, binx4, t[1], t[1])
		b = Purezza(data[i][0], Nb, data[i][2], Mb, c1, c2, c3, R_MC)
		
		data[i][6] = math.sqrt(pow(a-data[i][4],2) + pow(b-data[i][4],2))

		# tightness
		binx3 = hist.GetXaxis().FindBin(iso[1])

		Ma = hist.Integral(binx1, binx2, t[0], t[0])
		Mb = hist.Integral(binx3, binx4, t[0], t[0])
		a = Purezza(data[i][0], data[i][1], Ma, Mb, c1, c2, c3, R_MC)

		Ma = hist.Integral(binx1, binx2, t[2], t[2])
		Mb = hist.Integral(binx3, binx4, t[2], t[2])
		b = Purezza(data[i][0], data[i][1], Ma, Mb, c1, c2, c3, R_MC)

		data[i][7] = math.sqrt(pow(a-data[i][4],2) + pow(b-data[i][4],2))

		# errore sistematico totale calcolato come somma in quadratura
		data[i][8] = math.sqrt(pow(data[i][6],2) + pow(data[i][7],2))
		
	except ZeroDivisionError:
		continue


# scrittura delle approssimazioni 
approssimazioni = open(PATH_APPROSSIMAZIONI, "w+")
for i in range(len(app_lambda)):
	approssimazioni.write(repr(app_lambda[i]) + "\n")

# scrittura dei risultati
dati = open(PATH_DATI, "w+")
for i in range(len(file.GetListOfKeys())):
	for j in range(9):
		dati.write(repr(data[i][j]) + "\t")
	dati.write("\n")



# print dei risultati

space = 12
roundN = 2

print("\n\n")

print("-"*75)
print("Regioni".ljust(space+5) + "Na".ljust(space) + "Nb".ljust(space) + "Ma".ljust(space) + "Mb".ljust(space) + 
	  "Purezza")
print("-"*75)

for i in range(len(regions)):
	print (regions[i].ljust(space + 5) + repr(round(data[i][0],roundN)).ljust(space) + repr(round(data[i][1],roundN)).ljust(space) + 
		   repr(round(data[i][2],roundN)).ljust(space) + repr(round(data[i][3],roundN)).ljust(space) + repr(round(data[i][4],roundN)).ljust(0) )
print("-"*75)
print("\n\n")

space = 16
print("-"*99)
print("Regioni      	Purezza 	propagazione 	sistematica 	sistematica 	errore sistematico")
print("             			degli errori 	isolamento 	tightness	totale")
print("-"*99)
for i in range(len(regions)):
	print (regions[i].ljust(space) + repr(round(data[i][4],roundN)).ljust(space) + repr(round(data[i][5],roundN)).ljust(space) +  
		   repr(round(data[i][6],roundN)).ljust(space) + repr(round(data[i][7],roundN)).ljust(space) + repr(round(data[i][8],roundN)).ljust(0))
print("-"*99)
print("\n\n")






