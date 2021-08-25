import ROOT


PATH_Wgamma = "histograms_Wgamma.root"
PATH_Zgamma = "histograms_Zgamma.root"
PATH_Znunugamma = "histograms_Znunugamma.root"


file_Wgamma = ROOT.TFile(PATH_Wgamma)
file_Zgamma = ROOT.TFile(PATH_Zgamma)
file_Znunugamma = ROOT.TFile(PATH_Znunugamma)

files = [ file_Wgamma, file_Zgamma, file_Znunugamma ]

regions = [ key.GetName() for key in file_Wgamma.GetListOfKeys() ]

# seleziono le regioni che voglio plottare di ogni file 

Wgamma = [ 0, 1, 2, 3 ]
Zgamma = [ 0, 1, 2, 3]
Znunugamma = [ 0, 1, 2, 3]

selection = [ Wgamma, Zgamma, Znunugamma ]

# 		SR 1muCR 2muCR 2eCR
colors = [ 99, 94, 81, 54 ]
colors2 = [2, 3, 4]
CR = ["SR", "1muCR", "2muCR", "2eCR", "gammajetCR"]
sample = ["Wgamma", "Zgamma", "Znunugamma"] 

c1 = ROOT.TCanvas("c1")
c2 = ROOT.TCanvas("c2")
c3 = ROOT.TCanvas("c3")
c4 = ROOT.TCanvas("c4")
c5 = ROOT.TCanvas("c5")

canvas = [ c1, c2 ,c3, c4, c5]

legend1 = ROOT.TLegend(0.9,0.9,0.70,0.7)
legend2 = ROOT.TLegend(0.9,0.9,0.70,0.7)
legend3 = ROOT.TLegend(0.9,0.9,0.70,0.7)
legend4 = ROOT.TLegend(0.9,0.9,0.70,0.7)
legend5 = ROOT.TLegend(0.9,0.9,0.70,0.7)

legend = [ legend1, legend2, legend3, legend4, legend5 ]



N_hists = 0

for c in range(len(canvas)):

	canvas[c].cd()
	
	for f in range(len(files)):
		for i in [0]:#selection[f]:
		
			hist = files[f].Get(regions[5*i+c])
			hist.SetTitle(regions[5*i+c].split()[2])
			ROOT.gStyle.SetOptStat(0)

			try:

				hist.Scale(1/hist.GetMaximum())
				hist.GetYaxis().SetRangeUser(-0.02, 1.1)

				hist.SetLineColor(colors2[f])
				hist.SetMarkerColor(colors2[f])
				hist.SetLineWidth(1)

				hist.Draw("HISTLSAME")
				legend[c].AddEntry(hist, sample[f] + " - " + CR[i])

				N_hists = N_hists + 1

			except ZeroDivisionError:
				N_hists = N_hists + 1
				continue

	legend[c].Draw("SAME")

print(N_hists)
raw_input("Press enter to quit.")






