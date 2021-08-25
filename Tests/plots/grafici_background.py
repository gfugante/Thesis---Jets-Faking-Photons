
from ROOT import TCanvas, TLegend, TFile, gStyle



process   = ['Wjets', 'Zjets']
selection = ['tight', 'tight4']
selection_string = ['tight', 'tight-4']
colors    = [2, 4]


canvas = []
legend = []
file   = []
hist   = []





for k in range(len(process)):

	canvas.append(TCanvas('canvas' + repr(k+1)))
	canvas[k].cd()
	#canvas[k].SetLogy()
	gStyle.SetOptStat(0)

	legend.append(TLegend(0.9,0.9,0.70,0.8))

	file.append([])
	hist.append([])



	for i in range(len(selection)):

		file[k].append(TFile('/users2/gfugante/Test/plots/root_files/background isolation/' + process[k] + '_' + selection[i]+ '.root'))

		hist[k].append(file[k][i].Get('slice1'))
			
		hist[k][i].SetTitle(process[k] + ' isolation profiles')
		hist[k][i].SetLineColor(colors[i])
		legend[k].AddEntry(hist[k][i], selection_string[i], 'l')
		hist[k][i].DrawNormalized('histSame')




	legend[k].Draw("SAME")

	canvas[k].SaveAs('/users2/gfugante/Test/plots/PDF/background isolation/' + process[k] + ' background isolation.pdf')






raw_input("\nPress enter to quit.")



