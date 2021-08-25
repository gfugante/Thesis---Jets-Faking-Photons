import ROOT


PATH_Wgamma = "root_files/Wgamma_Eiso.root"
PATH_Zgamma = "root_files/Zgamma_Eiso.root"
PATH_Znunugamma = "root_files/Znunugamma_Eiso.root"


file_Wgamma = ROOT.TFile(PATH_Wgamma)
file_Zgamma = ROOT.TFile(PATH_Zgamma)
file_Znunugamma = ROOT.TFile(PATH_Znunugamma)

files = [ file_Wgamma, file_Zgamma, file_Znunugamma ]

regions = [ key.GetName() for key in file_Wgamma.GetListOfKeys() ]


colors = [2, 4, 8]
sample = ["Wgamma", "Zgamma", "Znunugamma"] 

c1 = ROOT.TCanvas("c1")
c1.SetLogy()

legend = ROOT.TLegend(0.9,0.9,0.70,0.7)


for f in range(len(files)):
	
	hist = files[f].Get(regions[0])
	hist.SetTitle(regions[0])
	ROOT.gStyle.SetOptStat(0)
	
	try:

		hist.Scale(1/hist.Integral())
		#hist.GetYaxis().SetRangeUser(-0.02, 1.1)

		hist.SetLineColor(colors[f])
		hist.SetMarkerColor(colors[f])
		hist.SetLineWidth(1)

		hist.Draw("HISTSAME")
		legend.AddEntry(hist, sample[f])

	except ZeroDivisionError:
		continue


legend.Draw("SAME")


raw_input("Press enter to quit.")






