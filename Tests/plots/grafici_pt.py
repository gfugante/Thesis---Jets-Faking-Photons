
from ROOT import TCanvas, TLegend, TFile, gStyle


variable_to_be_plotted = 'pt'

directory = ['simple plots', 'tight applied', 'track isolation applied']
selection = ['', ' tight selection applied', ' track isolation applied']
process   = ['Wgamma', 'Zgamma', 'Znunugamma', 'gammajets']
colors    = [2, 3, 4, 93]


canvas = []
legend = []
file   = []
hist   = []





for k in range(len(directory)):

	canvas.append(TCanvas('canvas' + repr(k+1)))
	canvas[k].cd()
	canvas[k].SetLogy()
	gStyle.SetOptStat(0)

	legend.append(TLegend(0.9,0.9,0.70,0.7))

	file.append([])
	hist.append([])



	for i in range(len(process)):

		file[k].append(TFile('/users2/gfugante/Test/plots/root_files/'+ directory[k] + '/' + process[i] + '_' + variable_to_be_plotted + '.root'))

		hist[k].append(file[k][i].Get('slice1'))
			
		hist[k][i].SetTitle(variable_to_be_plotted + ' distribution' + selection[k])
		hist[k][i].SetLineColor(colors[i])
		legend[k].AddEntry(hist[k][i], process[i], 'l')
		hist[k][i].DrawNormalized('histSame')




	legend[k].Draw("SAME")

	canvas[k].SaveAs('/users2/gfugante/Test/plots/PDF/' + directory[k] + '/pt distribution.pdf')






raw_input("\nPress enter to quit.")




