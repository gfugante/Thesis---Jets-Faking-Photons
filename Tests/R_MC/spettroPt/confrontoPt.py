import ROOT


PATH_Wjets = "histograms_Wjets.root"
PATH_Zjets = "histograms_Zjets.root"



file_Wjets = ROOT.TFile(PATH_Wjets)
file_Zjets = ROOT.TFile(PATH_Zjets)

files = [ file_Wjets, file_Zjets ]

regions = [ key.GetName() for key in file_Wjets.GetListOfKeys() ]

# seleziono le regioni che voglio plottare di ogni file 

Wjets = [ 0, 1]
Zjets = [ 0, 2, 3]

selection = [ Wjets, Zjets ]


colors = [ 99, 93, 54, 64, 74]

CR = ["SR", "1muCR", "2muCR", "2eCR", "gammajetCR"]
sample = ["Wjets", "Zjets"] 

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
n = 0 
n_ = 2

for c in range(len(canvas)):

	canvas[c].cd()
	
	for f in range(len(files)):
		
		for i in selection[f]:
		
			hist = files[f].Get(regions[5*i+c])
			hist.SetTitle(regions[5*i+c].split()[2])
			ROOT.gStyle.SetOptStat(0)

			try:

				hist.Scale(1/hist.GetMaximum())
				hist.GetYaxis().SetRangeUser(-0.02, 1.1)

				hist.SetLineColor(colors[n%5])
				hist.SetMarkerColor(colors[n%5])
				hist.SetLineWidth(1)

				hist.Draw("HISTLSAME")
				legend[c].AddEntry(hist, sample[f] + " - " + CR[i])

				N_hists = N_hists + 1
				
				n = n + 1

			except ZeroDivisionError:
				N_hists = N_hists + 1
				continue
		
		




	legend[c].Draw("SAME")

print(N_hists)
raw_input("Press enter to quit.")






