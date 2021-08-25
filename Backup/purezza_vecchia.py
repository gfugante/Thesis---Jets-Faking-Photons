import ROOT
import math
import numpy as np


def Purezza(Na,Nb,Ma,Mb):
	return 100. * (1. - (float(Nb*Ma*R_MC)/float(Na*Mb))) / (1. + ( float((c3*Na) - (c2*Nb*R_MC) - (c1*Ma*R_MC) ) / float(Mb)) )


R_MC = 1.

c1 = 0.
c2 = 0.
c3 = 0.

#bin tightness
tight = 5
tight3 = 1
tight4 = 2
tight5 = 3
nottight = 4

iso = [2., 3., 4.]
t = [tight3, tight4, tight5]

file = ROOT.TFile("root_files/grafici2D.root")

data = np.zeros((len(file.GetListOfKeys()), 9))
# 0.Na 1.Nb 2.Ma 3.Mb 4.Purezza 5.propagazione degli errori 6.errore sistematico isolamento 7.errore sistematico tightness
# 8.errore sistematico totale in quadratura

# nomi delle regioni
regions = []



for i in range(len(file.GetListOfKeys())):

	regions.append(file.GetListOfKeys()[i].GetName())
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
	
	try:	
		# purezza ed errore dalla propagazione(senza contare errori su R_MC e ci)
		data[i][4] = Purezza(data[i][0], data[i][1], data[i][2], data[i][3])
		
		data[i][5] = 100. * (float(data[i][1]*data[i][2])/float(data[i][0]*data[i][3])) * math.sqrt( (1./float(data[i][0])) + (1./float(data[i][1])) + (1./float(data[i][2])) + (1./float(data[i][3])))
		
		# calcolo delle incertezze sistematiche
		
		# isolamento
		binx3 = hist.GetXaxis().FindBin(iso[0])
		Nb = hist.Integral(binx3, binx4, tight, tight)
		Mb = hist.Integral(binx3, binx4, t[1], t[1])
		a = Purezza(data[i][0], Nb, data[i][2], Mb)
		
		binx3 = hist.GetXaxis().FindBin(iso[2])
		Nb = hist.Integral(binx3, binx4, tight, tight)
		Mb = hist.Integral(binx3, binx4, t[1], t[1])
		b = Purezza(data[i][0], Nb, data[i][2], Mb)
		
		data[i][6] = math.sqrt(pow(a-data[i][4],2) + pow(b-data[i][4],2))

		# tightness
		binx3 = hist.GetXaxis().FindBin(iso[1])

		Ma = hist.Integral(binx1, binx2, t[0], t[0])
		Mb = hist.Integral(binx3, binx4, t[0], t[0])
		a = Purezza(data[i][0], data[i][1], Ma, Mb)

		Ma = hist.Integral(binx1, binx2, t[2], t[2])
		Mb = hist.Integral(binx3, binx4, t[2], t[2])
		b = Purezza(data[i][0], data[i][1], Ma, Mb)

		data[i][7] = math.sqrt(pow(a-data[i][4],2) + pow(b-data[i][4],2))

		# errore sistematico totale calcolato come somma in quadratura
		data[i][8] = math.sqrt(pow(data[i][6],2) + pow(data[i][7],2))
		
	except ZeroDivisionError:
		continue




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








