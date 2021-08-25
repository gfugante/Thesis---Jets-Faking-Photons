
from ROOT import TCanvas, TLegend, TFile, gStyle


variable_to_be_plotted = 'eta'

directory = ['simple plots', 'tight applied', 'track isolation applied']
selection = ['', ' tight selection applied', ' track isolation applied']
process   = ['Wgamma', 'Zgamma', 'Znunugamma', 'gammajets']
colors    = [2, 3, 4, 93]
pt_slice  = [150, 225, 300, 2000]


canvas = []
legend = []
file   = []
hist   = []




for k in range(len(directory)):

	canvas.append([])
	legend.append([])
	file.append([])
	hist.append([])

	for j in range(3):


		canvas[k].append(TCanvas('c' + repr(3*k + j)))
		canvas[k][j].cd()
		#canvas[k][j].SetLogy()
		gStyle.SetOptStat(0)

		legend[k].append(TLegend(0.9,0.9,0.70,0.7))


		file[k].append([])
		hist[k].append([])


		for i in range(len(process)):

			file[k][j].append(TFile('/users2/gfugante/Test/plots/root_files/'+ directory[k] + '/' + process[i] + '_' + variable_to_be_plotted + '.root'))

			hist[k][j].append(file[k][j][i].Get('slice' + repr(j+1)))
				
			hist[k][j][i].SetTitle(variable_to_be_plotted + ' distribution  pt: ' + repr(pt_slice[j]) + '-' + repr(pt_slice[j+1]) + ' GeV' + selection[k])
			hist[k][j][i].SetLineColor(colors[i])
			legend[k][j].AddEntry(hist[k][j][i], process[i], 'l')
			hist[k][j][i].DrawNormalized('histSame')




		legend[k][j].Draw("SAME")

		canvas[k][j].SaveAs('/users2/gfugante/Test/plots/PDF/' + directory[k] + '/eta distribution pt ' + repr(pt_slice[j]) + '-' + repr(pt_slice[j+1]) + '.pdf')

raw_input("\nPress enter to quit.")
